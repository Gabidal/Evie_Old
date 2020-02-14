#include "../../H/Emulator/Emulator.h"

/*
int Emulator::Factory()
{
	for (Token* t : Input)
	{
		if (Has(t, "return"))
		{
			return Next_Op_Picker(*t);
		}
		else
		{
			Next_Op_Picker(*t);
		}
	}
}

int Emulator::Start_Simulation(int start)
{
	return Next_Op_Picker(*Input.at(start));
}

int Emulator::Next_Op_Picker(Token &T)
{


	if (T.is(Function))
	{
		if (Simulate_Function_Return_Value(&T))
		{
			Emulator E = *this;
			E.Input = T.Childs;
			E.Layer = 0;
			E.Clear_Log();
			if (T.Callations->size() > 0)
			{
				E.Sync_Parameters(T.Parameters);
				int result = E.Factory();
				this->Register_Turn = E.Register_Turn;
				if (T.is(Returning))
				{
					return result;
				}
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return T.Value;
		}
	}
	else if (T.is(Call))
	{
		if (Simulate_Importance(&T))
		{
			for (Token* t : T.Parameters)
			{
				if (t->is(Number))
				{
					Stack.push_back(atoi(t->Name.c_str()));
				}
				else
				{
					Stack.push_back(Find_From_Log(t)->Value);
				}
			}
			if (T.daddy_Func->Childs.size() > 0)
			{
				reverse(Stack.begin(), Stack.end());
				Emulator E = *this;
				E.Input.clear();
				E.Input.push_back(T.daddy_Func);
				//Original_Size = Log.size();
				int result = E.Factory();
				this->Register_Turn = E.Register_Turn;
				if (T.is(Returning))
				{
					return result;
				}
				reverse(Stack.begin(), Stack.end());
			}
			for (Token* t : T.Parameters)
			{
				Stack.pop_back();
			}
		}
	}
	else if (T.is(OPERATOR))
	{
		if ((Layer == 0) && (T.Parameters.at(0)->is(OPERATOR) || T.Childs.at(0)->is(OPERATOR)))
		{
			//Re-arrange the operation tokens.
			if (T.Semanticked == false)
			{
				Token* t = new Token(T);
				Semantic* S = new Semantic(t);
				T = S->Factory();
			}
		}
		if (T.Parameters.at(0)->is(Call))
		{
			Emulator e = *this;
			e.Double_Callation = this->Double_Callation;
			e.Input = T.Parameters;
			e.Layer++;
			int result = e.Factory();
			e.Layer--;
			this->Deep_Math = e.Deep_Math;
			if (T.Parameters.at(0)->is(Call))
			{
				Dest = new Token(TMP, &Input);
				Dest->Flags |= Number;
				Dest->Name = to_string(result);
			}
		}
		if (T.Parameters.at(0)->is(Variable) || T.Parameters.at(0)->is(Ptr))
		{
			Dest = T.Parameters.at(0);
		}
		else
		{
			Emulator b = *this;
			b.Input = T.Parameters;
			b.Layer++;
			b.Factory();
			b.Layer--;
			Register_Turn = b.Register_Turn;
			this->Log = b.Log;
			this->Deep_Math = b.Deep_Math;
			this->Dest = b.Dest;
			this->Cheat = b.Cheat;
		}
		if (Dest->is(Returning) && T.Childs.at(0)->is(Returning))
		{
			Double_Callation = true;
		}
		if (T.Childs.at(0)->is(Call))
		{
			Emulator e = *this;
			e.Double_Callation = this->Double_Callation;
			e.Input = T.Childs;
			e.Layer++;
			int result = e.Factory();
			e.Layer--;
			this->Deep_Math = e.Deep_Math;
			if (T.Childs.at(0)->is(Call))
			{
				//the callation hasnt been removed by optimization
				Source = new Token(TMP, &Input);
				Source->Flags |= Number;
				Source->Name = to_string(result);
			}
		}
		if (T.Childs.at(0)->is(Variable) || T.Childs.at(0)->is(Number) || T.Childs.at(0)->is(Ptr) || T.Childs.at(0)->is(String))
		{
			Source = T.Childs.at(0);
		}
		else
		{
			Emulator b = *this;
			b.Double_Callation = this->Double_Callation;
			b.Input = T.Childs;
			b.Layer++;
			b.Factory();
			b.Layer--;
			Register_Turn = b.Register_Turn;
			this->Log = b.Log;
			this->Deep_Math = b.Deep_Math;
			this->Source = b.Dest;
			this->Cheat = b.Cheat;
		}
		if (Dest->is(Returning) && T.Childs.at(0)->is(Returning))
		{
			Double_Callation = false;
			Dest->SReg = R2;
			R2->Link(Dest);
		}
		if (T.repz != nullptr)
		{
			T.Parameters.at(0)->repz = T.repz;
			Dest->repz = T.repz;
		}
		if (T.Name == "+")
		{
			Simulate_Add(Dest, Source);
		}
		else if (T.Name == "-")
		{
			Simulate_Sub(Dest, Source);
		}
		else if (T.Name == "*")
		{
			Simulate_Mul(Dest, Source);
		}
		else if (T.Name == "/")
		{
			Simulate_Div(Dest, Source);
		}
		if ((Layer == 0) && (Cheat != Dest))
		{
			if (Deep_Math == false)
			{
				if (Cheat != nullptr)
				{
					Simulate_Equ(Cheat, Dest);
					Cheat = nullptr;
				}
				else
				{
					Simulate_Equ(Dest, Source);
				}
				if (Dest->Passing_String)
				{
					if (Dest->is(Private))
					{
						//Set_All_References(Dest->Name, Ptr, Dest->ParentFunc->Childs);
					}
					else
					{
						//Set_All_References(Dest->Name, Ptr, *Dest->Input);
					}
				}
				else if (Source->is(Array))
				{
					if (Dest->is(Private))
					{
						//Set_All_References(Dest->Name, INT32_MAX, Dest->ParentFunc->Childs);
					}
					else
					{
						//Set_All_References(Dest->Name, INT32_MAX, *Dest->Input);
					}
				}
			}
			else
			{
				Deep_Math_Done = true;
				Simulate_Equ(Cheat, Dest);
			}
		}
		else if (T.Name == "==" || T.Name == ">=" || T.Name == "<=" || T.Name == ">" || T.Name == "<" || T.Name == "!=" || T.Name == "!>" || T.Name == "!<")
		{
			Unlock_Requem(&T);
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
				if (Find_From_Log(Dest) == nullptr)
				{
					Cheat = Dest;
				}
				else
				{
					Cheat = Find_From_Log(Dest);
				}
				if (Find_From_Log(Source) == nullptr)
				{
					Dest = Source;
				}
				else
				{
					Dest = Find_From_Log(Source);
				}
			}
		}

		if ((Layer == 0))
		{
			string resulter = Dest->Name;
			if (T.Name == "+" || T.Name == "-")
			{
				if (Source->is(Number) && (Cheat->Name == Dest->Name))
				{
					return 0;
				}
				if (Dest->is(Number) && (Cheat->Name == Source->Name))
				{
					return 0;
				}
			}
			if ((Cheat != nullptr) && (Deep_Math == false))
			{
				Simulate_Equ(Cheat, Dest);
			}
		}
		if (Deep_Math_Done)
		{
			Deep_Math = false;
			Deep_Math_Done = false;
			Cheat = nullptr;
		}
	}
	else if (T.is(If) || (T.is(Else) && T.is(If)))
	{
		if (Unlock_Requem(T.Parameters.at(0)))
		{
			Emulator E = *this;
			E.Input = T.Childs;
			int result = E.Factory();
			this->Register_Turn = E.Register_Turn;
			if (Return_Inside_If(T.Childs))
			{
				return result;
			}
		}
	}
	else if (T.is(Else) && (Unlock_Requem(T.Former->Parameters.at(0)) == false))
	{
		Emulator E = *this;
		E.Input = T.Childs;
		int result = E.Factory();
		this->Register_Turn = E.Register_Turn;
		if (Return_Inside_If(T.Childs))
		{
			return result;
		}
	}
	else if (T.is(While))
	{
		for (;Unlock_Requem(T.Parameters.at(0)) == false;)
		{
			Emulator E = *this;
			E.Input = T.Childs;
			int result = E.Factory();
			this->Register_Turn = E.Register_Turn;
			if (Return_Inside_If(T.Childs))
			{
				return result;
			}
		}
	}
}

bool Emulator::Unlock_Requem(Token *T)
{
	int Left = Get_Value_Of(T->Parameters.at(0));
	int Right = Get_Value_Of(T->Childs.at(0));
	if (T->Name == "==")
	{
		if (Left == Right)
		{
			return true;
		}
	}
	else if (T->Name == "!=")
	{
		if (Left != Right)
		{
			return true;
		}
	}
	else if (T->Name == ">")
	{
		if (Left > Right)
		{
			return true;
		}
	}
	else if (T->Name == "<")
	{
		if (Left < Right)
		{
			return true;
		}
	}
	else if (T->Name == "!>")
	{
		if (Left <= Right)
		{
			return true;
		}
	}
	else if (T->Name == "!<")
	{
		if (Left >= Right)
		{
			return true;
		}
	}
	return false;
}

Register* Emulator::Optimized_Register_Giver(Token* T)
{
	if (T->SReg != nullptr)
	{
		return T->SReg;
	}
	//optimized register to give to a normal math variable is R1 or R4
	//optimized rigister to give to offsetter is R3
	//optimized register to give to array is R5 or R6
	//optimized register to give to pointers is R2
	//this part checks is this named variable already has a register to it's name
	if ((R3->Base != nullptr) && (R3->Base->Name == T->Name))
	{
		//this has been a offsetter before
		R3->Link(T);
		T->SReg = R3;
		return R3;
	}
	else if ((R1->Base != nullptr) && (R1->Base->Name == T->Name))
	{
		//this is just a normal  math variable
		R1->Link(T);
		T->SReg = R1;
		Register_Turn = 1;
		return R1;
	}
	else if ((R4->Base != nullptr) && (R4->Base->Name == T->Name))
	{
		//this is just a normal  math variable
		R4->Link(T);
		T->SReg = R4;
		Register_Turn = 2;
		return R4;
	}
	else if ((R5->Base != nullptr) && (R5->Base->Name == T->Name))
	{
		if ((T->Offsetter != nullptr) && (R5->Base->Offsetter->Name == T->Offsetter->Name))
		{
			//same parent variable array, and same offsetters.
			R3->Link(T->Offsetter);
			T->Offsetter->SReg = R3;
			R5->Link(T);
			T->SReg = R5;
			return R5;
		}
		else
		{
			R5->Link(T);
			T->SReg = R5;
			Register_Turn = 3;
			return R5;
		}
		//even if this variable has R5 and,
		//now it doesnt have the same offsetter it wont point to same place enymore
	}
	else if ((R6->Base != nullptr) && (R6->Base->Name == T->Name))
	{
		if ((T->Offsetter != nullptr) && (R6->Base->Offsetter->Name == T->Offsetter->Name))
		{
			//same parent variable array, and same offsetters.
			R3->Link(T->Offsetter);
			T->Offsetter->SReg = R3;
			R6->Link(T);
			T->SReg = R6;
			return R6;
		}
		else
		{
			R6->Link(T);
			T->SReg = R6;
			Register_Turn = 0;
			return R6;
		}
		//even if this variable has R6 and,
		//now it doesnt have the same offsetter it wont point to same place enymore
	}
	else if (T->is(Variable) || T->is(Number) || T->is(Ptr))
	{
		if (Register_Turn == 0)
		{
			R1->Link(T);
			T->SReg = R1;
			Register_Turn++;
			return R1;
		}
		else if (Register_Turn == 1)
		{
			R4->Link(T);
			T->SReg = R4;
			Register_Turn++;
			return R4;
		}
		else if (Register_Turn == 2)
		{
			R5->Link(T);
			T->SReg = R5;
			Register_Turn++;
			return R5;
		}
		else if (Register_Turn > 2)
		{
			R6->Link(T);
			T->SReg = R6;
			Register_Turn = 0;
			return R6;
		}
	}
	else if (T->is(Array) || T->is(Ptr))
	{
		if (Register_Turn == 0)
		{
			R5->Link(T);
			T->SReg = R5;
			Register_Turn++;
			return R5;
		}
		else if (Register_Turn > 0)
		{
			R6->Link(T);
			T->SReg = R6;
			Register_Turn--;
			return R6;
		}
	}
	else if (T->is(Returning))
	{
		R1->Link(T);
		T->SReg = R1;
		Register_Turn++;
		return R1;
	}
	else
	{
		return nullptr;
	}
}

int Emulator::Get_Value_Of(Token* T)
{
	int Result = 0;
	if (T->SReg != nullptr)
	{
		return T->SReg->Value;
	}
	else if (T->is(Number))
	{
		return atoi(T->Name.c_str());
	}
	else if (T->is(Array))
	{
		//too complex
		//if this occurs something has gone wrong
	}
	else if (T->is(Variable))
	{
		return Find_From_Log(T)->Value;
	}
	else if (T->is(OPERATOR))
	{
		//later
	}
	else if (T->is(Returning))
	{
		//Later
	}
	return 0;
}

void Emulator::Add_To_Log(Token* T)
{
	bool There_Is_Already = false;
	for (Token* t : Log)
	{
		if (t == T)
		{
			*t = *T;
			There_Is_Already = true;
		}
	}
	if (There_Is_Already == false)
	{
		Log.push_back(T);
	}
}

Token* Emulator::Find_From_Log(Token* T)
{
	if (T->Offsetter != nullptr)
	{
		return nullptr;
	}
	for (Token *t : Log)
	{
		if ((t->Name == T->Name))
		{
			return t;
		}
	}
	return nullptr;
}

void Emulator::Sync_Parameters(vector<Token*> &Parameters)
{
	for (Token* t : Parameters)
	{
		t->Value = Stack.back();
		Stack.pop_back();
		Log.push_back(t);
	}
}

bool Emulator::Return_Inside_If(vector<Token*> T)
{
	for (Token* t : T)
	{
		if (t->Name == "return")
		{
			return true;
		}
		else if (t->Childs.size() > 0)
		{
			return Return_Inside_If(t->Childs);
		}
	}
	return false;
}

void Emulator::Clear_Log()
{
	for (int i = 0; i < Log.size(); i++)
	{
		if (Log.at(i)->is(Public) != true)
		{
			Log.erase(Log.begin() + i);
		}
	}
}

Token* Emulator::Get_Right_Token(Token* t)
{
	if (t->Offsetter != nullptr)
	{
		int Offset = Get_Value_Of(Get_Right_Token(t->Offsetter));
		int Parent_Address = t->StackOffset / 4;
		return Get_Right_Token(Get_List(t).at(Parent_Address + Offset - 1));
	}
	if (Find_From_Log(t) != nullptr)
	{
		return Find_From_Log(t);
	}
	else
	{
		return t;
	}
}

int Emulator::Simulate_Equ(Token* Dest, Token* Source)
{
	Token* D = Get_Right_Token(Dest);
	Token* S = Get_Right_Token(Source);

	D->Value = Get_Value_Of(S);
	Add_To_Log(D);
	return D->Value;
}

int Emulator::Simulate_Add(Token* Dest, Token* Source)
{
	Token* D = Get_Right_Token(Dest);
	Token* S = Get_Right_Token(Source);

	Classify_Right_Registers(D, S);

	Optimized_Register_Giver(D)->Value = Get_Value_Of(D);
	Optimized_Register_Giver(S)->Value = Get_Value_Of(S);
	D->SReg->Value += S->SReg->Value;
	return D->SReg->Value;
}

int Emulator::Simulate_Sub(Token* Dest, Token* Source)
{
	Token* D = Get_Right_Token(Dest);
	Token* S = Get_Right_Token(Source);

	Classify_Right_Registers(D, S);

	Optimized_Register_Giver(D)->Value = Get_Value_Of(D);
	Optimized_Register_Giver(S)->Value = Get_Value_Of(S);
	D->SReg->Value -= S->SReg->Value;
	return D->SReg->Value;
}

int Emulator::Simulate_Mul(Token* Dest, Token* Source)
{
	Token* D = Get_Right_Token(Dest);
	Token* S = Get_Right_Token(Source);

	Classify_Right_Registers(D, S);

	Optimized_Register_Giver(D)->Value = Get_Value_Of(D);
	Optimized_Register_Giver(S)->Value = Get_Value_Of(S);
	D->SReg->Value *= S->SReg->Value;
	return D->SReg->Value;
}

int Emulator::Simulate_Div(Token* Dest, Token* Source)
{
	Token* D = Get_Right_Token(Dest);
	Token* S = Get_Right_Token(Source);

	Classify_Right_Registers(D, S);

	Optimized_Register_Giver(D)->Value = Get_Value_Of(D);
	Optimized_Register_Giver(S)->Value = Get_Value_Of(S);
	D->SReg->Value /= S->SReg->Value;
	return D->SReg->Value;
}

bool Emulator::Simulate_Importance(Token* T)
{
	//this function gives function callations different parameter values and
	//checks if it gives different return values.
	if ((T->Parameters.size() > 0) && (T->is(Returning)))
	{
		for (Token* t : T->Parameters)
		{
			if (t->is(Parameter) && t->Outside_Of_Parameters)
			{
				return true;
			}
		}
		vector<int> results;
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < T->Parameters.size(); i++)
			{
				Stack.push_back(Get_Value_Of(Find_From_Log(T->Parameters.at(i))));
			}
			Emulator e = *this;
			e.Clear_Log();
			e.Sync_Parameters(T->daddy_Func->Parameters);
			e.Input.clear();
			e.Input = T->daddy_Func->Childs;
			results.push_back(e.Factory());
			e.clean_REG();
			for (int i = 0; i < T->Parameters.size(); i++)
			{
				Stack.pop_back();
			}
		}
		if ((results.at(0) == results.at(1)) && (results.at(2) == results.at(1)))
		{
			//useless function.
			Token* Num = T;
			Num->Name = to_string(results.at(0));
			Num->Flags = Number;
			Num->Childs.clear();
			Num->Parameters.clear();
			T = Num;
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		//check if this function touches public variables;
	}
	return true;
} //for calling

bool Emulator::Simulate_Function_Return_Value(Token* T)
{
	for (Token *C : *T->Callations)
	{
		for (Token* t : C->Parameters)
		{
			if (t->is(Parameter) && t->Outside_Of_Parameters)
			{
				return true;
			}
		}
	}
	if (T->Parameters.size() > 0)
	{
		vector<int> results;
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < T->Parameters.size(); i++)
			{
				Stack.push_back(rand() * 2);
			}
			Emulator e = *this;
			e.Clear_Log();
			e.Input = T->Childs;
			e.Sync_Parameters(T->Parameters);
			results.push_back(e.Factory());
			e.clean_REG();
			for (int i = 0; i < T->Parameters.size(); i++)
			{
				Stack.pop_back();
			}
		}
		if ((results.at(0) == results.at(1)) && (results.at(2) == results.at(1)))
		{
			//useless function.
			T->_Value_Return_ = true;
			T->Value = results.at(0);
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (T->is(Returning))
	{
		//check if the function touches global variables

		vector<int> results;
		for (int j = 0; j < 3; j++)
		{
			Emulator e = *this;
			e.Clear_Log();
			e.Input = T->Childs;
			results.push_back(e.Factory());
			e.clean_REG();
		}
		if ((results.at(0) == results.at(1)) && (results.at(2) == results.at(1)))
		{
			//useless function.
			T->_Value_Return_ = true;
			T->Value = results.at(0);
			return false;
		}
		else
		{
			return true;
		}
	}
	return true;
}

bool Emulator::Smart_Parameters(Token* F)
{
	for (Token* t : F->Childs)
	{
		if (t->is(If) || t->is(While))
		{
			return true;
		}
	}
	return false;
}

bool Emulator::Function_Unpacker(Token* F)
{
	//banana function only is called once
	//a = banana()
	//unpack the child tokens of banana into a = (x)
	return false;
}

void Emulator::clean_REG()
{
	for (int i = 0; i < R1->History.size(); i++)
	{
		R1->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < R4->History.size(); i++)
	{
		R4->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < R3->History.size(); i++)
	{
		R3->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < R5->History.size(); i++)
	{
		R5->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < R6->History.size(); i++)
	{
		R6->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < R7->History.size(); i++)
	{
		R7->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < R8->History.size(); i++)
	{
		R8->History.at(i)->SReg = nullptr;
	}

	R1->Value = 0;
	R4->Value = 0;
	R3->Value = 0;
	R5->Value = 0;
	R6->Value = 0;
	R7->Value = 0;
	R8->Value = 0;
}

vector<Token*> Emulator::Get_List(Token* t)
{
	if (t->ParentFunc != nullptr)
	{
		return t->ParentFunc->Childs;
	}
	else if (t->ParentType != nullptr)
	{
		return t->ParentType->Childs;
	}
}

void Emulator::Classify_Right_Registers(Token* d, Token* s)
{
	if ((d->SReg != nullptr) && d->SReg->Name == "R1")
	{
		Register_Turn = 1;
	}
	else if ((d->SReg != nullptr) && d->SReg->Name == "R4")
	{
		Register_Turn = 0;
	}
	if ((s->SReg != nullptr) && s->SReg->Name == "R1")
	{
		Register_Turn = 1;
	}
	else if ((s->SReg != nullptr) && s->SReg->Name == "R4")
	{
		Register_Turn = 0;
	}
}

bool Emulator::Has(Token* t, string s)
{
	if (t->Type == s)
	{
		return true;
	}
	else if (t->Right_Side_Token->Type == s)
	{
		return true;
	}
	for (Token* T : t->Right_Side_Token->Childs)
	{
		if (T->Type == s)
		{
			return true;
		}
	}
	return false;
}*/

