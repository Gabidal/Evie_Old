#include "../../H/Back/Back.h"
#include "../../H/Selector/Selector.h"
extern Selector* S;
extern int _SYSTEM_BIT_TYPE;
string Context = "";

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
		if (t->is("import") || t->is("export") || t->is(_Number_) || t->is("mangle"))
			return t->Name;
		return "_" + t->Name;
	}
	else if (t->is(Task_For_Type_Address))
	{
		return S->Get_Right_Reg(Task_For_Type_Address, _SYSTEM_BIT_TYPE)->Name +
			Get_Direction(t) + to_string(t->StackOffset);
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

string Back::Get_Address(Token* t) {
	string left_parathesis_type = "(";
	string right_paranthesis_type = ")";
	if (Context == "outline") {
		left_parathesis_type = "[";
		right_paranthesis_type = "]";
	}
	if (t->is(_External_)) {
		return left_parathesis_type + Get_Handler(t) + right_paranthesis_type;
	}
	else
	{
		return left_parathesis_type + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name +
			Get_Direction(t) + to_string(t->StackOffset) + right_paranthesis_type;
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
			//[ebp-offsetter]
			return S->Get_ID(to_string(_SYSTEM_BIT_TYPE), "", { _SYSTEM_BIT_TYPE }) + "[" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE)->Name +
				Get_Direction(t) + Get_Handler(t->Offsetter) + "]";
		}
		else if (t->is(_Pointting_))
		{
			//[address+offsetter*Size]
			return S->Get_ID(to_string(t->Size), "", { t->Size }) + "[" + Get_Handler(t) + Get_Direction(t) + Get_Handler(t->Offsetter) + SCALE + to_string(t->Hidden_Size) + "]";
		}
		else if (t->is(_Array_))
		{
			//[(ebp-4)+offsetter*Size]
			return S->Get_ID(to_string(t->Size), "", { t->Size }) + "[" + Get_Address(t) +
				Get_Direction(t) + Get_Handler(t->Offsetter) + SCALE + to_string(t->Size) + "]";
		}
	}
	else if (t->is(_Giving_Address_) && (t->Context == "Global Scope"))
	{
		Context = "outline";
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
	else if (t->_Give_String_Address_)
		return "_" + t->Name;		//usually string name is the same as the stirng adress
	else if (t->_RAW_STRING_)
		return "\"" + t->Name + "\"";
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

	Context = Input->ID;
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
	Comment c(Input);
	for (string i : c.Output){
		Output += S->Get_ID("comment", "", {0, 0}) + i;
		Output += "\n";
	}
	Make();
}
