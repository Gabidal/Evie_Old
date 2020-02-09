#include "..\..\H\Selector\Selector.h"
#include "../../H/Back/Token.h"

Selector::Selector(Token* i)
{
#if __ARM__
	ARC_Factory();
#else
	ARC_Factory();
#endif
	Input = i;
	I = Input->Name;
}

Selector::Selector()
{
#if __ARM__
	ARC_Factory();
#else
	ARC_Factory();
#endif
}

OpC* Selector::OpCode_Selector()
{
	return nullptr;
}

string Selector::Get_Right_Reg(int F)
{
	for (Register* r : Registers)
	{
		if (r->is(F))
		{
			return r->Name;
		}
	}
}

string Selector::Get_ID(string id)
{
	for (OpC* o : OpCodes)
	{
		if (o->ID == id)
		{
			return o->OpCode;
		}
	}
	cout << "unable to find OpCode " << id << endl;
}

Register* Selector::Get_Reg(string id)
{
	for (Register* o : Registers)
	{
		if (o->ID == id)
		{
			return o;
		}
	}
	cout << "unable to find Register " << id << endl;
}
