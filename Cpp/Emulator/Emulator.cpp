#include "../../H/Emulator/Emulator.h"

int Emulator::Factory()
{
	for (Token* t : Input)
	{
		Next_Op_Picker(*t);
		if (t->Name == "return")
		{
			return Find_From_Log(t->Childs.at(0))->Value;
		}
	}
}

void Emulator::Start_Simulation(int start)
{
	Next_Op_Picker(*Input.at(start));
}

void Emulator::Branch_Picker(int i)
{

}

void Emulator::Next_Op_Picker(Token &T)
{
	if (T.is(Function))
	{
		Emulator E = *this;
		E.Input = T.Childs;
		E.Layer = 0;
		Sync_Parameters(T.Parameters);
		E.Log = Log;
		E.Factory();
		this->Register_Turn = E.Register_Turn;
	}
	else if (T.is(Call))
	{
		for (Token* t : T.Parameters)
		{
			Stack.push_back(Find_From_Log(t)->Value);
		}
		if (T.daddy_Func->Childs.size() > 0)
		{
			Emulator E = *this;
			E.Input.clear();
			E.Input.push_back(T.daddy_Func);
			//Original_Size = Log.size();
			E.Factory();
			this->Register_Turn = E.Register_Turn;
		}
	}
	else if (T.is(OPERATOR))
	{
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
			this->Deep_Math = b.Deep_Math;
			this->Dest = b.Dest;
			this->Cheat = b.Cheat;
		}
		if (Dest->is(Returning) && T.Childs.at(0)->is(Returning))
		{
			Double_Callation = true;
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
			Simulate_Add(Dest, Source, Cheat);
		}
		else if (T.Name == "-")
		{
			Simulate_Sub(Dest, Source, Cheat);
		}
		else if (T.Name == "*")
		{
			Simulate_Mul(Dest, Source, Cheat);
		}
		else if (T.Name == "/")
		{
			Simulate_Div(Dest, Source, Cheat);
		}
		if (Layer == 0)
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
				Dest->SReg->Link(Cheat);
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
				Cheat = Dest;
				Dest = Source;
			}
		}

		if ((reg.size() > 0) && (Layer == 0))
		{
			string resulter = Dest->Name;
			if (T.Name == "+" || T.Name == "-")
			{
				if (Source->is(Number) && (Cheat->Name == Dest->Name))
				{
					return;
				}
				if (Dest->is(Number) && (Cheat->Name == Source->Name))
				{
					return;
				}
			}/*
			if (Dest->tmp != nullptr)
			{
				if (Cheat->tmp != nullptr)
				{
					//Cheat->tmp->MOVE(Dest->tmp);
					//Simulate_Equ(Cheat, Dest);
				}
				else
				{
					//Cheat->MOVE(Dest->tmp);
				}
			}*/
			if ((Cheat != nullptr) && (Deep_Math == false))
			{
				Simulate_Equ(Cheat, Dest);
			}
			Dest->SReg->Link(Dest);
		}
		if (Deep_Math_Done)
		{
			Deep_Math = false;
			Deep_Math_Done = false;
			Cheat = nullptr;
		}
	}
	else if (T.is(If) || (T.is(Else) && T.is(If)) || T.is(While))
	{
		if (Unlock_Requem(*T.Parameters.at(0)))
		{
			Emulator E = *this;
			E.Input = T.Childs;
			E.Factory();
			this->Register_Turn = E.Register_Turn;
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
	}
	else if ((EAX->Base != nullptr) && (EAX->Base->Name == T->Name))
	{
		//this is just a normal  math variable
		EAX->Link(T);
		T->SReg = EAX;
	}
	else if ((EDX->Base != nullptr) && (EDX->Base->Name == T->Name))
	{
		//this is just a normal  math variable
		EDX->Link(T);
		T->SReg = EDX;
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
		}
		else if (Register_Turn == 1)
		{
			EDX->Link(T);
			T->SReg = EDX;
			Register_Turn--;
		}
	}
	else if (T->is(Array) || T->is(Ptr))
	{
		if (Register_Turn == 0)
		{
			EDI->Link(T);
			T->SReg = EDI;
			Register_Turn++;
		}
		else if (Register_Turn > 0)
		{
			ESI->Link(T);
			T->SReg = ESI;
			Register_Turn--;
		}
	}
	else if (T->is(Returning))
	{
		EAX->Link(T);
		T->SReg = EAX;
		Register_Turn++;
	}
	else
	{
		return nullptr;
	}
}

int Emulator::Get_Value_Of(Token* T)
{
	int Result = 0;
	if (T->is(Number))
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

int Emulator::Simulate_Equ(Token* Dest, Token* Source)
{
	if (Source->is(Number))
	{
		//direct movation into address dont need to use reg
		Dest->Value = atoi(Source->Name.c_str());
	}
	else if (Source->is(Variable))
	{
		//need to get a reg
		Dest->Value = Source->Value;
		if ((Source->SReg != nullptr) && (Source->SReg->Name != "null"))
		{
		}
		else
		{
			Optimized_Register_Giver(Source);
		}
		Dest->SReg = Source->SReg;
		Dest->Value = Dest->SReg->Value;
	}
	Add_To_Log(Dest);
	return Dest->Value;
}

int Emulator::Simulate_Add(Token* Dest, Token* Source, Token* Cheat)
{
	if (Source->is(Number))
	{
		//we need to get the logged value of dest
		if (Dest == Cheat)
		{
			//direct save the value
			Find_From_Log(Cheat)->Value += atoi(Source->Name.c_str());
		}
		else
		{
			//save the value into a S_Register
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value += atoi(Source->Name.c_str());
		}
	}
	else if (Source->is(Variable))
	{
		//we need to get the logged value of dest
		if (Dest == Cheat)
		{
			//direct save the value
			Find_From_Log(Cheat)->Value += Find_From_Log(Source)->Value;
		}
		else
		{
			//save the value into a S_Register
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value += Find_From_Log(Source)->Value;
		}
	}
	return 0;
}

int Emulator::Simulate_Sub(Token* Dest, Token* Source, Token* Cheat)
{
	if (Source->is(Number))
	{
		//we need to get the logged value of dest
		if (Dest == Cheat)
		{
			//direct save the value
			Find_From_Log(Cheat)->Value -= atoi(Source->Name.c_str());
		}
		else
		{
			//save the value into a S_Register
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value -= atoi(Source->Name.c_str());
		}
	}
	else if (Source->is(Variable))
	{
		//we need to get the logged value of dest
		if (Dest == Cheat)
		{
			//direct save the value
			Find_From_Log(Cheat)->Value -= Find_From_Log(Source)->Value;
		}
		else
		{
			//save the value into a S_Register
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value -= Find_From_Log(Source)->Value;
		}
	}
	return 0;
}

int Emulator::Simulate_Mul(Token* Dest, Token* Source, Token* Cheat)
{
	if (Source->is(Number))
	{
		//we need to get the logged value of dest
		if (Dest == Cheat)
		{
			//direct save the value
			Find_From_Log(Cheat)->Value *= atoi(Source->Name.c_str());
		}
		else
		{
			//save the value into a S_Register
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value *= atoi(Source->Name.c_str());
		}
	}
	else if (Source->is(Variable))
	{
		//we need to get the logged value of dest
		if (Dest == Cheat)
		{
			//direct save the value
			Find_From_Log(Cheat)->Value *= Find_From_Log(Source)->Value;
		}
		else
		{
			//save the value into a S_Register
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value *= Find_From_Log(Source)->Value;
		}
	}
	return 0;
}

int Emulator::Simulate_Div(Token* Dest, Token* Source, Token* Cheat)
{
	if (Source->is(Number))
	{
		//we need to get the logged value of dest
		if (Dest == Cheat)
		{
			//direct save the value
			Find_From_Log(Cheat)->Value /= atoi(Source->Name.c_str());
		}
		else
		{
			//save the value into a S_Register
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value /= atoi(Source->Name.c_str());
		}
	}
	else if (Source->is(Variable))
	{
		//we need to get the logged value of dest
		if (Dest == Cheat)
		{
			//direct save the value
			Find_From_Log(Cheat)->Value /= Find_From_Log(Source)->Value;
		}
		else
		{
			//save the value into a S_Register
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value /= Find_From_Log(Source)->Value;
		}
	}
	return 0;
}
