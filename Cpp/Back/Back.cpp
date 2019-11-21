#include "../../H/Back/Back.h"

/*void Back::Handle_Usation(int &i)
{
    if (Input.at(i)->is(Used) == false)
    {
        i++;
    }
}*/

void Back::Handle_Operators(int i)
{
    if (Input.at(i)->is(OPERATOR))
    {
        if (Input.at(i)->Parameters.at(0)->is(Variable))
        {
            Dest = Input.at(i)->Parameters.at(0);
        }
        else
        {
            Back b = *this;
            b.Input = Input.at(i)->Parameters;
            b.Layer++;
            b.Factory();
            b.Layer--;
            this->Dest = b.Dest;
            this->Cheat = b.Cheat;
        }
        if (Input.at(i)->Childs.at(0)->is(Variable) || Input.at(i)->Childs.at(0)->is(Number))
        {
            Source = Input.at(i)->Childs.at(0);
        }
        else
        {
            Back b = *this;
            b.Input = Input.at(i)->Childs;
            b.Layer++;
            b.Factory();
            b.Layer--;
            this->Source = b.Source;
            this->Cheat = b.Cheat;
        }
        string reg = "";
        if (Input.at(i)->Name == "+")
        {
            reg = Dest->SUM(Source);
        }
        else if (Input.at(i)->Name == "-")
        {
            reg = Dest->SUBSTRACT(Source);
        }
        else if (Input.at(i)->Name == "*")
        {
            reg = Dest->MULTIPLY(Source);
        }
        else if (Input.at(i)->Name == "/")
        {
            reg = Dest->DIVIDE(Source);
        }
        else if (Input.at(i)->Name == "=" && Layer == 0)
        {
            Dest->MOVE(Source);
            reg = "";
        }
        else if (Input.at(i)->Name == "==" || Input.at(i)->Name == ">=" || Input.at(i)->Name == "<=" || Input.at(i)->Name == ">" || Input.at(i)->Name == "<" || Input.at(i)->Name == "!=" || Input.at(i)->Name == "!>" || Input.at(i)->Name == "!<")
        {
            Dest->COMPARE(Source);
        }
        else if (Layer != 0)
        {
            Cheat = Dest;
            Dest = Source;
        }
        
        if (reg.size() > 0 && Layer == 0)
        {
            Dest = Cheat;
            Dest->Reg = registers[reg];
            Output += MOV + Dest->GetAddress() + FROM + Dest->Reg->Name + NL + NL;
        }
    }
}

void Back::Handle_Variables(int i)
{
    if (Input.at(i)->is(Variable) || Input.at(i)->is(Ptr) || Input.at(i)->is(Number))
    {
        if (Priority_For_Parametering)
        {
            if (Input.at(i)->is(Ptr))
            {
                Output += PUSH + Input.at(i)->GetAddress() + NL;
            }
            else if (Input.at(i)->is(Variable))
            {
                Output += PUSH + Input.at(i)->InitVariable() + NL;
            }
            else
            {
                Output += PUSH + Input.at(i)->Name + NL;
            }
        }
        if (Get_Direct)
        {
            Dest = Input.at(i);
        }
    }
}

vector<Token*> *seen = new vector<Token*>();
int Get_Amount(vector<Token*> list, int flag)
{
    int ret = 0;
    for (int i = 0; i < list.size(); i++)
    {
       if (list.at(i)->Childs.size() > 0)
       {
           ret += Get_Amount(list.at(i)->Childs, flag);
       }
       else if (list.at(i)->Any(flag) && find(seen->begin(), seen->end(), list.at(i)) == seen->end() && find(list.at(i)->Parameters.begin(), list.at(i)->Parameters.end(), list.at(i)) == list.at(i)->Parameters.end())
       {
           seen->push_back(list.at(i));
           ret++;
       }
    }
    return ret;
}

void Back::Handle_Function_Init(int i)
{
    if (Input.at(i)->is(Function) && Input.at(i)->is(Call) == false)
    {
        Input.at(i)->InitFunction();
        Back b = *this;
        b.Input = Input.at(i)->Childs;
        StackFrame stack(Output, true);
        int care = Variable | Ptr;
        Output += SUB + ESP->Name + FROM + to_string(Get_Amount(Input.at(i)->Childs, care) * 4) + NL + NL;
        b.IS_PUBLIC++;
        b.Factory();
        b.IS_PUBLIC--;
    }
}

void Back::Handle_Type_Init(int i)
{
    if (Input.at(i)->is(TypE) && Input.at(i)->is(__NEW) == false)
    {
        Back b = *this;
        vector<Token*> vars;
        vector<Token*> Functions;
        for (int j = 0; j < Input.at(i)->Childs.size(); j++)
        {
            if (Input.at(i)->Childs.at(j)->is(Variable) || Input.at(i)->Childs.at(j)->is(Ptr))
            {
                vars.push_back(Input.at(i)->Childs.at(j));
            }
            else
            {
                Functions.push_back(Input.at(i)->Childs.at(j));
            }
        }
        if (vars.size() > 0)
        {
            b.Input = vars;
            b.IS_PUBLIC++;
            b.Factory();
            b.IS_PUBLIC--;
        }
        if (Functions.size() > 0)
        {
            b.Input = Functions;
            b.IS_PUBLIC++;
            b.Factory();
            b.IS_PUBLIC--;
        }
    }
}

void Back::Handle_Call_Function(int i)
{
    if (Input.at(i)->is(Call))
    {
        if (Input.at(i)->Parameters.size() > 0)
        {
            Back b = *this;
            b.Input = Input.at(i)->Parameters;
            b.Priority_For_Parametering = true;
            b.Factory();
            if (Input.at(i)->is(This))
            {
                //for function fetching in types;
                b.Input.clear();
                b.Input.push_back(Input.at(i)->Fetcher);
                b.Priority_For_Parametering = true;
                b.Factory();
            }
        }
        Output += CALL + Input.at(i)->getFullName() + NL + NL;
        if (Input.at(i)->is(Returning))
        {
            Source = Input.at(i);
        }
        
    }
}

void Back::Handle_Arrays(int i)
{

}

int Back::Find(string name, int flag, vector<Token*> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list.at(i)->Name == name && list.at(i)->is(flag))
        {
            return i;
        }
    }
    return -1;
}

string Back::END(int i)
{
    return string("END");
}

void Back::Handle_Jumps(int i)
{
    string conditionJump = "";
    if (Find("==", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JNE ;
    }
    if (Find("!=", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JE ;
    }
    if (Find(">=", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JNGE ;
    }
    if (Find("<=", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JNLE ;
    }
    if (Find("<", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JG ;
    }
    if (Find(">", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JL ;
    }
    if (Find("!<", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JGE ;
    }
    if (Find("!>", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JLE ;
    }
    string destination = "";
    int ID = 0;
    string endd = "";
    if (Input.at(i)->is(Successour))
    {
        destination = Input.at(i)->Former->SuccessorToken.at(0)->getFullName();
        ID = Input.at(i)->Former->SuccessorToken.at(0)->ID;
    }
    else if (Input.at(i)->SuccessorToken.size() > 0)
    {
        destination = Input.at(i)->SuccessorToken.at(0)->getFullName();
        ID = Input.at(i)->SuccessorToken.at(0)->ID;
        Input.at(i)->SuccessorToken.erase(Input.at(i)->SuccessorToken.begin() + 0);
    }
    else
    {
        destination = Input.at(i)->getFullName();
        ID = Input.at(i)->ID;
        endd = "END";
    }
    
    Output += conditionJump + destination + to_string(ID) + endd + NL;
}

void Back::Handle_Conditions(int i)
{
    if (Input.at(i)->is(If) || Input.at(i)->is(Else))
    {
        Back b = *this;
        if ((Input.at(i)->is(Else) && Input.at(i)->is(If)) || Input.at(i)->is(Else))
            Output += JMP + Input.at(i)->Former->SuccessorToken.at(Input.at(i)->Former->SuccessorToken.size() - 1)->getFullName() + to_string(Input.at(i)->Former->SuccessorToken.at(Input.at(i)->Former->SuccessorToken.size() - 1)->ID) + NL;
        Output += LABEL(Input.at(i)->getFullName() + to_string(Input.at(i)->ID));

        //if
        if (Input.at(i)->Parameters.size() > 0 && Input.at(i)->is(While) != true)
        {
            b.Input = Input.at(i)->Parameters;
            b.Factory();
            Handle_Jumps(i);
        }
        //( ...)
        if (Input.at(i)->Childs.size() > 0)
        {
            b.Input = Input.at(i)->Childs;
            b.Factory();
        }
        //while
        if (Input.at(i)->Parameters.size() > 0 && Input.at(i)->is(While))
        {
            b.Input = Input.at(i)->Parameters;
            b.Factory();
            Handle_Jumps(i);
        }
        Output += LABEL(Input.at(i)->getFullName() + to_string(Input.at(i)->ID) + END(i));
    }
}

void Back::Handle_Returning(int i)
{
    if (Input.at(i)->Name == "return")
    {
        if (Input.at(i)->Childs.size() > 0)
        {
            Back b = *this;
            b.Input = Input.at(i)->Childs;
            b.Get_Direct = true;
            b.Factory();
            Token *returnAddress = new Token(Output);
            returnAddress->getReg();
            Output += MOV + ESP->Name + FROM + EBP->Name + NL;
            Output += POP + EBP->Name + NL;
            Output += POP + returnAddress->Reg->Name + NL;
            Output += PUSH + string(DWORD) + b.Dest->GetAddress() + NL;
            Output += JMP + returnAddress->Reg->Name + NL + NL;
        }
    }
}

void Back::Handle_Variable_Initalization(int i)
{
    if (Input.at(i)->_INITTED == false && Input.at(i)->is(Variable) && Input.at(i)->is(Public))
    {
        Output += Input.at(i)->Name + DD + NL;
        Input.at(i)->_INITTED = true;
    }
}

void Back::Factory()
{
    if (IS_PUBLIC == 0)
    {
        Output += BSSSEGMENT;
    }
    for (int i = 0; i < Input.size(); i++)
    {
        Handle_Variable_Initalization(i);
    }
    if (IS_PUBLIC == 0)
    {
        Output += CODESEGMENT;
    }
    for (int i = 0; i < Input.size(); i++)
    {
        if (Input.at(i)->is(Used) == false)
        {
            continue;
        }
        //Handle_Usation(i);
        Handle_Type_Init(i);
        Handle_Function_Init(i);
        Handle_Call_Function(i);
        Handle_Operators(i);
        Handle_Arrays(i);
        Handle_Variables(i);
        Handle_Conditions(i);
        Handle_Returning(i);
    }
}


Back &Back::operator=(const Back& name)
{
    Output = name.Output;
    Input = name.Input;
    Dest = name.Dest;
    Source = name.Source;
    Layer = name.Layer;
    Cheat = name.Cheat;
    IS_PUBLIC = name.IS_PUBLIC;
    return *this;
}