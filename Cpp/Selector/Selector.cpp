#include "..\..\H\Selector\Selector.h"
#include "../../H/Back/Token.h"
extern int _SYSTEM_BIT_TYPE;

Selector::Selector(string s)
{
	Board_type = s;
	if (s == "-x86")
	{
		x86 x;
		x.ARC_Factory();
		Registers128 = x.Registers128;
		Registers64 = x.Registers64;
		Registers32 = x.Registers32;
		Registers16 = x.Registers16;
		Registers8 = x.Registers8;
		OpCodes = x.OpCodes;
	}
	else if (s == "-arm")
	{
		ARM x;
		x.ARC_Factory();
		Registers128 = x.Registers128;
		Registers64 = x.Registers64;
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

Token* Selector::Get_Right_Reg(int F, int Size)
{
	if ((F & Task_For_General_Purpose) == Task_For_General_Purpose)
	{
		if (Size == 8)
		{
			Token* r = Registers64.at(Reg_Turn64);
			Reg_Turn64++;
			if (Reg_Turn64 >= Registers64.size())
			{
				Reg_Turn64 = 0;
			}
			return r;
		}
		else if (Size == 4)
		{
			Token* r = Registers32.at(Reg_Turn32);
			Reg_Turn32++;
			if (Reg_Turn32 >= Registers32.size())
			{
				Reg_Turn32 = 0;
			}
			return r;
		}
		else if (Size == 2)
		{
			Token* r = Registers16.at(Reg_Turn16);
			Reg_Turn16++;
			if (Reg_Turn16 >= Registers16.size())
			{
				Reg_Turn16 = 0;
			}
			return r;
		}
		else if (Size == 1)
		{
			Token* r = Registers8.at(Reg_Turn8);
			Reg_Turn8++;
			if (Reg_Turn8 >= Registers8.size())
			{
				Reg_Turn8 = 0;
			}
			return r;
		}
	}
	else if ((F & Task_For_Floating_Math) == Task_For_Floating_Math)
	{
		if (Size == 12)
		{
			Token* r = Registers128.at(Reg_Turn128);
			Reg_Turn128++;
			return r;
		}
	}
	if (Size == 12)
	{
		for (Token* r : Registers128)
		{
			if (r->is(F))
			{
				return r;
			}
		}
	}
	else if (Size == 8)
	{
		for (Token* r : Registers64)
		{
			if (r->is(F))
			{
				return r;
			}
		}
	}
	else if (Size == 4)
	{
		for (Token* r : Registers32)
		{
			if (r->is(F))
			{
				return r;
			}
		}
	}
	else if (Size == 2)
	{
		for (Token* r : Registers16)
		{
			if (r->is(F))
			{
				return r;
			}
		}
	}
	else
	{
		for (Token* r : Registers8)
		{
			if (r->is(F))
			{
				return r;
			}
		}
	}
	cout << "Error:: Couldn't find suitable architehture register(" + Board_type + ": " + to_string(Size * 8) + " )." << endl;
	return nullptr;
}

string Selector::Get_ID(string id, string trust, vector<int> minmax)
{
	if (id == "")
		return "";
	int i_R = minmax.at(0);
	int i_L = minmax.at(1);
	for (OpC* o : OpCodes)
	{
		int o_R_Min = o->MinMax.at(0);
		int o_R_Max = o->MinMax.at(1);
		int o_L_Min = o->MinMax.at(2);
		int o_L_Max = o->MinMax.at(3);
		if (((o_R_Min <= i_R) && (i_R <= o_R_Max)) && ((o_L_Min <= i_L) &&( i_L <= o_L_Max)))
		{
			if (o->ID == id)
				return o->OpCode;
		}
	}
	if ((trust == "export") || (trust == "raw_label"))
		return id;
	if (trust != "label")
		cout << "Warning:: This is here because your'e using a illegal opcode: " << id << endl;
	return "_" + id;
}
