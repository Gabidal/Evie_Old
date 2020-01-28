#include "../../H/Emulator/Emulator.h"


int Emulator::Factory()
{
	for (Token* t : Input)
	{
		if ((t->is(If) || (t->is(Else) && t->is(If)) || t->is(While)) && (Unlock_Requem(*t->Parameters.at(0))) && Return_Inside_If(t->Childs))
		{
			return Next_Op_Picker(*t);
		}
		else if (t->is(Else) && (t->Name == "else") && (Unlock_Requem(*t->Former->Parameters.at(0)) == false) && Return_Inside_If(t->Childs))
		{
			return Next_Op_Picker(*t);
		}
		else if ((Input.size() == 1) && ((t->is(Call)) || (t->is(Function))))
		{
			return Next_Op_Picker(*t);
		}
		else
		{
			Next_Op_Picker(*t);
		}
		if (t->Name == "return")
		{
			if (t->Childs.at(0)->is(Number))
			{
				return Get_Value_Of(t->Childs.at(0));
			}
			else
			{
				return Find_From_Log(t->Childs.at(0))->Value;
			}
		}
	}
}

int Emulator::Start_Simulation(int start)
{
	return Next_Op_Picker(*Input.at(start));
}

void Emulator::Branch_Picker(int i)
{

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
			this->Log = b.Log;
			this->Deep_Math = b.Deep_Math;
			this->Source = b.Source;
			this->Cheat = b.Cheat;
		}
		if (Dest->is(Returning) && T.Childs.at(0)->is(Returning))
		{
			Double_Callation = false;
			Dest->SReg = EBX;
			EBX->Link(Dest);
		}
		string reg = "...";
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
				reg = "";
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
			Unlock_Requem(T);
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

		if ((reg.size() > 0) && (Layer == 0))
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
		if (Unlock_Requem(*T.Parameters.at(0)))
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
	else if (T.is(Else) && (Unlock_Requem(*T.Former->Parameters.at(0)) == false))
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
		for (;Unlock_Requem(*T.Parameters.at(0)) == false;)
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

bool Emulator::Unlock_Requem(Token &T)
{
	int Left = Get_Value_Of(T.Parameters.at(0));
	int Right = Get_Value_Of(T.Childs.at(0));
	if (T.Name == "==")
	{
		if (Left == Right)
		{
			return true;
		}
	}
	else if (T.Name == "!=")
	{
		if (Left != Right)
		{
			return true;
		}
	}
	else if (T.Name == ">")
	{
		if (Left > Right)
		{
			return true;
		}
	}
	else if (T.Name == "<")
	{
		if (Left < Right)
		{
			return true;
		}
	}
	else if (T.Name == "!>")
	{
		if (Left <= Right)
		{
			return true;
		}
	}
	else if (T.Name == "!<")
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
	//optimized register to give to a normal math variable is EAX or EDX
	//optimized rigister to give to offsetter is ECX
	//optimized register to give to array is EDi or ESi
	//optimized register to give to pointers is EBX
	//this part checks is this named variable already has a register to it's name
	if ((ECX->Base != nullptr) && (ECX->Base->Name == T->Name))
	{
		//this has been a offsetter before
		ECX->Link(T);
		T->SReg = ECX;
		return ECX;
	}
	else if ((EAX->Base != nullptr) && (EAX->Base->Name == T->Name))
	{
		//this is just a normal  math variable
		EAX->Link(T);
		T->SReg = EAX;
		Register_Turn = 1;
		return EAX;
	}
	else if ((EDX->Base != nullptr) && (EDX->Base->Name == T->Name))
	{
		//this is just a normal  math variable
		EDX->Link(T);
		T->SReg = EDX;
		Register_Turn = 0;
		return EDX;
	}
	else if ((EDI->Base != nullptr) && (EDI->Base->Name == T->Name))
	{
		if ((T->Offsetter != nullptr) && (EDI->Base->Offsetter->Name == T->Offsetter->Name))
		{
			//same parent variable array, and same offsetters.
			ECX->Link(T->Offsetter);
			T->Offsetter->SReg = ECX;
			EDI->Link(T);
			T->SReg = EDI;
			return EDI;
		}
		//even if this variable has EDI and,
		//now it doesnt have the same offsetter it wont point to same place enymore
	}
	else if ((ESI->Base != nullptr) && (ESI->Base->Name == T->Name))
	{
		if ((T->Offsetter != nullptr) && (ESI->Base->Offsetter->Name == T->Offsetter->Name))
		{
			//same parent variable array, and same offsetters.
			ECX->Link(T->Offsetter);
			T->Offsetter->SReg = ECX;
			ESI->Link(T);
			T->SReg = ESI;
			return ESI;
		}
		//even if this variable has ESI and,
		//now it doesnt have the same offsetter it wont point to same place enymore
	}
	else if (T->is(Variable) || T->is(Number) || T->is(Ptr))
	{
		if (Register_Turn == 0)
		{
			EAX->Link(T);
			T->SReg = EAX;
			Register_Turn++;
			return EAX;
		}
		else if (Register_Turn == 1)
		{
			EDX->Link(T);
			T->SReg = EDX;
			Register_Turn--;
			return EDX;
		}
	}
	else if (T->is(Array) || T->is(Ptr))
	{
		if (Register_Turn == 0)
		{
			EDI->Link(T);
			T->SReg = EDI;
			Register_Turn++;
			return EDI;
		}
		else if (Register_Turn > 0)
		{
			ESI->Link(T);
			T->SReg = ESI;
			Register_Turn--;
			return ESI;
		}
	}
	else if (T->is(Returning))
	{
		EAX->Link(T);
		T->SReg = EAX;
		Register_Turn++;
		return EAX;
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
		//too complex atm
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

	Optimized_Register_Giver(D)->Value = Get_Value_Of(D);
	Optimized_Register_Giver(S)->Value = Get_Value_Of(S);
	D->SReg->Value += S->SReg->Value;
	return D->SReg->Value;
}

int Emulator::Simulate_Sub(Token* Dest, Token* Source)
{
	Token* D = Get_Right_Token(Dest);
	Token* S = Get_Right_Token(Source);

	Optimized_Register_Giver(D)->Value = Get_Value_Of(D);
	Optimized_Register_Giver(S)->Value = Get_Value_Of(S);
	D->SReg->Value -= S->SReg->Value;
	return D->SReg->Value;
}

int Emulator::Simulate_Mul(Token* Dest, Token* Source)
{
	Token* D = Get_Right_Token(Dest);
	Token* S = Get_Right_Token(Source);

	Optimized_Register_Giver(D)->Value = Get_Value_Of(D);
	Optimized_Register_Giver(S)->Value = Get_Value_Of(S);
	D->SReg->Value *= S->SReg->Value;
	return D->SReg->Value;
}

int Emulator::Simulate_Div(Token* Dest, Token* Source)
{
	Token* D = Get_Right_Token(Dest);
	Token* S = Get_Right_Token(Source);

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
	for (int i = 0; i < EAX->History.size(); i++)
	{
		EAX->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < EDX->History.size(); i++)
	{
		EDX->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < ECX->History.size(); i++)
	{
		ECX->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < EDI->History.size(); i++)
	{
		EDI->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < ESI->History.size(); i++)
	{
		ESI->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < ESP->History.size(); i++)
	{
		ESP->History.at(i)->SReg = nullptr;
	}
	for (int i = 0; i < EBP->History.size(); i++)
	{
		EBP->History.at(i)->SReg = nullptr;
	}

	EAX->Value = 0;
	EDX->Value = 0;
	ECX->Value = 0;
	EDI->Value = 0;
	ESI->Value = 0;
	ESP->Value = 0;
	EBP->Value = 0;
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

