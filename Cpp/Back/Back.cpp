#include "../../H/Back/Back.h"
#include "../../H/Selector/Selector.h"
extern Selector* S;
extern int _SYSTEM_BIT_TYPE;

string Back::Get_Direction(Token* t)
{
	if (t->is(_Parameter_))
	{
		return " + ";
	}
	else
	{
		return " - ";
	}
}

string Back::Get_Info_Of(Token* t, bool Storing)
{
	if (Storing)
		return "[" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name +
		Get_Direction(t) + to_string(t->StackOffset) + "]";
	else if (S->Get_Belonging_Reg(t->Name) != nullptr)
		return S->Get_Belonging_Reg(t->Name)->Name;
	else if (t->is(_Number_))
		return t->Name;
	else if (t->is(_External_))
		return "[" + t->Name + "]";
	else
		return "[" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name +
		Get_Direction(t) + to_string(t->StackOffset) + "]";
}

void Back::Load_To_Reg()
{
	Input->Parameters.at(0)->Reg = S->Get_Right_Reg(Input->Reg_Flag, Input->Parameters.at(0)->Size);

	Output += S->Get_ID("ldr") + Input->Parameters.at(0)->Reg->Name +
		FROM + S->Get_ID(to_string(Input->Parameters.at(0)->Size)) + Get_Info_Of(Input->Parameters.at(0), false) + NL;
	Handle = S->Get_Right_Reg(Input->Reg_Flag, Input->Parameters.at(0)->Size);
	Input->Parameters.at(0)->Reg->Base = Input->Parameters.at(0);
}

void Back::Store_To_Reg()
{
	Input->Parameters.at(0)->Reg = S->Get_Right_Reg(Input->Reg_Flag, Input->Parameters.at(0)->Size);

	Output += S->Get_ID("str") + Get_Info_Of(Input->Parameters.at(0), true) + FROM +
		Input->Parameters.at(0)->Reg->Name + NL;
	Input->Parameters.at(0)->Reg->Base = Input->Parameters.at(0);
}

void Back::Make()
{
	bool Storing = Input->ID == "=" || Input->ID == "str";
	Output += S->Get_ID(Input->PreFix, Input->ID) + S->Get_ID(Input->ID);
	for (int i = 0; i < Input->Parameters.size(); i++)
	{
		if (i > 0)
		{
			Output += FROM;
			Output += S->Get_ID(to_string(Input->Parameters.at(i)->Size));
		}
		Output += Get_Info_Of(Input->Parameters.at(i), Storing);
		//only the first can be giving the Storing parameter.
		Storing = false;
	}
}

void Back::Factory()
{
	if (Input->Comment != "")
	{
		Output += S->Get_ID("comment") + Input->Comment;
	}
	if (Input->is(_Load_To_Reg))
	{
		Load_To_Reg();
	}
	else if (Input->is(_Store_To_Reg))
	{
		Store_To_Reg();
	}
	else
	{
		Make();
	}
}
