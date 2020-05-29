#include "../../H/Back/Comment.h"

void Comment::Factory()
{
}

void Comment::Make_Context()
{
}

void Comment::Gather_Subroutins()
{
	for (stirng s : Subroutins) {

	}
}

string Comment::Get_Info_From_AST(Token* t)
{
	//a = b + 1
	string Result = "";
	//first filter all complex stuff away.
	if (t->is(_Operator_)) {
		Subroutins.push_back(Get_Info_From_Token(t->Left_Side_Token));
		Subroutins.push_back(Get_Info_From_Token(t->Right_Side_Token));
	}
	for (Token* i : t->Childs)
		Subroutins.push_back(Get_Info_From_Token(i));
	if (t->Name_Of_Same_Using_Register) {
		//this means this token is on left side of the =
		return Get_Token_Info(t) + " is getting the value of " + t->Name_Of_Same_Using_Register;
	}
	if (t->is(_Number_)) {
		return Get_Token_Info(t);
	}
	return string();
}

string Comment::Get_Token_Info(Token* t)
{
	string r = "";
	if (t->is(_Giving_Address_))
		r += "@";
	r += t->Name;
	if (t->is(_Pointting_))
		r += "[" + Get_Token_Info(t->Offsetter) + "]";
	if (t->is(_Array_))
		r += ":" + Get_Token_Info(t->Offsetter);
	return r;
}

string Comment::Get_Comment()
{
	return string();
}
