#include "../../H/Parser/Optimizer.h"

#define EnyFlag INT32_MAX

int Optimizer::Find(string name, int flag, vector<Token*> list)
{
    for (int i = 0; i < int(list.size()); i++)
    {
        if (list.at(i)->Name == name && list.at(i)->is(flag))
        {
            return i;
        }
    }
    return -1;
}

Token *Optimizer::GetAbsoluteDestination(Token *t)
{
    if (t->Parameters.size() > 0)
    {
        return GetAbsoluteDestination(t->Parameters.at(0));
    }
    else
    {
        return t;
    }
    return nullptr;
}

int Optimizer::GetSecondaryDestination(vector<Token*> t)
{
    for (int i = 0; i < int(t.size()); i++)
    {
        if (t.at(i)->Name == "=")
        {
            return 1;
        }
        else if (t.at(i)->Parameters.size() > 0)
        {
            return GetSecondaryDestination(t.at(i)->Parameters);
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

void Optimizer::Optimize_Math(vector<Token*> &T)
{
    // <<a = b> + a>
    for (auto t : T)
    {
        if (t->is(OPERATOR) && (t->Name != "="))
        {
            Optimize_Math(t->Parameters);
            if (GetAbsoluteDestination(t)->is(Used))
            {
                t->Flags |= Used;
                Set_All_References(t->Childs.at(0)->Name, EnyFlag, Global);
            }
        }
        if ((t->Name == "=") && t->Parameters.at(0)->is(Used))
        {
            t->Flags |= Used;
            if (t->Childs.at(0)->is(Number) != true)
            {
                Set_All_References(t->Childs.at(0)->Name, EnyFlag, Global);
            }
        }
        if ((t->Name == "=") && t->Childs.at(0)->is(Call) && (t->Parameters.at(0)->is(Used) != true))
        {
            //cancel the math and make it a callation only.
            *t = *t->Childs.at(0);
        }
        
    }
}

void Optimizer::Set_All_References(string name, int flags, vector<Token*> &T)
{
    for (auto t : T)
    {
        if (t->Childs.size() > 0)
        {
            Set_All_References(name, flags, t->Childs);
        }
        if (t->Parameters.size() > 0)
        {
            Set_All_References(name, flags, t->Parameters);
        }
        if (t->Name == name && t->Any(flags))
        {
            t->Flags |= Used;
        }
    }
}

void Optimizer::Optimize_Variables(int i)
{
    if (Input.at(i)->is(Variable) && Priority_For_Return)
    {
        if (Input.at(i)->is(Member))
        {
            Set_All_References(Input.at(i)->Name, (Variable | Member), Global);
        }
        if ((Input.at(i)->Offsetter != 0) && Input.at(i)->is(Array))
        {
            Set_All_References(Input.at(i)->Name, (Variable | Array), Global);
        }
        if (Input.at(i)->is(Variable))
            Set_All_References(Input.at(i)->Name, Variable, Global);
    }
    if (Input.at(i)->is(Number) && Priority_For_Return)
    {
        Input.at(i)->Flags |= Used;
    }
}

void Optimizer::GetReturningToken(int i)
{
    if (Input.at(i)->Name == "return")
    {
        Input.at(i)->Flags |= Used;
        Optimizer o = *this;
        o.Input = (Input.at(i)->Childs);
        o.Priority_For_Return = true;
        o.Factory();
        o.Priority_For_Return = false; // for safe keeping
    }
}

void Optimizer::Optimize_Sys_Functions(Token * t)
{
    if (t->Name == "Malloc")
    {
        Linux l;
        t->output += l.Malloc();
    }
    else if (t->Name == "raw_print")
    {
        Linux l;
        t->output += l.Raw_Print();
    }
    else if (t->Name == "raw_in")
    {
        Linux l;
        t->output += l.Raw_In();
    }
}

void Optimizer::Optimize_Functions(int i)
{
    if (Input.at(i)->is(Function) && Input.at(i)->CallationAmount > 0)
    {
        for (int j = 0; j < int(Input.at(i)->Callations.size()); j++)
        {
            if (Input.at(i)->Callations.at(j)->ParentFunc != nullptr)
            {
                if (Input.at(i)->Callations.at(j)->ParentFunc->is(Used))
                {
                    //if function callation is inside another function that is called
                    Input.at(i)->Flags |= Used;
                    Optimize_Sys_Functions(Input.at(i));
                    break;
                }
            }
            else if (Input.at(i)->Callations.at(j)->ParentType == nullptr)
            {
                //this functon callation is public
                Input.at(i)->Flags |= Used;
                Optimize_Sys_Functions(Input.at(i));
                break;
            }
            for (auto t : Input.at(i)->Childs)
            {
                //if function is using global variables things change a bit!
                if (t->is(OPERATOR))
                {
                    if (GetAbsoluteDestination(t)->is(Used) && GetAbsoluteDestination(t)->is(Public))
                    {
                        Input.at(i)->Flags |= Used;
                        Optimize_Sys_Functions(Input.at(i));
                        break;
                    }
                }
                
                if (t->is(Used) && t->is(Public))
                {
                    Input.at(i)->Flags |= Used;
                    Optimize_Sys_Functions(Input.at(i));
                    break;
                }
            }
        }
        Optimizer o = *this;
        o.Input = (Input.at(i)->Childs);
        o.Factory();
    }
}

void Optimizer::Optimize_Function_Calls(int i)
{
    if (Input.at(i)->is(Call))
    {
        Input.at(i)->Flags |= Used;
    }
}

void Optimizer::Optimize_Types(int i)
{
    if (Input.at(i)->is(TypE) && (Input.at(i)->Callations.size() > 0))
    {
        for (Token *t : Input.at(i)->Callations)
        {
            if (t->ParentFunc != 0)
            {
                if (t->ParentFunc->is(Used))
                {
                    Input.at(i)->Flags |= Used;
                }
            }
            else if (t->ParentType != 0)
            {
                if (t->ParentType->is(Used))
                {
                    Input.at(i)->Flags |= Used;
                }
            }
        }
    }
}

void Optimizer::Optimize_Condition_Variebles(Token *&T)
{
    if (T->is(OPERATOR))
    {
        Optimize_Condition_Variebles(T->Parameters.at(0));
        Optimize_Condition_Variebles(T->Childs.at(0));
        T->Flags |= Used;
    }
    else if (T->is(Number) != true)
    {
        //enything than number is usedizided
        Set_All_References(T->Name, EnyFlag, Global);
    }
}

void Optimizer::Optimize_Conditions(int i)
{
    if (Input.at(i)->is(If) || Input.at(i)->is(Else) || Input.at(i)->is(While))
    {
        int j;
        if ((j = Find("=", OPERATOR, Input.at(i)->Childs)) != -1)
        {
            if (Input.at(i)->Childs.at(j)->is(Used))
            {
                Input.at(i)->Flags |= Used;
                if (Input.at(i)->Parameters.size() > 0)
                {
                    Optimize_Condition_Variebles(Input.at(i)->Parameters.at(0));
                }
            }
        }
        else if ((j = GetSecondaryDestination(Input.at(i)->Childs)) != -1)
        {
            Set_All_References(Input.at(i)->Name, EnyFlag, Global);
        }
        else if ((j = Find("return", Returning, Input.at(i)->Childs)) != -1)
        {
            Input.at(i)->Flags |= Used;
            if (Input.at(i)->Parameters.size() > 0)
            {
                Optimize_Condition_Variebles(Input.at(i)->Parameters.at(0));
            }
        }
        Optimizer o = *this;
        o.Input = (Input.at(i)->Childs);
        o.Factory();
    }
}

void Optimizer::Factory()
{
    for (int i = 0; i < int(Input.size()); i++)
    {
        Optimize_Functions(i);
        Optimize_Function_Calls(i);
        Optimize_Types(i);
        Optimize_Variables(i);
        GetReturningToken(i);
        Optimize_Conditions(i);
    }
    Optimize_Math(Input);
}