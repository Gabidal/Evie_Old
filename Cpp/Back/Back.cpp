#include "../../H/Back/Back.h"

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
			string resulter = Dest->Name;
            Dest = Cheat;
            Dest->Reg = registers[reg];
            if (Dest->is(Member))
            {
				Output += COMMENT + "Saving result of " + resulter + " into " + Dest->Name + " from " + Dest->Fetcher->Name + NL;
                Output += MOV + FRAME(Dest->Fetcher->InitVariable() + OFFSET + to_string(Dest->StackOffset - 4)) + FROM + Dest->Reg->Name + NL + NL;
            }
            else
            {
				Output += COMMENT + "Saving result of " + resulter + " into " + Dest->Name + NL;
                Output += MOV + Dest->GetAddress() + FROM + Dest->Reg->Name + NL + NL;
            }
			Dest->Reg->Link(Dest);
			Dest->Reg->Apply(Dest, &Input);
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
                Output += PUSH + Input.at(i)->GetAddress() + NL;
            }
            else if (Input.at(i)->is(Variable))
            {
				Output += COMMENT + "Pushing Variable " + NL;
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
        if ((t->Childs.size() > 0) && (t->is(OPERATOR) != true) && (t->Name != "return"))
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
    if (Input.at(i)->is(Function) && Input.at(i)->is(Call) == false && Input.at(i)->Childs.size() > 0)
    {
		Output += COMMENT + "Function " + Input.at(i)->Name + NL;
		Input.at(i)->Flags |= Real;
        Input.at(i)->InitFunction();
        Back b = *this;
        b.Input = Input.at(i)->Childs;
        StackFrame stack(Output, true);
        int care = Variable | Ptr | NotOriginal | Array;
		Output += COMMENT + "Making space for local variables " + NL;
        Output += SUB + ESP->Name + FROM + to_string(Get_Amount(Input.at(i)->Childs, care)) + NL + NL;
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
        Linux l;
		Output += COMMENT + "Allocating new memory space for new type " + NL;
        Output += l.Call_Malloc(Input.at(i));

    }
}

void Back::Handle_Call_Function(int i)
{
    if (Input.at(i)->is(Call))
    {
		Output += COMMENT + "Calling " + Input.at(i)->Name + NL;
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
        conditionJump = JGE ;
    }
    if (Find(">", OPERATOR, Input.at(i)->Parameters) != -1)
    {
        conditionJump = JLE ;
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
    
    Output += conditionJump + destination + to_string(ID) + endd + NL;
}

void Back::Handle_Conditions(int i)
{
    if (Input.at(i)->is(If) || Input.at(i)->is(Else))
    {
        Back b = *this;
        if ((Input.at(i)->is(Else) && Input.at(i)->is(If)))
            Output += JMP + Input.at(i)->Former->SuccessorToken.at(Input.at(i)->Former->SuccessorToken.size() - 1)->getFullName() + to_string(Input.at(i)->Former->SuccessorToken.at(Input.at(i)->Former->SuccessorToken.size() - 1)->ID) + NL;
        else if ((Input.at(i)->is(Else)))
            Output += JMP + Input.at(i)->getFullName() + to_string(Input.at(i)->ID) + END(i) + NL + NL;
        Output += LABEL(Input.at(i)->getFullName() + to_string(Input.at(i)->ID));

		Input.at(i)->Flags |= Real;
        //if
        if (Input.at(i)->Parameters.size() > 0)
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
            b.Dest->InitVariable();
			Output += COMMENT + "Return " + b.Dest->Name + NL;
            Token *returnAddress = new Token(Output, &Input);
			returnAddress->Name = "Returning address";
            returnAddress->getReg();
            Output += MOV + ESP->Name + FROM + EBP->Name + NL;
            Output += POP + EBP->Name + NL;
            Output += POP + returnAddress->Reg->Name + NL;
            Output += PUSH + b.Dest->Reg->Name + NL;
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
        for (int i = 0; i < int(Input.size()); i++)
        {
            Handle_Variable_Initalization(i);
        }
    }
    if (IS_PUBLIC == 0)
    {
        Output += CODESEGMENT;
    }
    for (int i = 0; i < int(Input.size()); i++)
    {
        if (Input.at(i)->is(Used) == false)
        {
            continue;
        }
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