#include "../../H/Back/Back.h"
#include "../../H/Selector/Selector.h"
extern Selector* S;


string Back::Get_Agent(bool Giver, Token* t)
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
	if (Giver)
	{
		return Get_Mem_Address(t);
	}
	else
	{
		return Get_Reg(t);
	}
}

string Back::Get_Reg(Token* t)
{
	string Reg_Name = S->Registers.at(S->Reg_Turn)->Name;

	Output += S->Get_ID("=") + Reg_Name + FROM + Get_Mem_Address(t) + NL;
	if (S->Reg_Turn > (S->Registers.size() - 1))
	{
		S->Reg_Turn = 0;
	}
	else
	{
		S->Reg_Turn++;
	}
	return Reg_Name;
}

void Back::Make(Token*Dest, Token* Source, string Operator)
{
	Output += S->Get_ID(Operator) + Get_Agent(true, Dest) + FROM + Get_Agent(false, Source) + NL;
}

string Back::Get_Mem_Address(Token* t)
{
	if (t->is(_External_))
	{
		return "[" + t->Name + "]";
	}
	else
	{
		return "[" + S->Get_Right_Reg(Task_For_Type_Address_Basing) + t->Get_Additive_Operator() + to_string(t->StackOffset) + "]";
	}
}