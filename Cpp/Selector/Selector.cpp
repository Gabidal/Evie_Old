#include "..\..\H\Selector\Selector.h"
#include "../../H/Back/Token.h"

Selector::Selector(string s)
{
	if (s == "-x86")
	{
		x86 x;
		Registers = x.Registers;
		OpCodes = x.OpCodes;
	}
	else if (s == "-arm")
	{
		ARM x;
		Registers = x.Registers;
		OpCodes = x.OpCodes;
	}
}

Selector::~Selector()
{
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

Register* Selector::Get_Belonging_Reg(string name)
{
	for (Register* r: Registers)
	{
		if (r->Base->Name == name)
		{
			return r;
		}
	}
	return nullptr;
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
