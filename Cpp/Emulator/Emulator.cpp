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
			if (T.repz != nullptr)
			{
				//T.Parameters.at(0)->repz = T.repz;
			}
			if (T.Name == "+")
			{
				//reg = Dest->SUM(Source, Cheat);
			}
			else if (T.Name == "-")
			{
				//reg = Dest->SUBSTRACT(Source, Cheat);
			}
			else if (T.Name == "*")
			{
				//reg = Dest->MULTIPLY(Source);
			}
			else if (T. Name == "/")
			{
				//reg = Dest->DIVIDE(Source);
			}
			if (T.Name == "=" && Layer == 0)
			{
				reg = "";
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
					//Cheat->MOVE(Dest);
				}
				//Dest->Reg->Link(Dest);
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
	if (ECX->Base->Name == T->Name)
	{
		//this has been a offsetter before
		ECX->Link(T);
	}
	else if (EAX->Base->Name == T->Name)
	{
		//this is just a normal  math variable
		EAX->Link(T);
	}
	else if (EDX->Base->Name == T->Name)
	{
		//this is just a normal  math variable
		EDX->Link(T);
	}
	else if (EDI->Base->Name == T->Name)
	{
		if ((T->Offsetter != nullptr) && (EDI->Base->Offsetter->Name == T->Offsetter->Name))
		{
			//same parent variable array, and same offsetters.
			ECX->Link(T->Offsetter);
			EDI->Link(T);
		}
		//even if this variable has EDI and,
		//now it doesnt have the same offsetter it wont point to same place enymore
	}
	else if (ESI->Base->Name == T->Name)
	{
		if ((T->Offsetter != nullptr) && (ESI->Base->Offsetter->Name == T->Offsetter->Name))
		{
			//same parent variable array, and same offsetters.
			ECX->Link(T->Offsetter);
			ESI->Link(T);
		}
		//even if this variable has ESI and,
		//now it doesnt have the same offsetter it wont point to same place enymore
	}
	return nullptr;
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
		if ((Source->Reg != nullptr) || (Source->Reg->Name != "null"))
		{
			//link as same registers.
			Dest->Reg = Source->Reg;
		}
	}
	return 0;
}

int Emulator::Simulate_Add(Token* Dest, Token* Source, Token* Cheat)
{
	return 0;
}

int Emulator::Simulate_Sub(Token* Dest, Token* Source, Token* Cheat)
{
	return 0;
}

int Emulator::Simulate_Mul(Token* Dest, Token* Source)
{
	return 0;
}

int Emulator::Simulate_Div(Token* Dest, Token* Source)
{
	return 0;
}
