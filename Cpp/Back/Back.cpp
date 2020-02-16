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

void Back::Make(Token*Dest, Token* Source, string Operator, bool Storing)
{
	if (Source == nullptr)
	{
		Output += S->Get_ID(Operator) + Get_Agent(Storing, Dest) + NL;
	}
	else
	{
		Output += S->Get_ID(Operator) + Get_Agent(Storing, Dest) + FROM + Get_Size_Translator(Source->Size) + Get_Agent(false, Source) + NL;
	}
}

string Back::Get_Mem_Address(Token* t)
{
	if (t->is(_External_))
	{
		return "[" + t->Name + "]";
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
