#include "../../H/Parser/Analyzer.h"
#include "../../H/Parser/Algebra.h"

extern bool Optimized;

Analyzer::Analyzer()
{
	Factory();
}

void Analyzer::Factory()
{
	//gather information about the AST that we have made
	Detect_Abnormal_Start_Address();
	List_All_Exported();

	for (auto* f : Start_Of_Proccesses) {
		Calling_Count_Incrementer(f);
	}
}

void Analyzer::Detect_Abnormal_Start_Address()
{
	if (sys->Info.Format == "exe") {
		Node* Main = Global_Scope->Find("main", Global_Scope, FUNCTION_NODE);

		if (Main)
			Start_Of_Proccesses.push_back(Main);
	}
}

void Analyzer::List_All_Exported()
{
	for (auto *f : Global_Scope->Defined)
		if (f->is(FUNCTION_NODE) && f->is("export"))
			Start_Of_Proccesses.push_back(f);
}

vector<Node*> Callin_Trace;
void Analyzer::Calling_Count_Incrementer(Node* f)
{
	for (auto* i : Callin_Trace)
		if (i == f)
			return;

	Callin_Trace.push_back(f);

	if (f->Is_Template_Object)
		return;

	//nevertheless we always want to increment the calling count 
	//be it by the start list, or calld for.
	f->Calling_Count++;

	for (auto* c : f->Childs) {
		for (auto* i : c->Get_all({CALL_NODE})) {
			Calling_Count_Incrementer(i->Function_Implementation);
		}
	}

	Callin_Trace.pop_back();
}

void Analyzer::Call_Algebra(Node* n)
{
	while (true) {
		Algebra a(n->Scope, &n->Childs);
		if (!Optimized)
			break;
		Optimized = false;
	}
}
