#include "../../H/UI/Safe.h"
#include "../../H/UI/Usr.h"
#include "../../H/BackEnd/Selector.h"
#include "../../H/Docker/Mangler.h"
#include "../../Tests/H/Test_Lexer.h"
#include "../../Tests/H/Test_Back_End.h"
#include "../../H/Parser/Algebra.h"
#include "../../H/Nodes/Node.h"

extern Selector* selector;
extern Usr* sys;
extern Node* Global_Scope;

const string Red = "\x1B[1;31m";
const string Green = "\x1b[1;32m";
const string Yellow = "\x1b[1;33m";
const string Blue = "\x1b[1;34m";
const string Magenta = "\x1b[1;35m";
const string Cyan = "\x1b[1;36m";
const string White = "\x1b[1;37m";
const string Reset = "\x1b[1;0m";

//gather here all the warnings and push them out when a error occurs
//			Cause , Observation
vector<pair<string, vector<Observation>>> Notices;

void Safe::PostProsessor_Factory()
{
	for (auto i : Input) {
		Check_Return_Validity(i);
		Disable_Non_Ptr_Class_Return(i);
		Check_For_Unitialized_Objects(i);
		Warn_Usage_Of_Depricated(i);
		Prefer_Class_Cast_Rather_Object_Cast(i);
		Warn_Usage_Before_Definition(i);
		Check_For_Undefined_Inheritance(i);
	}
}

void Stop() {
	cout << endl;
	throw::runtime_error("ERROR!");
}

void Observation::Report(bool Last)
{
	/*string Head;
	if (Type == ERROR)
		Head = Red + "Error" + Reset + ": ";
	else if (Type == WARNING)
		Head = Yellow + "Warning" + Reset + ": ";
	else if (Type == SOLUTION)
		Head = Green + "Solution" + Reset + ": {\n  ";
	else if (Type == INFO)
		Head = Green + "Notice" + Reset + ": ";

	if (Pos.GetLine() != -1)
		if (Pos.GetFilePath() != nullptr)
			cout << Pos.GetFilePath() << ":" << Pos.GetFriendlyLine() << ":" << Pos.GetFriendlyCharacter() << ": " << Head << Msg << endl;
		else
			cout << Head << Msg << endl;
	else
		cout << Head << Msg << endl;

	if (Type == SOLUTION)
		cout << "}" << endl;
	if ((Type == FAIL || Type == ERROR) && !Dont_Stop)
			throw::runtime_error("ERROR");*/

	//try to find same category of cause
	bool Found_Own_Category = false;
	for (auto& i : Notices) {
		if (i.first == this->Cause) {
			i.second.push_back(*this);
			Found_Own_Category = true;
		}
	}
	//if not found, then create a new category of cause
	if (Found_Own_Category == false) {
		Notices.push_back({ this->Cause, {*this} });
	}
	if (Type == ERROR || Type == FAIL || (sys->Service_Info == Document_Request_Type::ASM && Last)) {
		//flush here:
		for (auto N : Notices) {
			string Result = "";
			//Tell the Severity of this Report.
			if (N.second[0].Type == ERROR)
				Result = Red + "Error" + Reset + ": ";
			else if (N.second[0].Type == WARNING)
				Result = Yellow + "Warning" + Reset + ": ";
			else if (N.second[0].Type == SOLUTION)
				Result = Green + "Solution" + Reset + ": ";
			else if (N.second[0].Type == INFO)
				Result = Green + "Notice" + Reset + ": ";

			string Header = "";
			bool Single_Line_Report = false;

			if (N.second.size() == 1 && N.second[0].Msg == N.first) {
				Single_Line_Report = true;
				Header = string(N.second[0].Pos.GetFilePath()) + ":" + to_string(N.second[0].Pos.GetFriendlyLine()) + ":" + to_string(N.second[0].Pos.GetFriendlyCharacter()) + ": ";
			}

			//Tell the Cause of this report.
			Result += Header + N.first;

			if (!Single_Line_Report)
				Result += " {";

			//List all the reporters and their locations.
			for (auto O : N.second) {
				if (O.Msg == N.first)
					continue;

				Result += "\n  " + string(O.Pos.GetFilePath()) + ":" + to_string(O.Pos.GetFriendlyLine()) + ":" + to_string(O.Pos.GetFriendlyCharacter()) + ": ";

				Result += O.Msg;
			}

			if (!Single_Line_Report)
				Result += "\n}\n";;

			cout << Result << endl;
		}

		Notices.clear();
	}

	if (!Dont_Stop) {
		Stop();
	}
}

void Report(Observation o)
{
	o.Report();
}

void Report(vector<Observation> o)
{
	for (int i = 0; i < o.size(); i++) {
		if (o[i].Type == ERROR || o[i].Type == FAIL) {
			o[i] = Observation(o[i], true);
		}
	}

	for (int i = 0; i < o.size(); i++)
		o[i].Report(i == o.size() - 1);
}

void Report(long type, Lexer_Expectation_Set expectation, string source, vector<Component> result) {
	if (type == SUCCESS) {
		cout << source << Green << " OK " << Reset << endl;
	}
	else if (type == FAIL) {
		cout << source << Red << " FAILED!" << Reset << "\n";
		int s = (int)expectation.Expecations.size();
		if (result.size() < expectation.Expecations.size())
			s = (int)result.size();
		for (int i = 0; i < s; i++) {
			if (expectation.Get_Name(i) != expectation.Get_Name(result[i]))
				cout << "Expected " << expectation.Get_Name(i) << " got " << expectation.Get_Name(result[i]) << "\n";
		}
		cout << endl;
	}
	if (type == FAIL)
		throw::runtime_error("ERROR");
}

void Report(long type, Back_Expectation_Set expectation, string source, vector<Base*> result) {
	if (type == SUCCESS) {
		cout << source << Green << " OK " << Reset << endl;
	}
	else if (type == FAIL) {
		cout << source << Red << " FAILED!" << Reset << "\n";
		int s = (int)expectation.Expecations.size();
		if (result.size() < expectation.Expecations.size())
			s = (int)result.size();
		for (int i = 0; i < s; i++) {
			if (expectation.Get_Name(i) != expectation.Get_Name(result[i]))
				cout << "Expected " << expectation.Get_Name(i) << " got " << expectation.Get_Name(result[i]) << "\n";
		}
		cout << endl;
	}
	if (type == FAIL)
		throw::runtime_error("ERROR");
}

void Safe::Check_Return_Validity(Node* n)
{
	if (n->Name != "return")
		return;
	Node* func = n->Get_Scope_As(FUNCTION_NODE, n->Scope);

	if (n->Right != nullptr) {
		if (!n->Right->Has({ OPERATOR_NODE, ARRAY_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE, CONTENT_NODE})) {
			
			if (n->Right->is(CALL_NODE))
				if (!n->Right->Function_Ptr)
					goto Skip_Size_And_Inheritance;
			n->Right->Size = n->Find(n->Right, n->Scope)->Size;
			n->Right->Inheritted = n->Find(n->Right, n->Scope)->Inheritted;

		Skip_Size_And_Inheritance:;
		}
		if (n->Right->Get_Inheritted("_", false, false, true) == func->Get_Inheritted("_", false, false, true))
			return;
		else if (n->Right->Get_Inheritted("_", true, false, true) == func->Get_Inheritted("_", false, false, true))
			return;
		else if (n->Right->Cast_Type != nullptr && n->Find(n->Right->Cast_Type, n)->Get_Size() == func->Get_Size() && n->Find(n->Right->Cast_Type, n)->Get_Inheritted("_", false, false, true) == func->Get_Inheritted("_", false, false, true))
			return;
		else if (func->Get_Size() == 0) {
			Report(Observation(ERROR, "Can't return '" + n->Right->Get_Inheritted(" ", false, false, true) + "' in function '" + func->Name + "'.", *n->Location, "Value return in non-returning funciton."));
		}
		else {
			Report({
				Observation(ERROR, "Incorrect return type!", *n->Location, "Incorrect return type!"),
				//Observation(WARNING, "Return type '" + n->Right->Get_Inheritted(" ", false, false, true) + " ' does not mach with '" + func->Get_Inheritted(" ", false, false, true) + " '.", *n->Right->Location, "Incorrect return type!"),
				Observation(SOLUTION, "Try casting '" + n->Right->Get_Inheritted(" ", false, false, true) + " ' to '" + func->Get_Inheritted(" ", false, false, true) + " '." , *n->Right->Location, "Incorrect return type!")
				});
		}
	}
	else if (func->Get_Size() != 0 && !func->is("func")){
		Report(Observation(ERROR, func->Name + " needs to return something", *n->Location, "Non-void function needs returning value."));
	}
}

void Safe::Disable_Non_Ptr_Class_Return(Node* n)
{
	if (!n->is(FUNCTION_NODE) && !n->is(IMPORT))
		return;
	if (n->is("ptr"))
		return;
	if (n->Is_Template_Object)
		return;
	if (MANGLER::Is_Based_On_Base_Type(n))
		return;

	if (n->Find(n, n->Scope)->Size > selector->Get_Largest_Register_Size()) {
		Report(Observation(ERROR, n->Name, *n->Location, "non-ptr return exeeds size of " + to_string(_SYSTEM_BIT_SIZE_) + " Bits."));
	}
}

void Safe::Check_For_Unitialized_Objects(Node* func)
{
	//go through the code inside this function and try to find '=' operators-
	//that set the object in question an initial value.
	if (!func->is(FUNCTION_NODE))
		return;

	for (auto v : func->Defined) {
		if (v->is(PARAMETER_NODE))
			continue;
		for (auto c : func->Childs) {
			for (auto n : c->Get_all(ASSIGN_OPERATOR_NODE)) {
				if (n->Left->Name == v->Name)
					goto Next_Variable;
			}
			//constructor callation
			for (auto n : c->Get_all(CALL_NODE)) {
				if (n->Parameters.size() > 0 && n->Parameters[0]->Name == v->Name)
					if (n->Name == v->Inheritted[0])
						goto Next_Variable;
			}
		}

		
		Report({
			Observation(WARNING, "Usage of uninitialized object is dangerous!", *v->Location, ""),
			Observation(SOLUTION, "Call constructor of '" + v->Name + "' to initialize it.", *v->Location, "Usage of uninitialized object is dangerous!"),
		});

	Next_Variable:;
	}
}

void Safe::Warn_Usage_Of_Depricated(Node* n)
{
	if (n->Has({ FUNCTION_NODE, IMPORT, EXPORT, PROTOTYPE, CLASS_NODE }))
		return;

	COMMENT* Comment = nullptr;

	if (n->is(CALL_NODE) && !n->Function_Ptr)
		Comment = &n->Function_Implementation->Comment;
	else if (n->Has({OBJECT_NODE, OBJECT_DEFINTION_NODE}))
		Comment = &n->Find(n, n)->Comment;

	if (!Comment || Comment->Deprication_Information == "")
		return;

	Report(Observation(WARNING, Comment->Deprication_Information, *n->Location, ""));
}

void Safe::Prefer_Class_Cast_Rather_Object_Cast(Node* n)
{
	if (n->Cast_Type == nullptr || n->Cast_Type->Name == "address")
		return;
	//check here if the cast type is a class or a object
	Node* Cast = n->Find(n->Cast_Type, n);
	if (!Cast->is(CLASS_NODE)) {
		Report(Observation(WARNING, "Cast" + n->Name +  " with 'type " + Cast->Get_Inheritted(" ", false, false, false) + " " + Cast->Name + "{}'", *Cast->Location, "Non-Class based casting"));
	}
}

void Safe::Warn_Usage_Before_Definition(Node* n)
{
	if (!n->is(OBJECT_NODE))
		return;
	Node* Definition = n->Find(n, n->Scope);

	if (Definition == nullptr)
		return;

	if (Definition->Location->GetAbsolute() > n->Location->GetFriendlyAbsolute() && Definition->Location->GetFilePath() == n->Location->GetFilePath()) {
		Report(Observation(ERROR, "Usage of local variable '" + n->Name + "' before definition at line '" + to_string(Definition->Location->GetFriendlyLine()) + "'.", *n->Location, "Usage of variable before its definition"));
	}
}

void Safe::Parser_Factory()
{
	Reference_Count_Type_Un_Availability();
}

void Safe::Reference_Count_Type_Un_Availability()
{
	for (auto& i : Global_Scope->Defined) {
		if (MANGLER::Is_Base_Type(i)) {
			i->Update_Size();
		}
	}

	Node* Reference_Count_Type = Global_Scope->Find(sys->Info.Reference_Count_Size, Global_Scope, CLASS_NODE, "integer", true);

	if (Reference_Count_Type == nullptr) {
		Report({
			Observation(ERROR, "Not found an integer at size '" + to_string(sys->Info.Reference_Count_Size) + "' for Reference_Count.", Position(), "Not found an integer at size '" + to_string(sys->Info.Reference_Count_Size) + "' for Reference_Count."),
			Observation(SOLUTION, "type [name]{\n    size = " + to_string(sys->Info.Reference_Count_Size) + "\n  }", Position(), "Not found an integer at size '" + to_string(sys->Info.Reference_Count_Size) + "' for Reference_Count.")
		});
	}
}

void Safe::Check_For_Undefined_Inheritance(Node* n)
{
	for (auto i : n->Inheritted) {
		//ignore keywords
		for (auto j : Lexer::Keywords)
			if (i == j)
				goto Next;
		//ignore template inheritances
		for (auto j : n->Templates)
			if (i == j->Name)
				goto Next;
		for (auto j : n->Inheritable_templates)
			if (i == j->Name)
				goto Next;
		//
		if (n->Find(i, n) == nullptr) {
			Report(Observation(ERROR, "Usage of un-declared type '" + i + "'.", *n->Location, ""));
		}
	Next:;
	}
}
