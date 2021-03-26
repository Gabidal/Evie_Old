#include "../../H/Nodes/Token.h"
#include "../../H/BackEnd/Selector.h"
#include "../../H/UI/Usr.h"

extern Selector* selector;
extern Usr* sys;

Token::Token(Node* n) {
	if (n->is(OBJECT_NODE) || n->is(OBJECT_DEFINTION_NODE)) {
		if (n->Find(n, n->Scope)->Scope->Name == "GLOBAL_SCOPE" || n->is("static") != -1 || (n->Fetcher != nullptr && n->Fetcher->is("static") != -1))
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
		if (n->Coefficient == -1)
			n->Name = "-" + n->Name;
	}
	else if (n->is(PARAMETER_NODE)) {
		//first get the index this paremet is
		int Max_Integer_Registers = selector->Get_Numerical_Parameter_Register_Count(n->Scope->Parameters);
		int Current_Integer_Register_Count = 0;
		int Max_Floating_Registers = selector->Get_Floating_Parameter_Register_Count(n->Scope->Parameters);
		int Current_Float_Register_Count = 0;

		bool Requires_Address = n->Find(n, n->Scope)->Requires_Address;

		//find the curresponding register
		for (int i = 0; i < n->Scope->Parameters.size(); i++) {
			if (n->Scope->Parameters[i]->Name == n->Name) {
				if (n->Find(n->Scope->Parameters[i]->Name)->Format == "decimal") {
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
			if (n->Find(n->Scope->Parameters[i]->Name)->Format == "decimal")
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
	n->Find(n, n->Scope)->Update_Size_By_Inheritted();
	Size = n->Find(n, n->Scope)->Size;

	Name = n->Name;

	if (n->is("static") != -1 || (n->Fetcher != nullptr && n->Fetcher->is("static") != -1))
		Name = n->Fetcher->Name + "_" + n->Name;

	Parent = n->Scope;
}