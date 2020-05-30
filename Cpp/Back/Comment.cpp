#include "../../H/Back/Comment.h"

void Comment::Make_Context()
{
	return;
}

void Comment::Gather_Subroutins()
{
	for (Token* i : OPCode->Parameters)
		Sub_Content += Get_Token_Info(i) + " ";
	if (Sub_Content != "")
		OPCode->Comments.push_back(Sub_Content);
	return;
}

void Comment::Make_Comment()
{
	Make_Context();
	Gather_Subroutins();
	return;
}

string Comment::Get_Token_Info(Token* t)
{
	//string r = (string)"[SIZE " + to_string(t->Size) + "]";
	string r = "";
	if (t->is(_Giving_Address_))
		r += "@";
	r += t->Name;
	if (t->is(_Pointting_))
		r += "[" + Get_Token_Info(t->Offsetter) + "]";
	if (t->is(_Array_))
		r += ":" + Get_Token_Info(t->Offsetter);
	if (t->Name_Of_Same_Using_Register != "")
		r += " gets value of " + t->Name_Of_Same_Using_Register;
	if (t->Comment != "")
		OPCode->Comments.push_back(t->Comment);
	return r;
}