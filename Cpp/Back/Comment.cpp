#include "../../H/Back/Comment.h"

void Comment::Factory()
{
}

void Comment::Detect_Complex_Numbers(Token* n)
{
	if (!n->is(_Number_))
		return;
	if (n->Name.find('.') == -1)
		return;
	//size 4 == normal numbers
	//size 8 == big numbers
	//size 12 == complex numbers/ floating point ones
	int value = atoi(n->Name.c_str());
	Output.push_back("If it's value is broken here have this " + to_string(*(float*)&value) + ".");
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
	for (string s : t->Comments)
		Output.push_back(s);
	return r;
}