#include "..\..\H\UI\Safe.h"
#include "../../H/BackEnd/Selector.h"
#include "../../H/Docker/Mangler.h"
#include "../../Tests/H/Test_Lexer.h"

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
	}
}

void Stop() {
	throw::exception("ERROR!");
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

	if (Pos.GetFilePath() != nullptr)
		cout << Pos.GetFilePath() << ":" << Pos.GetFriendlyLine() << ":" << Pos.GetFriendlyCharacter() << ": " << Head << Msg << endl;
	else
		cout << Head << Msg << endl;
	if (Type == SOLUTION)
		cout << "}" << endl;
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

void Report(long type, Lexer_Expectation expectation, string source, vector<Component> result) {
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
}

void Safe::Check_Return_Validity(Node* n)
{
	if (n->Name != "return")
		return;
	Node* func = n->Get_Parent_As(FUNCTION_NODE, n->Parent);
	func->Update_Size_By_Inheritted();
	n->Right->Update_Size_By_Inheritted();
	if (n->Right != nullptr) {
		if (n->Right->Get_Size() == func->Get_Size() && n->Right->Get_Inheritted("_", false, false, true) == func->Get_Inheritted("_", false, false, true)) {
			return;
		}
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
	else if (func->Get_Size() != 0){
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
	if (MANGLER::Is_Based_On_Base_Type(n))
		return;

	n->Update_Size_By_Inheritted();

	if (n->Size > selector->Get_Largest_Register()) {
		Report({
			Observation(ERROR, "Return object is bigger than: " + to_string(_SYSTEM_BIT_SIZE_ * 8), *n->Location),
			Observation(SOLUTION, "Please return the object as a pointter", *n->Location)
			});
		throw::exception("ERROR!");
	}
}
