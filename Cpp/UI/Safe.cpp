#include "../../H/UI/Safe.h"
#include "../../H/BackEnd/Selector.h"
#include "../../H/Docker/Mangler.h"
#include "../../Tests/H/Test_Lexer.h"
#include "../../Tests/H/Test_Back_End.h"

extern Selector* selector;

const string Red = "\x1B[1;31m";
const string Green = "\x1b[1;32m";
const string Yellow = "\x1b[1;33m";
const string Blue = "\x1b[1;34m";
const string Magenta = "\x1b[1;35m";
const string Cyan = "\x1b[1;36m";
const string White = "\x1b[1;37m";
const string Reset = "\x1b[1;0m";

void Safe::Factory()
{
	for (auto i : Input) {
		Check_Return_Validity(i);
		Disable_Non_Ptr_Class_Return(i);
		Check_For_Unitialized_Objects(i);
		Warn_Usage_Of_Depricated(i);
	}
}

void Stop() {
	throw::runtime_error("ERROR!");
}

void Observation::Report()
{
	string Head;
	if (Type == ERROR)
		Head = Red + "Error" + Reset + ": ";
	else if (Type == WARNING)
		Head = Yellow + "Warning" + Reset + ": ";
	else if (Type == SOLUTION)
		Head = Green + "Solution" + Reset + ": {\n  ";
	else if (Type == INFO)
		Head = Green + "Notice" + Reset + ": ";

	if (Pos.GetFilePath() != nullptr)
		cout << Pos.GetFilePath() << ":" << Pos.GetFriendlyLine() << ":" << Pos.GetFriendlyCharacter() << ": " << Head << Msg << endl;
	else
		cout << Head << Msg << endl;
	if (Type == SOLUTION)
		cout << "}" << endl;
	if (Type == FAIL || Type == ERROR)
		throw::runtime_error("ERROR");
}

void Report(Observation o)
{
	o.Report();
}

void Report(vector<Observation> o)
{
	for (auto i : o)
		i.Report();
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
	Node* func = n->Get_Parent_As(FUNCTION_NODE, n->Scope);

	if (n->Right != nullptr) {
		if (!n->Right->Has({ OPERATOR_NODE, ARRAY_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE }))
			n->Right->Size = n->Find(n->Right, n->Scope)->Size;
		if (n->Right->Get_Size() == func->Get_Size() && n->Right->Get_Inheritted("_", false, false, true) == func->Get_Inheritted("_", false, false, true))
			return;
		else if (n->Right->Get_Inheritted("_", true, false, true) == func->Get_Inheritted("_", false, false, true))
			return;
		else if (n->Right->Cast_Type != "" && n->Find(n->Right->Cast_Type, n, CLASS_NODE)->Get_Size() == func->Get_Size() && n->Find(n->Right->Cast_Type, n, CLASS_NODE)->Get_Inheritted("_", false, false, true) == func->Get_Inheritted("_", false, false, true))
			return;
		else if (func->Get_Size() == 0) {
			Report(Observation(ERROR, "Cant return value in non-returning funciton.", *n->Location));
			Stop();
		}
		else {
			Report({
				Observation(ERROR, "Incorrect return type!", *n->Location),
				Observation(WARNING, n->Right->Name + " does not match " + func->Name + " return type.", *n->Right->Location),
				Observation(SOLUTION, "Try changing " + n->Right->Name + " type into " + func->Find(func->Get_Size(), func, CLASS_NODE, n->Right->Format)->Name + " or try casting it." , *n->Right->Location)
				});
			Stop();
		}
	}
	else if (func->Get_Size() != 0 && func->is("func") == -1){
		Report(Observation(ERROR, "Non-void function needs returning value.", *n->Location));
		Stop();
	}
}

void Safe::Disable_Non_Ptr_Class_Return(Node* n)
{
	if (!n->is(FUNCTION_NODE) && !n->is(IMPORT))
		return;
	if (n->is("ptr") != -1)
		return;
	if (n->Is_Template_Object)
		return;
	if (MANGLER::Is_Based_On_Base_Type(n))
		return;

	if (n->Find(n, n->Scope)->Size > selector->Get_Largest_Register()) {
		Report({
			Observation(ERROR, "Return object is bigger than: " + to_string(_SYSTEM_BIT_SIZE_ * 8), *n->Location),
			Observation(SOLUTION, "Please return the object as a pointter", *n->Location)
			});
		throw::runtime_error("ERROR!");
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
			Observation(WARNING, "Usage of uninitialized object is dangerous!", *v->Location),
			Observation(SOLUTION, "Call constructor of '" + v->Name + "' to initialize it.", *v->Location),
		});

	Next_Variable:;
	}
}

void Safe::Warn_Usage_Of_Depricated(Node* n)
{
	if (n->Comment == "")
		return;

	regex expression("Depricated:.+");
	smatch matches;
	string Buffer = n->Comment;
	if (regex_search(Buffer, matches, expression)) {
		for (auto i : matches) {
			Report(Observation(WARNING, i.str(), *n->Location));
		}
	}
}
