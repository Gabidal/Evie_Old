#include "../../H/BackEnd/IROptimizer.h"

void IROptimizer::Factory(){

    for (int i = 0; i < Input.size(); i++){
        for (auto& arg : Input[i]->Arguments){
            Combine_Scale_And_Offset_In_Memory(arg);
        }
    }


}

// [(((reg + reg) + 123) * 4)]
// ->
// {reg, +, reg, +, 123, *, 4}
vector<Token*> IROptimizer::Liquify_MEM_AST(Token* t){
    vector<Token*> Result;

    if (t->Any(TOKEN::SCALER | TOKEN::OFFSETTER | TOKEN::DEOFFSETTER)){
        vector<Token*> tmp = Liquify_MEM_AST(t->Left);

        // Add the left side of the operator.
        Result.insert(Result.end(), tmp.begin(), tmp.end());

        // add itself to the center
        Result.push_back(t);

        tmp = Liquify_MEM_AST(t->Right);

        // add the right side right after the centre.
        Result.insert(Result.end(), tmp.begin(), tmp.end());
    }
    // Open the paranthesis. e.g: TOKEN::CONTENT.
    else if (t->Childs.size() > 0){
        vector<Token*> tmp;

        for (auto& c : t->Childs){
            tmp = Liquify_MEM_AST(c);
            Result.insert(Result.end(), tmp.begin(), tmp.end());
        }
    }
    //Paranthesis wont have it's own place in the liquid list.
    else{
        Result.push_back(t);
    }

    return Result;
}

// This function finds spots where the operator sides can be switched whitout contaminating the equation.
// {213, +, reg, +, 32, *, 4}
// ->
// {reg, +, 213, +, 32, *, 4}
void IROptimizer::Switch_Operator_Sides(vector<Token*>& liquid){

    // {123, +, reg1, + 345, *, 2}
    // ->
    // {reg1, +, 123, + 345, *, 2}

    vector<bool> Movables;

    Movables.resize(liquid.size(), true);

    // First asses the liquided tokens that cannot be switched, this can occur either when the operator between the current tokens
    // Is either a * or -.
    for (int Current = 0; Current < liquid.size(); Current++){
        if (liquid[Current]->Any(TOKEN::DEOFFSETTER | TOKEN::SCALER)){
            for (int i = Current - 1; i < Current + 1; i++){
                Movables[i] = false;
            }
        }
    }

    // Now we can go and check if there are any movable numbers that can be switched to be more closer to another numbers.
    for (int i = 0; i < liquid.size(); i++){

        int Left = i-1;
        int Right = i+1;

        int Right_Operator = Right + 1;
        int Right_Operator_Right_Side = Right_Operator + 1;

        if (liquid[i]->Any(TOKEN::OFFSETTER)){

            if (liquid[Left]->Any(TOKEN::NUM) && !liquid[Right]->Any(TOKEN::NUM) && Movables[Right]){
                // {13, +, reg}

                //check if the right side of this operator could have a number
                // {13, +, reg, +, 2}
                // The right side operator cannot be any other operator other than +, because - and * are not movables, 
                // and thus the right side of this poerator should also have been immovable.
                if (liquid[Right_Operator_Right_Side]->Any(TOKEN::NUM)){
                    // Now we can switch this left side with this right side.
                    Switch_Sides(liquid, Left, Right);
                }
            }
        }
    }
}

// {l, +, r, +, 123}
// ->
// {r, +, l, +, 123}
void IROptimizer::Switch_Sides(vector<Token*>& liquid, int l, int r){

    Token Left_Tmp = *liquid[l];

    Token Right_Tmp = *liquid[r];

    *liquid[l] = Right_Tmp;
    *liquid[r] = Left_Tmp;

    // Now also setup the parents and other AST information.
    liquid[l]->Left = Left_Tmp.Left;
    liquid[l]->Right = Left_Tmp.Right;

    liquid[l]->Parent = Left_Tmp.Parent;
    liquid[l]->Childs = Left_Tmp.Childs;

    liquid[r]->Left = Right_Tmp.Left;
    liquid[r]->Right = Right_Tmp.Right;

    liquid[r]->Parent = Right_Tmp.Parent;
    liquid[r]->Childs = Right_Tmp.Childs;
}

// [reg + 0 * 4]
// ->
// [reg]
void IROptimizer::Combine_Scale_And_Offset_In_Memory(Token* mem){
    if (!mem->Any(TOKEN::MEMORY))
        return;

    vector<Token*> Liquid_List = Liquify_MEM_AST(mem);

    // Make sure that the operator sides coside with eachother.
    Switch_Operator_Sides(Liquid_List);

    for (int opc = 0; opc < Liquid_List.size(); opc++){
        if (!Liquid_List[opc]->Any(TOKEN::OFFSETTER | TOKEN::SCALER | TOKEN::DEOFFSETTER))
            continue;

        //chekc if the bith sides are numbers.
        int Left = opc - 1;
        int Right = opc + 1;

        if (!Liquid_List[Left]->Any(TOKEN::NUM) || !Liquid_List[Right]->Any(TOKEN::NUM))
            continue;

        // Now we can combine the two numbers.
        int Left_Num = stoi(Liquid_List[Left]->Name);
        int Right_Num = stoi(Liquid_List[Right]->Name);

        int Result = 0;

        if (Liquid_List[opc]->Any(TOKEN::OFFSETTER)){
            Result = Left_Num + Right_Num;
        }
        else if (Liquid_List[opc]->Any(TOKEN::SCALER)){
            Result = Left_Num * Right_Num;
        }
        else if (Liquid_List[opc]->Any(TOKEN::DEOFFSETTER)){
            Result = Left_Num - Right_Num;
        }

        // Now we can replace the three tokens with one.
        // because the operator is always the gateway to the right and left side, thus the operator is where wew will replace this result.
        Token opc_tmp = *Liquid_List[opc];

        *Liquid_List[opc] = *Liquid_List[Left];

        Liquid_List[opc]->Name = to_string(Result);

        // {(reg, + 12), +, 243}
        // ->
        // {reg, +, 265}

        // Also if the opc has a another operator on it's left or right side.
        if (opc_tmp.Left->Any(TOKEN::OFFSETTER | TOKEN::DEOFFSETTER | TOKEN::SCALER)){
            Token* New_Parent = opc_tmp.Left;

            *New_Parent->Right = *Liquid_List[opc];

            *Liquid_List[opc] = *New_Parent;
        }

        if (opc_tmp.Right->Any(TOKEN::OFFSETTER | TOKEN::DEOFFSETTER | TOKEN::SCALER)){
            Token* New_Parent = opc_tmp.Right;

            *New_Parent->Left = *Liquid_List[opc];

            *Liquid_List[opc] = *New_Parent;
        }
    }
}