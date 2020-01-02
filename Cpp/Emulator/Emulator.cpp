#include "../../H/Emulator/Emulator.h"

void Emulator::Factory()
{
}

void Emulator::Branch_Picker(int i)
{

}

void Emulator::Next_Op_Picker(Token &T)
{
	if (T.Childs.size() > 0)
	{
		if (T.Parameters.size() > 0)
		{
			//there is sertain requem to go T.Childs.
			Unlock_Requem();
		}
		for (Token *t : T.Childs)
		{
			Next_Op_Picker(*t);

		}
	}
}
