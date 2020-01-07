#include "../../H/Emulator/Emulator.h"

void Emulator::Factory()
{
	for (Token* t : Input)
	{
		Next_Op_Picker(*t);
	}
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
		E.Factory();
		this->Register_Turn = E.Register_Turn;
	}
	else if (T.is(Call))
	{
		for (Token* t : T.Parameters)
		{
			Stack.push_back(t->Value);
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
				this->Dest = b.Dest;
				this->Cheat = b.Cheat;
			}
			if (T.Childs.at(0)->is(Variable) || T.Childs.at(0)->is(Number) || T.Childs.at(0)->is(Ptr) || T.Childs.at(0)->is(String))
			{
				Source = T.Childs.at(0);
			}
			else
			{
				Emulator b = *this;
				b.Input = T.Childs;
				b.Layer++;
				b.Factory();
				b.Layer--;
				this->Source = b.Source;
				this->Cheat = b.Cheat;
			}
			string reg = "";
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
			else if (T. Name == "/")
			{
				Simulate_Div(Dest, Source, Cheat);
			}
			if (T.Name == "=" && Layer == 0)
			{
				Simulate_Equ(Dest, Source);
			}
			else if (T.Name == "==" || T.Name == ">=" || T.Name == "<=" || T.Name == ">" || T.Name == "<" || T.Name == "!=" || T.Name == "!>" || T.Name == "!<")
			{
				Unlock_Requem(T);
			}
			else if (Layer != 0)
			{
				Cheat = Dest;
				Dest = Source;
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
				}
				if (Dest->tmp != nullptr)
				{
					if (Cheat->tmp != nullptr)
					{
						//Cheat->tmp->MOVE(Dest->tmp);
					}
					else
					{
						//Cheat->MOVE(Dest->tmp);
					}
				}
				else if (Cheat != nullptr)
				{
					Simulate_Equ(Cheat, Dest);
				}
				Dest->SReg->Link(Dest);
				//Dest->Reg->Link(Dest);
			}
	}
	else if (T.is(If) || (T.is(Else) && T.is(If)) || T.is(While))
	{
		if (Unlock_Requem(T))
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
	return Dest->Value;
}

int Emulator::Simulate_Add(Token* Dest, Token* Source, Token* Cheat)
{
	if (Source->is(Number))
	{
		if ((Cheat != nullptr) && (Cheat->Name == Dest->Name))
		{
			Cheat->Value += atoi(Source->Name.c_str());
		}
		else if ((Dest->SReg == nullptr) && (Dest->SReg->Name == "null"))
		{
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value += atoi(Source->Name.c_str());
		}
	}
	else if (Source->is(Variable))
	{
		if ((Cheat != nullptr) && (Cheat->Name == Dest->Name))
		{
			Cheat->Value += Source->Value;
		}
		else if ((Dest->SReg == nullptr) || (Dest->SReg->Name == "null"))
		{
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value += Source->Value;
		}
	}
	return 0;
}

int Emulator::Simulate_Sub(Token* Dest, Token* Source, Token* Cheat)
{
	if (Source->is(Number))
	{
		if ((Cheat != nullptr) && (Cheat->Name == Dest->Name))
		{
			Cheat->Value -= atoi(Source->Name.c_str());
		}
		else if ((Dest->SReg == nullptr) && (Dest->SReg->Name == "null"))
		{
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value -= atoi(Source->Name.c_str());
		}
	}
	else if (Source->is(Variable))
	{
		if ((Cheat != nullptr) && (Cheat->Name == Dest->Name))
		{
			Cheat->Value -= Source->Value;
		}
		else if ((Dest->SReg == nullptr) || (Dest->SReg->Name == "null"))
		{
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value -= Source->Value;
		}
	}
	return 0;
}

int Emulator::Simulate_Mul(Token* Dest, Token* Source, Token* Cheat)
{
	if (Source->is(Number))
	{
		if ((Cheat != nullptr) && (Cheat->Name == Dest->Name))
		{
			Cheat->Value *= atoi(Source->Name.c_str());
		}
		else if ((Dest->SReg == nullptr) && (Dest->SReg->Name == "null"))
		{
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value *= atoi(Source->Name.c_str());
		}
	}
	else if (Source->is(Variable))
	{
		if ((Cheat != nullptr) && (Cheat->Name == Dest->Name))
		{
			Cheat->Value *= Source->Value;
		}
		else if ((Dest->SReg == nullptr) || (Dest->SReg->Name == "null"))
		{
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value *= Source->Value;
		}
	}
	return 0;
}

int Emulator::Simulate_Div(Token* Dest, Token* Source, Token* Cheat)
{
	if (Source->is(Number))
	{
		if ((Cheat != nullptr) && (Cheat->Name == Dest->Name))
		{
			Cheat->Value /= atoi(Source->Name.c_str());
		}
		else if ((Dest->SReg == nullptr) && (Dest->SReg->Name == "null"))
		{
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value /= atoi(Source->Name.c_str());
		}
	}
	else if (Source->is(Variable))
	{
		if ((Cheat != nullptr) && (Cheat->Name == Dest->Name))
		{
			Cheat->Value /= Source->Value;
		}
		else if ((Dest->SReg == nullptr) || (Dest->SReg->Name == "null"))
		{
			Optimized_Register_Giver(Dest);
			Dest->SReg->Value /= Source->Value;
		}
	}
	return 0;
}
