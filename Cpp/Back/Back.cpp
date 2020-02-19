#include "../../H/Back/Back.h"
#include "../../H/Selector/Selector.h"
extern Selector* S;
#define _SYSTEM_BIT_TYPE 4


string Back::Get_Agent(bool Storing, Token* t)
{
	//if it is number.
	if (t->is(_Number_))
	{
		return t->Name;
	}
	//first find if this token has a register to it.
	if (S->Get_Belonging_Reg(t->Name) != nullptr)
	{
		return S->Get_Belonging_Reg(t->Name)->Name;
	}
	//then get it from mem.
	if (Storing)
	{
		return Get_Mem_Address(t);
	}
	else
	{
		return S->Get_Reg(t->Size)->Name;
	}
}

void Back::Make(IR* ir, bool Storing)
{
	Output += S->Get_ID(ir->PreFix) + S->Get_ID(ir->ID);
	for (int i = 0; i < ir->Parameters.size(); i++)
	{
		if (i > 0)
		{
			Output += FROM;
			Output += S->Get_ID(to_string(ir->Parameters.at(i)->Size));
		}
		Output += Get_Agent(Storing, ir->Parameters.at(i));
	}
}

string Back::Get_Name(Token* t)
{
	if (t->ID > 0)
	{
		return t->Name + to_string(t->ID);
	}
	else
	{
		return t->Name;
	}
}

string Back::Get_Mem_Address(Token* t)
{
	if (t->is(_External_))
	{
		return "[" + Get_Name(t) + "]";
	}
	else
	{
		return "[" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE) + t->Get_Additive_Operator() + to_string(t->StackOffset) + "]";
	}
}

string Back::Get_Size_Translator(int Size)
{
	return S->Get_ID(to_string(Size));
}
