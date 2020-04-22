#include "../../H/Selector/Selector.h"
#include "../../H/Back/Token.h"
extern int _SYSTEM_BIT_TYPE;
extern map<string, Token*> Register_Lock;

Selector::Selector(string s)
{
	Board_type = s;
	if (s == "x86")
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
	else if (s == "arm")
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
	Token* r;
	if (((F & Task_For_General_Purpose) == Task_For_General_Purpose) || ((F & Task_For_Floating_Math) == Task_For_Floating_Math))
	{
		if (Size == 12)
		{
			r = Get_Reg(Registers128, F, Reg_Turn128);
			if (r != nullptr)
				return r;
		}
		if (Size == 8)
		{
			r = Get_Reg(Registers64, F, Reg_Turn64);
			if (r != nullptr)
				return r;
		}
		else if (Size == 4)
		{
			r = Get_Reg(Registers32, F, Reg_Turn32);
			if (r != nullptr)
				return r;
		}
		else if (Size == 2)
		{
			r = Get_Reg(Registers16, F, Reg_Turn16);
			if (r != nullptr)
				return r;
		}
		else if (Size == 1)
		{
			r = Get_Reg(Registers8, F, Reg_Turn8);
			if (r != nullptr)
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
	cout << "Error: Couldn't find suitable architehture register(" + Board_type + ": " + to_string(Size * 8) + " )." << endl;
	return nullptr;
}

Token* Selector::Get_Reg(vector<Token*> regs, int F, int &Previus)
{
	Token* r = new Token;
	if (Previus >= (int)regs.size()) Previus = 0;
	int i = Previus;
	do// int i = Reg_Turn16; i < Registers16.size(); i++)
	{
		if (regs.at(i)->is(F))
		{
			r = regs.at(i);
			Previus = i + 1;
			return r;
		}
		if (++i >= (int)regs.size())
		{
			i = 0;
		}
	} while (i != Previus);
	return nullptr;
}

Token* Selector::Check_For_Reg(int Size)
{
	if (Size == 12)
	{
		return Registers128.at(Reg_Turn128);
	}
	else if (Size == 8)
	{
		return Registers64.at(Reg_Turn64);
	}
	else if (Size == 4)
	{
		return Registers32.at(Reg_Turn32);
	}
	else if (Size == 2)
	{
		return Registers16.at(Reg_Turn16);
	}
	else if (Size == 1)
	{
		return Registers8.at(Reg_Turn8);
	}
	cout << "Error: Cannot check the size of --> " << Size << endl;
	return nullptr;
}

void Selector::Increase(int Size)
{
	if (Size == 12)
	{
		Reg_Turn128++;
	}
	else if (Size == 8)
	{
		Reg_Turn64++;
	}
	else if (Size ==4)
	{
		Reg_Turn32++;
	}
	else if (Size == 2)
	{
		Reg_Turn16++;
	}
	else if (Size == 1)
	{
		Reg_Turn8++;
	}
}

int Selector::Get_Right_Reg_Index(int size, Token* r){
	vector<Token*> registers;
	if (size == 1)
	{
		registers = Registers8;
	}
	else if (size == 2)
	{
		registers = Registers16;
	}
	else if (size == 4)
	{
		registers = Registers32;
	}
	else if (size == 8)
	{
		registers = Registers64;
	}
	else if (size == 12)
	{
		registers = Registers128;
	}
	else
	{
		cout << "Error: No known size --> " << size << ". Register name --> " << r->Name << endl;
		return 0;
	}

	for (int i = 0; i < registers.size(); i++)
		if (registers.at(i)->Name == r->Name)
			return i;
	cout << "Error: First of all this shouldnt be happening XD" << endl;
	return 0;
}

int& Selector::Get_Ongoing_Index(int size){
	if (size == 1)
	{
		return Reg_Turn8;
	}
	else if (size == 2)
	{
		return Reg_Turn16;
	}
	else if (size == 4)
	{
		return Reg_Turn32;
	}
	else if (size == 8)
	{
		return Reg_Turn64;
	}
	else if (size == 12)
	{
		return Reg_Turn128;
	}
	else
	{
		cout << "Error: No known size --> " << size << endl;
		int* tmp;
		return *tmp;
	}
}

string Selector::Get_ID(string id, string trust, vector<int> minmax)
{
	if (id == "")
		return "";

	vector<int> i_Sizes = minmax;
	for (OpC* o : OpCodes)
	{
		vector<int> o_Sizes = o->MinMax;
		if (o_Sizes.size() != (i_Sizes.size() * 2))
			continue;
		for (int i = 0; i < (int)i_Sizes.size(); i++)
		{
			int in = i_Sizes.at(i);
			int in_min = o_Sizes.at(i * 2);
			int in_max = o_Sizes.at(i * 2 + 1);
			if ((in_min <= in) && (in_max >= in))
				continue;
			else
				goto CONTINUE;
		}
		if (o->ID == id)
			return o->OpCode;
		CONTINUE:;
	}
	if ((trust == "export") || (trust == "import") || (trust == "raw_label") || (trust == "global"))
		return id;
	if ((trust != "label") && (trust != "<") && (trust != ">") && (trust != "!<") && (trust != "!>") && (trust != "==") && (trust != "!=") && (trust != "<=") && (trust != ">=") && (trust != "jmp"))
	{
		cout << "Warning: This is here because your'e using a illegal opcode: " << id << " ";
		for (int i : minmax)
		{
			cout << i << ", ";
		}
		cout << endl;
	}

	return "_" + id;
}

Token* Selector::Fixable_Register(Token* r){
	vector<Token*> rs;
	if (r->Size == 1)
	{
		rs = Registers8;
	}
	else if (r->Size == 2)
	{
		rs = Registers16;
	}
	else if (r->Size == 4)
	{
		rs = Registers32;
	}
	else if (r->Size == 8)
	{
		rs = Registers64;
	}
	else if (r->Size == 12)
	{
		rs = Registers128;
	}
	for (Token* i : rs)
		if (i->Name == r->Name)
		{
			return i;
		}
	return nullptr;
}

vector<Token*>& Selector::Get_Register_List(int s){
	if (s == 12)
		return Registers128;
	else if (s == 8)
		return Registers64;
	else if (s == 4)
		return Registers32;
	else if (s == 2)
		return Registers16;
	else
		return Registers8;
}