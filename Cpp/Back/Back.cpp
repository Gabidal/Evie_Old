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
	if ((t->PreFix_Type == "export"))// && (t->Size == 0))
		return t->Name;
	else if (t->Offsetter != nullptr)
	{
		if (t->is(_Pointting_))
		{
			//[address+offsetter*Size]
			return S->Get_ID(to_string(t->Size), "", { t->Size }) + "[" + t->UID + OFFSET + t->Offsetter->UID + SCALE + to_string(t->Size) + "]";
		}
		else if (t->is(_Array_))
		{
			//[(ebp-4)+offsetter*Size]
			return S->Get_ID(to_string(t->Size), "", { t->Size }) + "[(" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name +
				Get_Direction(t) + to_string(t->StackOffset) + ")" +
				OFFSET + t->Offsetter->UID + SCALE + to_string(t->Size) + "]";
		}
	}
	else if (Storing && (t->is(_External_) != true))
		return S->Get_ID(to_string(t->Size), "", { t->Size }) + "[" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name +
		Get_Direction(t) + to_string(t->StackOffset) + "]";
	else if (t->is(_Register_))
		return t->UID;
	else if (t->is(_Number_))
		return S->Get_ID(to_string(t->Size), "", { t->Size}) + t->Name;
	else if (t->is(_Call_))
		return "_" + t->Name;
	else if (t->is(_External_))
		return S->Get_ID(to_string(t->Size), "", { t->Size}) + "[" + t->Name + "]";
	else
		return S->Get_ID(to_string(t->Size), "", {t->Size}) + "[" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name +
		Get_Direction(t) + to_string(t->StackOffset) + "]";
	cout << "Error: Cannot find info for >> " + t->Name + ", " + t->UID << endl;
}

void Back::Make()
{
	vector<int> MinMax;
	for (Token* t : Input->Parameters)
		MinMax.push_back(t->Size);

	bool Storing = Input->ID == "=" || Input->ID == "str";

	string trustFactor;
	if (Input->ID == "label" || Input->ID == "raw_label")
		trustFactor = Input->ID;
	else
		trustFactor = Input->PreFix;

	Output += S->Get_ID(Input->PreFix, trustFactor, MinMax) + S->Get_ID(Input->ID, trustFactor, MinMax);
	for (int i = 0; i < Input->Parameters.size(); i++)
	{
		if (i > 0)
		{
			Output += FROM;
			//Output += S->Get_ID(to_string(Input->Parameters.at(i)->Size));
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
		Output += S->Get_ID("comment", "", {0, 0}) + Input->Comment;
	}
	else
	{
		Make();
	}
}
