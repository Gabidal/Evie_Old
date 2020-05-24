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

string Back::Get_Handler(Token* t)
{
	if (t->is(_Register_))
	{
		return t->UID;
	}
	else if (t->is(_External_) || t->is(_Number_))
	{
		if (t->is("import") || t->is("export") || t->is(_Number_))
			return t->Name;
		return "_" + t->Name;
	}
	else
	{
		return S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name +
			Get_Direction(t) + to_string(t->StackOffset);
	}
	return "";
}

string Back::Get_Frame(string inside){
	if (storing)
	{
		return "[" + inside + "]";
	}
	else
	{
		return inside;
	}
}

string Back::Get_Address(Token* t){
	if (t->is(_External_)){
		return "(" + Get_Handler(t) + ")";
	}
	else
	{
		return "(" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name +
				Get_Direction(t) + to_string(t->StackOffset) + ")";
	}
	return "";
}

string Back::Get_Call(Token* t){
	if (t->is("func") || t->State == "func")
	{
		return Get_Handler(t);
	}
	else
	{
		return "[" + Get_Handler(t) + "]";
	}
}

string Back::Get_Info_Of(Token* t)
{
	if (t->is("export") || t->is("import"))// && (t->Size == 0))
		return t->Name;
	else if (t->Offsetter != nullptr)
	{
		if (t->_Has_Member_) {
			//[(ebp-4)+offsetter]
			return S->Get_ID(to_string(_SYSTEM_BIT_TYPE), "", { _SYSTEM_BIT_TYPE }) + "[" + Get_Address(t) +
				OFFSET + Get_Handler(t->Offsetter) + "]";
		}
		else if (t->is(_Pointting_))
		{
			//[address+offsetter*Size]
			return S->Get_ID(to_string(t->Size), "", { t->Size }) + "[" + Get_Handler(t) + OFFSET + Get_Handler(t->Offsetter) + SCALE + to_string(t->Hidden_Size) + "]";
		}
		else if (t->is(_Array_))
		{
			//[(ebp-4)+offsetter*Size]
			return S->Get_ID(to_string(t->Size), "", { t->Size }) + "[" + Get_Address(t) +
				OFFSET + Get_Handler(t->Offsetter) + SCALE + to_string(t->Size) + "]";
		}
	}
	else if (t->is(_Giving_Address_) && (t->Context == "Global Scope"))
	{
		return Get_Address(t);
	}
	else if (storing && !t->is(_External_))
		//return S->Get_ID(to_string(t->Size), "", { t->Size }) + "[" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name + 
		//Get_Direction(t) + to_string(t->StackOffset) + "]";
		return Get_Frame(Get_Handler(t));
	else if (t->is(_Register_))
		return t->UID;
	else if (t->is(_Number_))
		return Get_Size(t) + t->Name;
	else if (t->is(_String_))
		return t->Name;			//change into the S1 pointters!!!
	else if (t->is(_Call_))
		return Get_Call(t);
	else if (t->is(_External_))
		return S->Get_ID(to_string(t->Size), "", { t->Size}) + "[" + Get_Handler(t) + "]";
	else
		return S->Get_ID(to_string(t->Size), "", {t->Size}) + "[" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name +
		Get_Direction(t) + to_string(t->StackOffset) + "]";
	cout << "Error: Cannot find info for " << t->Name << ". Used at line" << t->Line_Number << endl;
	return "";
}

string Back::Get_Size(Token* t)
{
	if (!t->is(_Locked_))
	{
		return S->Get_ID(to_string(t->Size), "", { t->Size });
	}
	return "";
}

void Back::Make()
{
	vector<int> MinMax;
	for (Token* t : Input->Parameters)
		MinMax.push_back(t->Size);

	storing = Input->ID == "=" || Input->ID == "str";

	string trustFactor;
	if (Input->ID == "label" || Input->ID == "raw_label")
		trustFactor = Input->ID;
	else
		trustFactor = Input->PreFix;

	//make the opcode and add the syntax tab
	Output += Input->Tabs + S->Get_ID(Input->PreFix, trustFactor, MinMax) + S->Get_ID(Input->ID, trustFactor, MinMax);
	for (int i = 0; i < (int)Input->Parameters.size(); i++)
	{
		if (i > 0)
		{
			Output += FROM;
			//Output += S->Get_ID(to_string(Input->Parameters.at(i)->Size));
		}
		Output += Get_Info_Of(Input->Parameters.at(i));
		//only the first can be giving the Storing parameter.
		storing = false;
	}
}

void Back::Factory()
{
	if (Input->Comment != "")
	{
		Output += S->Get_ID("comment", "", {0, 0}) + Input->Comment;
		Output += "\n";
	}
	Make();
}
