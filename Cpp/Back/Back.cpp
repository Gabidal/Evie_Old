#include "../../H/Back/Back.h"

void Back::Set_All_References(string name, int flags, vector<Token*>& T)
{
	for (auto* t : T)
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
			t->Passing_String = true;;
		}
	}
}

void Back::Handle_Operators(int i)
{
    if (Input.at(i)->is(OPERATOR))
    {
        if (Input.at(i)->Parameters.at(0)->is(Variable) || Input.at(i)->Parameters.at(0)->is(Ptr))
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
            this->Deep_Math = b.Deep_Math;
            this->Dest = b.Dest;
            this->Cheat = b.Cheat;
        }
        if (Dest->is(Returning) && Input.at(i)->Childs.at(0)->is(Returning))
        {
            Double_Callation = true;
        }
        if (Input.at(i)->Childs.at(0)->is(Variable) || Input.at(i)->Childs.at(0)->is(Number) || Input.at(i)->Childs.at(0)->is(Ptr) || Input.at(i)->Childs.at(0)->is(String))
        {
            Source = Input.at(i)->Childs.at(0);
        }
        else
        {
            Back b = *this;
            b.Double_Callation = this->Double_Callation;
            b.Input = Input.at(i)->Childs;
            b.Layer++;
            b.Factory();
            b.Layer--;
            this->Deep_Math = b.Deep_Math;
            this->Source = b.Source;
            this->Cheat = b.Cheat;
        }
        if (Dest->is(Returning) && Input.at(i)->Childs.at(0)->is(Returning))
        {
            Double_Callation = false;
            Dest->Reg = EBX;
            EBX->Link(Dest);
        }
        string reg = "";
		if (Input.at(i)->repz != nullptr)
		{
			Input.at(i)->Parameters.at(0)->repz = Input.at(i)->repz;
            Dest->repz = Input.at(i)->repz;
		}
        if (Input.at(i)->Name == "+")
        {
            reg = Dest->SUM(Source, Cheat);
        }
        else if (Input.at(i)->Name == "-")
        {
            reg = Dest->SUBSTRACT(Source, Cheat);
        }
        else if (Input.at(i)->Name == "*")
        {
            reg = Dest->MULTIPLY(Source);
        }
        else if (Input.at(i)->Name == "/")
        {
            reg = Dest->DIVIDE(Source);
        }
        if (Layer == 0)
        {
            if (Deep_Math == false)
            {
                if (Cheat != nullptr)
                {
                    Cheat->MOVE(Dest);
                    Cheat = nullptr;
                }
                else
                {
                    Dest->MOVE(Source);
                }
                reg = "";
                if (Dest->Passing_String)
                {
                    if (Dest->is(Private))
                    {
                        Set_All_References(Dest->Name, Ptr, Dest->ParentFunc->Childs);
                    }
                    else
                    {
                        Set_All_References(Dest->Name, Ptr, *Dest->Input);
                    }
                }
                else if (Source->is(Array))
                {
                    if (Dest->is(Private))
                    {
                        Set_All_References(Dest->Name, INT32_MAX, Dest->ParentFunc->Childs);
                    }
                    else
                    {
                        Set_All_References(Dest->Name, INT32_MAX, *Dest->Input);
                    }
                }
            }
            else
            {
                Deep_Math_Done = true;
                Output += MOV + Cheat->GetAddress() + FROM + Dest->Reg->Name + NL;
                Dest->Reg->Link(Cheat);
            }
        }
        else if (Input.at(i)->Name == "==" || Input.at(i)->Name == ">=" || Input.at(i)->Name == "<=" || Input.at(i)->Name == ">" || Input.at(i)->Name == "<" || Input.at(i)->Name == "!=" || Input.at(i)->Name == "!>" || Input.at(i)->Name == "!<")
        {
            Dest->COMPARE(Source);
        }
        else if (Layer != 0)
        {
            if (Cheat != nullptr)
            {
                //the math operation is more deep than 2 operations
                Deep_Math = true;
            }
            else
            {
                Cheat = Dest;
                Dest = Source;
            }
        }
        
        if ((reg.size() > 0) && (Layer == 0))
        {
			string resulter = Dest->Name;
			if (Input.at(i)->Name == "+" || Input.at(i)->Name == "-")
			{
				if (Source->is(Number) && (Cheat->Name == Dest->Name))
				{
					return;
				}
				if (Dest->is(Number) && (Cheat->Name == Source->Name))
				{
					return;
				}
			}
			if (Dest->tmp != nullptr)
			{
                if (Cheat->tmp != nullptr)
                {
                    Cheat->tmp->MOVE(Dest->tmp);
                }
                else
                {
                    Cheat->MOVE(Dest->tmp);
                }
			}
            else if ((Cheat != nullptr) && (Deep_Math == false))
            {
                Cheat->MOVE(Dest);
            }
			Dest->Reg->Link(Dest);
        }
        if (Deep_Math_Done)
        {
            Deep_Math = false;
            Deep_Math_Done = false;
            Cheat = nullptr;
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
				Output += COMMENT + "Pushing pointter " + NL;
				Output += PUSH + string(DWORD) + Input.at(i)->GetAddress() + NL;
            }
            else if (Input.at(i)->is(Variable))
            {
				Output += COMMENT + "Pushing Variable " + NL;
				if (Input.at(i)->Reg == nullptr)
				{
					Output += PUSH + string(DWORD) + Input.at(i)->GetAddress() + NL;
				}
				else
				{
					Output += PUSH + Input.at(i)->InitVariable() + NL;
				}
            }
            else
            {
                Output += PUSH + string(DWORD) + Input.at(i)->Name + NL;
            }
        }
        if (Get_Direct)
        {
            Dest = Input.at(i);
        }
        if (Input.at(i)->is(Member))
        {
            
        }
        
    }
}

vector<Token*> *seen = new vector<Token*>();
int ret = 0;
int Get_Amount(vector<Token*> list, int flag)
{
    for (Token *t : list)
    {
        if (t->is(Used) != true)
        {
            continue;
        }
        if ((t->Childs.size() > 0) && (t->is(OPERATOR) != true) && (t->Name != "return") && (t->Origin == nullptr))
        {
            Get_Amount(t->Childs, flag);
        }
        else if (t->Any(flag))
        {
            for (int i = 0; i < int(seen->size()); i++)
            {
                if (seen->at(i) == t)
                {
                    goto ___skip;
                }
            }
            ret += t->Size;
            seen->push_back(t);
        }
        ___skip:;
    }
    return ret;
}

void Back::Handle_Function_Init(int i)
{
    if (Input.at(i)->is(Function) && (Input.at(i)->is(Call) == false) && (Input.at(i)->Childs.size() > 0))
    {
		Output += COMMENT + "Function " + Input.at(i)->Name + NL;
		Input.at(i)->Flags |= Real;
        Input.at(i)->InitFunction();
        Back b = *this;
        b.Input = Input.at(i)->Childs;
		if ((b.Input.size() - 1) < 0)
		{
			Output += RET + NL;
		}
		else
		{
			StackFrame stack(Output, true);
			int care = Variable | Ptr | NotOriginal | Array;
			if (Get_Amount(Input.at(i)->Childs, care) > 0)
			{
				Output += COMMENT + "Making space for local variables " + NL;
				Output += SUB + ESP->Name + FROM + to_string(Get_Amount(Input.at(i)->Childs, care)) + NL + NL;
			}
			b.IS_PUBLIC++;
			b.Factory();
			b.IS_PUBLIC--;
		}
    }
}

void Back::Handle_Type_Init(int i)
{
    if (Input.at(i)->is(TypE) && Input.at(i)->is(__NEW) == false)
    {
        Back b = *this;
        vector<Token*> vars;
        vector<Token*> functions;
        for (int j = 0; j < int(Input.at(i)->Childs.size()); j++)
        {
            if (Input.at(i)->Childs.at(j)->is(Function))
            {
                functions.push_back(Input.at(i)->Childs.at(j));
            }
            else
            {
                vars.push_back(Input.at(i)->Childs.at(j));
            }
        }
		Input.at(i)->Flags |= Real;
        if (vars.size() > 0)
        {
			Token* initter = new Token(Output, &Input);
			initter->Name = "Init_Variables_Of_" + Input.at(i)->Name;
			initter->Flags |= Function;
			initter->Flags |= Returning;
			Token* THIS = new Token(Output, &Input);
			THIS->Flags |= Variable;
			THIS->Size = 4;
			THIS->Name = "this";
			initter->addParameter(THIS);
			initter->Childs = vars;
			b.Input.push_back(initter);
            b.IS_PUBLIC++;
            b.Factory();
            b.IS_PUBLIC--;
        }
        if (functions.size() > 0)
        {
            b.Input = functions;
            b.IS_PUBLIC++;
            b.Factory();
            b.IS_PUBLIC--;
        }
    }
}

void Back::Handle_New(int i)
{
    if ((i - 1) < 0)
    {
        return;
    }
    
    if (Input.at(i - 1)->is(__NEW) && Input.at(i)->is(NotOriginal))
    {
		Output += COMMENT + "Allocating new memory space for new type " + NL;
		Output += PUSH + to_string(Input.at(i)->Size) + NL;
		Output += CALL + "malloc" + NL;
		Input.at(i)->Reg = EAX;
		EAX->Link(Input.at(i));
		Input.at(i)->MOVE(Input.at(i));
    }
}

void Back::Handle_Call_Function(int i)
{
    if (Input.at(i)->is(Call))
    {
        if (Double_Callation)
        {
            //this means the both of Dest as Source is a function
            //so we need to save the previus return value into EBX
            Output += NL + COMMENT + "Saving previus return value into EBX" + NL;
            Output += MOV + EBX->Name + FROM + EAX->Name + NL + NL;
        }
		Output += COMMENT + "Calling " + Input.at(i)->Name + NL;
        if (Input.at(i)->Parameters.size() > 0)
        {
            Back b = *this;
            b.Input = Input.at(i)->Parameters;
            reverse(b.Input.begin(), b.Input.end());
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
    for (int i = 0; i < int(list.size()); i++)
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
	if (Input.at(i)->Parameters.at(0)->is(OPERATOR) != true)
	{
		return;
	}
    string conditionJump = "";
	string sourceJMP = "";
    if (Find("==", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JNE ;
		sourceJMP = "==";
    }
    else if (Find("!=", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JE ;
		sourceJMP = "!=";
    }
    else if (Find(">=", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JNGE ;
		sourceJMP = ">=";
    }
    else if (Find("<=", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JNLE ;
		sourceJMP = "<=";
    }
    else if (Find("<", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JGE ;
		sourceJMP = "<";
    }
    else if (Find(">", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JLE ;
		sourceJMP = ">";
    }
    else if (Find("!<", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JGE ;
		sourceJMP = "!<";
    }
    else if (Find("!>", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JLE ;
		sourceJMP = "!>";
    }
    string destination = "";
    int ID = 0;
    string endd = "";
    if (Input.at(i)->is(Successour) && Input.at(i)->Former->SuccessorToken.at(0)->is(Used))
    {
        destination = Input.at(i)->Former->SuccessorToken.at(0)->getFullName();
        ID = Input.at(i)->Former->SuccessorToken.at(0)->ID;
    }
    else if (Input.at(i)->SuccessorToken.size() > 0 && Input.at(i)->SuccessorToken.at(0)->is(Used))
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
	Output += COMMENT + "Jumping source: \'" + sourceJMP + "\'" + NL;
    Output += conditionJump + destination + to_string(ID) + endd + NL;
}

void Back::Handle_Conditions(int i)
{
    if (Input.at(i)->is(If) || Input.at(i)->is(Else) || Input.at(i)->is(While))
    {
        Back b = *this;
		if ((Input.at(i)->is(Else) && Input.at(i)->is(If)))
		{
			Output += JMP + Input.at(i)->Former->SuccessorToken.at(Input.at(i)->Former->SuccessorToken.size() - 1)->getFullName() + to_string(Input.at(i)->Former->SuccessorToken.at(Input.at(i)->Former->SuccessorToken.size() - 1)->ID) + NL;
		}
		else if ((Input.at(i)->is(Else)))
		{
			Output += JMP + Input.at(i)->getFullName() + to_string(Input.at(i)->ID) + END(i) + NL + NL;
		}
        Output += LABEL(Input.at(i)->getFullName() + to_string(Input.at(i)->ID));

		Input.at(i)->Flags |= Real;
        //if
        if (Input.at(i)->Parameters.size() > 0)
        {
			for (Token * t : Input.at(i)->Parameters)
			{
				b.Input.clear();
				b.Input.push_back(t);
				b.Factory();
				Handle_Jumps(i);
			}
        }
        //( ...)
        if (Input.at(i)->Childs.size() > 0)
        {
            b.Input = Input.at(i)->Childs;
            b.Factory();
        }
        //while
        if (Input.at(i)->is(While) && (Input.at(i)->Childs.size() == 0))
        {
            //repz whiler.
            Input.at(i + 1)->repz = Input.at(i)->Parameters.at(0);
        }
        else if (Input.at(i)->Parameters.size() > 0 && Input.at(i)->is(While))
        {
            Output += JMP + Input.at(i)->getFullName() + to_string(Input.at(i)->ID) + NL + NL;
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
			Input.at(i)->Flags |= Real;
            Back b = *this;
            b.Input = Input.at(i)->Childs;
            b.Get_Direct = true;
            b.IS_PUBLIC++;
            b.Factory();
            b.IS_PUBLIC--;
            b.Dest->Flags |= Storer;
			Output += COMMENT + "Return " + b.Dest->Name + NL;
            b.Dest->Optimize_Register_Usage();
            if (b.Dest->is(Number))
            {
                Output += MOV + EAX->Name + FROM + b.Dest->Name + NL;
            }
			else if ((b.Dest->Reg == nullptr) || (b.Dest->Reg->Name == "null"))
			{
				Output += MOV + EAX->Name + FROM + DWORD + FRAME(b.Dest->getFullName()) + NL;
			}
			else if ((b.Dest->Reg != nullptr) && (b.Dest->Reg != EAX))
			{
				Output += MOV + EAX->Name + FROM + b.Dest->Reg->Name + NL;
			}
			Output += MOV + ESP->Name + FROM + EBP->Name + NL;
			Output += POP + EBP->Name + NL;
			Output += RET + NL + NL;
        }
    }
}

void Back::Handle_Variable_Initalization(int i)
{
    if ((Input.at(i)->_INITTED == false) && Input.at(i)->is(Variable) && Input.at(i)->is(Public) && Input.at(i)->is(Used))
    {
        Strings += Input.at(i)->Name + DD + NL;
        Input.at(i)->_INITTED = true;
    }
}

int String_Count = 0;
void Back::Handle_String_Initalization(vector<Token *> *&T)
{
	for (auto* t : *T)
	{
		if (t->Childs.size() > 0)
		{
			auto* k = &t->Childs;
			Handle_String_Initalization(k);
		}
		if (t->Parameters.size() > 0)
		{
			auto* k = &t->Parameters;
			Handle_String_Initalization(k);
		}
		if (t->is(String))
		{
			t->StringName = "S" + to_string(String_Count);
			Strings += t->StringName + NL + DB + '\"' + t->Name + '\"' + NL;
			String_Count++;
		}
	}
}

void Back::Factory()
{
    for (int i = 0; i < int(Input.size()); i++)
    {
		/*if (Input.at(i)->is(Used) == false)
        {
            continue;
        }*/
		if (Input.at(i)->is(Real))
		{
			//already written into asm
			continue;
		}
        Handle_Type_Init(i);
        Handle_Function_Init(i);
        Handle_Call_Function(i);
        Handle_Operators(i);
        Handle_Arrays(i);
        Handle_Variables(i);
        Handle_Conditions(i);
        Handle_Returning(i);
        Handle_New(i);

		//it is written
		Input.at(i)->Flags |= Real;
    }
}

void Back::Factory_Variables()
{
	if (IS_PUBLIC == 0)
	{
		Strings += BSSSEGMENT;
		for (int i = 0; i < int(Input.size()); i++)
		{
			Handle_Variable_Initalization(i);
		}
		Strings += DATASEGMENT;
		auto* k = &Input;
		Handle_String_Initalization(k);
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