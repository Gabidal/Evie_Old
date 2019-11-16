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
            b.Input = Input.at(i)->Parameters;
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
    if (Input.at(i)->is(Variable) || Input.at(i)->is(Ptr))
    {
        if (Priority_For_Parametering)
        {
            if (Input.at(i)->is(Ptr))
            {
                Output += PUSH + Input.at(i)->GetAddress() + NL;
            }
            else
            {
                Output += PUSH + Input.at(i)->InitVariable() + NL;
            }
        }
    }
}

void Back::Handle_Function_Init(int i)
{
    if (Input.at(i)->is(Function) && Input.at(i)->is(Call) == false)
    {
        //134479964
        Input.at(i)->InitFunction();
        Back b = *this;
        b.Input = Input.at(i)->Childs;
        StackFrame stack(Output, true);
        b.Factory();
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
            b.Factory();
        }
        if (Functions.size() > 0)
        {
            b.Input = Functions;
            b.Factory();
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
    }
}

void Back::Handle_Arrays(int i)
{

}

void Back::Factory()
{
    for (int i = 0; i < Input.size(); i++)
    {
        /*if (Input.at(i)->is(Used) == false)
        {
            continue;
        }*/
        //Handle_Usation(i);
        Handle_Type_Init(i);
        Handle_Function_Init(i);
        Handle_Call_Function(i);
        Handle_Operators(i);
        Handle_Arrays(i);
        Handle_Variables(i);
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
    return *this;
}