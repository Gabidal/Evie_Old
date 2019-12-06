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
    // a = a + sum(b, c)
    for (auto t : T)
    {
        if (t->is(OPERATOR) && (t->Name != "="))
        {
            Optimize_Math(t->Parameters);
            if (GetAbsoluteDestination(t)->is(Used))
            {
                t->Flags |= Used;
				if (t->Childs.at(0)->is(Call))
				{
					t->Childs.at(0)->Flags |= Used;
					t->Childs.at(0)->daddy_Func->Flags |= Used;
				}
				else
				{
					Set_All_References(t->Childs.at(0)->Name, EnyFlag, Global);
				}
            }
        }
        if ((t->Name == "=") && t->Parameters.at(0)->is(Used))
        {
            t->Flags |= Used;
            if ((t->Childs.at(0)->is(Number) != true) && (t->Childs.at(0)->is(Call) != true))
            {
				if (t->Childs.at(0)->is(Private) || t->Childs.at(0)->is(Parameter))
				{
					Set_All_References(t->Childs.at(0)->Name, EnyFlag, t->Childs.at(0)->ParentFunc->Childs);
				}
				else if (t->Childs.at(0)->is(Member))
				{
					Set_All_References(t->Childs.at(0)->Name, EnyFlag, t->Childs.at(0)->ParentType->Childs);
				}
				else if (t->Childs.at(0)->is(Public))
				{
					Set_All_References(t->Childs.at(0)->Name, EnyFlag, Global);
				}
            }
			else if (t->Childs.at(0)->is(Call))
			{
				Set_All_References(t->Childs.at(0)->daddy_Func->Name, Function, Global);
				for (int i = 0; i < t->Childs.at(0)->Parameters.size(); i++)
				{
					if (t->Childs.at(0)->Parameters.at(i)->is(Private) || t->Childs.at(0)->Parameters.at(i)->is(Parameter))
					{
						Set_All_References(t->Childs.at(0)->Parameters.at(i)->Name, EnyFlag, t->Childs.at(0)->Parameters.at(i)->ParentFunc->Childs);
					}
					else if (t->Childs.at(0)->is(Member))
					{
						Set_All_References(t->Childs.at(0)->Parameters.at(i)->Name, EnyFlag, t->Childs.at(0)->Parameters.at(i)->ParentType->Childs);
					}
					else if (t->Childs.at(0)->is(Public))
					{
						Set_All_References(t->Childs.at(0)->Parameters.at(i)->Name, EnyFlag, Global);
					}
				}
				t->Childs.at(0)->Flags |= Used;
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

void Optimizer::fix_All(Token* t, vector<Token*>& T)
{
	for (Token* u : T)
	{
		if (u->Childs.size() > 0)
		{
			fix_All(t, u->Childs);
		}
		if (u->Parameters.size() > 0)
		{
			fix_All(t, u->Parameters);
		}
		if ((u->Name == t->Name) && (u->Flags == t->Flags))
		{
			u->fixed_Location = true;
			u->StackOffset = t->StackOffset;
		}
	}
}

int Optimizer::Find(int Flag, vector<Token*>* T)
{
	for (Token* t : *T)
	{
		if (t->Childs.size() > 0)
		{
			return Find(Flag, &t->Childs);
		}
		else if (t->is(OPERATOR))
		{
			return Find(Flag, &t->Parameters);
		}
		else if (t->Any(Flag))
		{
			return 1;
		}
	}
	return -1;
}

void Optimizer::Optimize_Variables(int i)
{
    if (Input.at(i)->is(Variable) && Priority_For_Return)
    {
        if (Input.at(i)->is(Member))
        {
			if ((Input.at(i)->ParentFunc != nullptr))
			{
				Set_All_References(Input.at(i)->Name, (Variable | Member), Input.at(i)->ParentFunc->Childs);
				Set_All_References(Input.at(i)->Fetcher->Name, (NotOriginal), Input.at(i)->ParentFunc->Childs);
			}
			if ((Input.at(i)->ParentType != nullptr))
			{
				Set_All_References(Input.at(i)->Name, (Variable | Member), Input.at(i)->ParentType->Childs);
				Set_All_References(Input.at(i)->Fetcher->Name, (NotOriginal), Input.at(i)->ParentType->Childs);
			}
			if ((Input.at(i)->ParentType == nullptr) && (Input.at(i)->ParentFunc == nullptr))
			{
				Set_All_References(Input.at(i)->Name, (Variable | Member), Global);
				Set_All_References(Input.at(i)->Fetcher->Name, (NotOriginal), Global);
			}
        }
        else if ((Input.at(i)->Offsetter != 0) && Input.at(i)->is(Array))
        {
			if ((Input.at(i)->ParentFunc != nullptr))
			{
				Set_All_References(Input.at(i)->Name, (Variable | Array), Input.at(i)->ParentFunc->Childs);
			}
			if ((Input.at(i)->ParentType != nullptr))
			{
				Set_All_References(Input.at(i)->Name, (Variable | Array), Input.at(i)->ParentType->Childs);
			}
			if ((Input.at(i)->ParentType == nullptr) && (Input.at(i)->ParentFunc == nullptr))
			{
				Set_All_References(Input.at(i)->Name, (Variable | Array), Global);
			}
        }
		else if (Input.at(i)->is(Variable))
		{
			if ((Input.at(i)->ParentFunc != nullptr) && (Input.at(i)->is(Private)))
			{
				Set_All_References(Input.at(i)->Name, (Variable), Input.at(i)->ParentFunc->Childs);
			}
			if ((Input.at(i)->ParentType != nullptr) && (Input.at(i)->is(Member)))
			{
				Set_All_References(Input.at(i)->Name, (Variable), Input.at(i)->ParentType->Childs);
			}
			if ((Input.at(i)->is(Public)) || (Input.at(i)->ParentType == nullptr) && (Input.at(i)->ParentFunc == nullptr))
			{
				Set_All_References(Input.at(i)->Name, (Variable), Global);
			}
		}
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
        for (int j = 0; j < int(Input.at(i)->Callations->size()); j++)
        {
            /*if (Input.at(i)->Callations->at(j)->ParentFunc != nullptr)
            {
                if (Input.at(i)->Callations->at(j)->ParentFunc->is(Used))
                {
                    //if function callation is inside another function that is called
                    Input.at(i)->Flags |= Used;
                    Optimize_Sys_Functions(Input.at(i));
                    break;
                }
            }*/
            if ((Input.at(i)->Callations->at(j)->ParentType == nullptr) && (Input.at(i)->Callations->at(j)->ParentFunc == nullptr))
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
						for (int k = 0; k < Input.at(k)->Callations->size(); k++)
							Input.at(i)->Callations->at(k)->Flags |= Used;
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

void Optimizer::Optimize_Function_Local_Variables_reservation(int i)
{
	if (Input.at(i)->is(Function) && (Input.at(i)->is(Used)))
	{
		int fixing = 0;
		for (Token *t : Input.at(i)->Childs)
		{
			if ((t->is(Used) != true) && t->Any(Variable | NotOriginal | Ptr))
			{
				fixing -= t->Size;
			}
			else if (t->is(Used) && t->Any(Variable | NotOriginal | Ptr) && (t->fixed_Location == false))
			{
				t->StackOffset += fixing;
				t->fixed_Location = true;
				if (t->is(Private))
					fix_All(t, t->ParentFunc->Childs);
				else if (t->is(Member))
					fix_All(t, t->ParentType->Childs);
			}
		}
	}
}

void Optimizer::Optimize_Function_Calls(int i)
{
    /*if (Input.at(i)->is(Call))
    {
		if ((Input.at(i)->ParentFunc == nullptr) || Input.at(i)->ParentFunc->is(Used))
		{
			Input.at(i)->Flags |= Used;
		}
    }*/
}

void Optimizer::Optimize_Types(int i)
{
    if (Input.at(i)->is(TypE) && (Input.at(i)->Callations->size() > 0))
    {
        for (Token *t : *Input.at(i)->Callations)
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
		//Find if this condition is even useful for the user.
		if (Find(Used, &Input.at(i)->Childs) != -1)
		{
			Input.at(i)->Flags |= Used;
			for (int j = 0; j < Input.at(i)->Parameters.size(); j++)
			{
				Input.at(i)->Parameters.at(j)->Flags |= Used;
			}
			Optimizer o = *this;
			o.Input = (Input.at(i)->Childs);
			o.Factory();
		}
    }
}

void Optimizer::Factory()
{
    for (int i = 0; i < int(Input.size()); i++)
    {
        Optimize_Functions(i);
		Optimize_Function_Local_Variables_reservation(i);
        Optimize_Function_Calls(i);
        Optimize_Types(i);
        Optimize_Variables(i);
        GetReturningToken(i);
        Optimize_Conditions(i);
    }
    Optimize_Math(Input);
}