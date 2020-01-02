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
		if (T.Parameters.at(0)->is(OPERATOR))
		{
			Emulator E = *this;
			E.Input = T.Parameters;
			E.Factory();
		}
		else
		{
			Simulate_Math(T);
		}
	}
}

bool Emulator::Unlock_Requem(Token &T)
{
	return false;
}

void Emulator::Simulate_Math(Token& T)
{
	if (T.Name == "=")
	{
		if (T.Childs.at(0)->is(Number))
		{
			T.Parameters.at(0)->Value = atoi(T.Childs.at(0)->Name.c_str());
		}
		else if (T.Childs.at(0)->is(Variable))
		{
			T.Parameters.at(0)->Value = T.Childs.at(0)->Value;
		}
	}
}
