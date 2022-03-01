#include "../../H/Nodes/Token.h"
#include "../../H/BackEnd/Selector.h"
#include "../../H/UI/Usr.h"
#include "../../H/UI/Safe.h"
#include "../../H/Docker/Mangler.h"

extern Selector* selector;
extern Usr* sys;

Token::Token(Node* n, bool Skip_Needed_Address_Protocol) {
	if (n->is(OBJECT_NODE) || n->is(OBJECT_DEFINTION_NODE)) {
		if (n->Find(n, n->Scope)->Scope->is("static") || n->is("static") || (n->Fetcher && n->Fetcher->is("static")) || n->Find(n, n->Scope)->Has({FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT}))
			Flags = TOKEN::GLOBAL_VARIABLE | TOKEN::CONTENT;
		else if (n->Find(n, n->Scope)->Requires_Address)
			Flags = TOKEN::CONTENT;
		else
			Flags = TOKEN::REGISTER;

		if (n->Find(n, n)->Format == "decimal")
			Flags |= TOKEN::DECIMAL;
	}
	else if (n->is(NUMBER_NODE)) {
		Flags = TOKEN::NUM;
		if (n->Format == "decimal") {
			Flags |= TOKEN::DECIMAL;
			Has_Floating_Point_Value = true;
		}
		//This not needed anymore, because Algebra does this nowdays.
		/*if (n->Coefficient == -1)
			n->Name = "-" + n->Name;*/
	}
	else if (n->is(PARAMETER_NODE)) {
		//first get the index this paremet is
		int Max_Integer_Registers = selector->Get_Numerical_Parameter_Register_Count(n->Get_Scope_As(FUNCTION_NODE, n->Scope)->Parameters);
		int Current_Integer_Register_Count = 0;
		int Max_Floating_Registers = selector->Get_Floating_Parameter_Register_Count(n->Get_Scope_As(FUNCTION_NODE, n->Scope)->Parameters);
		int Current_Float_Register_Count = 0;

		bool Requires_Address = n->Find(n, n->Scope)->Requires_Address && !Skip_Needed_Address_Protocol;

		//find the curresponding register
		for (int i = 0; i < n->Get_Scope_As(FUNCTION_NODE, n->Scope)->Parameters.size(); i++) {
			if (n->Get_Scope_As(FUNCTION_NODE, n->Scope)->Parameters[i]->Name == n->Name) {
				if (n->Get_Scope_As(FUNCTION_NODE, n->Scope)->Parameters[i]->Format == "decimal") {
					if (Current_Float_Register_Count < Max_Floating_Registers && !Requires_Address) {
						Flags = TOKEN::REGISTER | TOKEN::DECIMAL | TOKEN::PARAMETER;
						Parameter_Index = i;
					}
					else
						Flags = TOKEN::CONTENT | TOKEN::DECIMAL;
					break;
				}
				else {
					if (Current_Integer_Register_Count < Max_Integer_Registers && !Requires_Address) {
						Flags = TOKEN::REGISTER | TOKEN::PARAMETER;
						Parameter_Index = i;
					}
					else
						Flags = TOKEN::CONTENT;
					break;
				}
			}
			if (n->Get_Scope_As(FUNCTION_NODE, n->Scope)->Parameters[i]->Format == "decimal")
				Current_Float_Register_Count++;
			else
				Current_Integer_Register_Count++;
		}
	}
	else if (n->is(STRING_NODE))
		Flags = TOKEN::STRING;
	else if (n->is(LABEL_NODE)) {
		Flags = TOKEN::LABEL;
		n->Size = _SYSTEM_BIT_SIZE_;//for giving the address
	}
	else
		return;
	Size = n->Find(n, n->Scope)->Size;

	Name = n->Name;

	if (n->is(NUMBER_NODE) && n->Format == "decimal") {
		double tmp = atof(n->Name.c_str());

		Name = to_string(*(long long*)&tmp);
	}

	if (n->Find(n, n->Scope)->Has({ FUNCTION_NODE, IMPORT, EXPORT }))
		Name = MANGLER::Mangle(n->Function_Implementation, "");

	if ((n->Find(n, n)->is("static")))
		Name = n->Scope->Name + "_" + Name;

	Parent = n->Scope;

	if (Flags == 0)
		Report(Observation(ERROR, "Internal error! Missing Flag in token " + Name, Position()));
}

vector<Token*> Token::Get_All(vector<long long> F)
{
	vector<Token*> Result;
	for (auto i : F) {
		vector<Token*> Tmp = Get_All(i);
		Result.insert(Result.begin(), Tmp.begin(), Tmp.end());
	}
	return Result;
}

vector<Token*> Token::Get_All(long long F)
{
	vector<Token*> Result;
	for (auto i : Childs) {
		vector<Token*> Tmp = i->Get_All(F);
		Result.insert(Result.begin(), Tmp.begin(), Tmp.end());
	}	
	for (auto i : Parameters) {
		vector<Token*> Tmp = i->Get_All(F);
		Result.insert(Result.begin(), Tmp.begin(), Tmp.end());
	}
	if (Left) {
		vector<Token*> Tmp = Left->Get_All(F);
		Result.insert(Result.begin(), Tmp.begin(), Tmp.end());
	}
	if (Right) {
		vector<Token*> Tmp = Right->Get_All(F);
		Result.insert(Result.begin(), Tmp.begin(), Tmp.end());
	}

	if (this->is(F))
		Result.push_back(this);

	return Result;
}
