#include "..\..\H\Selector\Selector.h"
#include "../../H/Back/Token.h"

Selector::Selector(string s)
{
	Board_type = s;
	if (s == "-x86")
	{
		x86 x;
		x.ARC_Factory();
		Registers32 = x.Registers32;
		Registers16 = x.Registers16;
		Registers8 = x.Registers8;
		OpCodes = x.OpCodes;
	}
	else if (s == "-arm")
	{
		ARM x;
		x.ARC_Factory();
		Registers32 = x.Registers32;
		Registers16 = x.Registers16;
		Registers8 = x.Registers8;
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

Register* Selector::Get_Right_Reg(int F, int Size)
{
	if (Size == 4)
	{
		for (Register* r : Registers32)
		{
			if (r->is(F))
			{
				return r;
			}
		}
	}
	else if (Size == 2)
	{
		for (Register* r : Registers16)
		{
			if (r->is(F))
			{
				return r;
			}
		}
	}
	else
	{
		for (Register* r : Registers8)
		{
			if (r->is(F))
			{
				return r;
			}
		}
	}
}

Register* Selector::Get_Belonging_Reg(string name)
{
	for (Register* r : Registers32)
	{
		if (r->Base == nullptr)
		{
			continue;
		}
		if (r->Base->Name == name)
		{
			return r;
		}
	}
	for (Register* r : Registers16)
	{
		if (r->Base == nullptr)
		{
			continue;
		}
		if (r->Base->Name == name)
		{
			return r;
		}
	}
	for (Register* r : Registers8)
	{
		if (r->Base == nullptr)
		{
			continue;
		}
		if (r->Base->Name == name)
		{
			return r;
		}
	}
	return nullptr;
}

string Selector::Get_ID(string id)
{
	if (id == "")
		return "";
	for (OpC* o : OpCodes)
	{
		if (o->ID == id)
		{
			return o->OpCode;
		}
	}
	cout << "unable to find OpCode " << id << endl;
	return id;
}

Register* Selector::Get_Reg(int Size)
{
	if (Size == 4)
	{
		if (Reg_Turn32 >= Registers32.size() - 1)
		{
			Reg_Turn32 = 1;
		}
		else
		{
			Reg_Turn32++;
		}
		return Registers32.at(Reg_Turn32 - 1);
	}
	else if (Size == 2)
	{
		if (Reg_Turn16 >= Registers16.size() - 1)
		{
			Reg_Turn16 = 1;
		}
		else
		{
			Reg_Turn16++;
		}
		return Registers16.at(Reg_Turn16 - 1);
	}
	else
	{
		if (Reg_Turn8 >= Registers8.size() - 1)
		{
			Reg_Turn8 = 1;
		}
		else
		{
			Reg_Turn8++;
		}
		return Registers8.at(Reg_Turn8 - 1);
	}
}
