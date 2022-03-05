#include "../../H/Parser/Analyzer.h"
#include "../../H/Parser/Algebra.h"
#include "../../H/Parser/Memory_Manager.h"

extern bool Optimized;

Analyzer::Analyzer()
{
	Factory();
}

void Analyzer::Factory()
{
	//gather information about the AST that we have made
	Safe::Go_Through_AST(Safe::Report_Missing_Cast);
	Safe::Flush_Errors();
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

void Analyzer::Analyze_Class(Node* c)
{

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

	/*f->Modify_AST(f, [](Node* a) { return true; }, [](Node*& n) {
		Optimized = true;
		while (Optimized) {
			Optimized = false;
			Algebra a(n, &n->Childs);
		}
	});*/

	//Define_Sizes(f);

	if (!sys->Info.Is_Service || sys->Service_Info == Document_Request_Type::ASM)
		for (auto& v : f->Defined)
			for (auto j : f->Childs) {
				Analyze_Variable_Address_Pointing(v, j);
				if (v->Requires_Address)
					break;
			}

	//do function memorry handling stuff
	Memory_Manager m(f);

	//
	for (auto* i : f->Defined) {
		for (auto* j : i->Get_Inheritted_Node_List()) {
			m = Memory_Manager(j);
		}
	}

	Define_Sizes(f);

	//repeat this for its calling as so on...
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

void Analyzer::Analyze_Variable_Address_Pointing(Node* v, Node* n)
{
	if (!v->Has({ OBJECT_DEFINTION_NODE, OBJECT_NODE, PARAMETER_NODE }))
		return;

	//if a variable is pointed to via a pointter or a function parameter address loader, use stack.
	//Other than that use registers.
	if (n->Has({ ASSIGN_OPERATOR_NODE, OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE, LOGICAL_OPERATOR_NODE })) {
		Analyze_Variable_Address_Pointing(v, n->Left);
		if (v->Requires_Address)
			return;
		Analyze_Variable_Address_Pointing(v, n->Right);
		if (v->Requires_Address)
			return;

		int Right_ptr = Get_Amount("ptr", n->Right);
		int Left_ptr = Get_Amount("ptr", n->Left);
		//TODO!! need better contex idea for what is the result be as ptr amount?!!
		if (Right_ptr > Left_ptr && n->Left->Name == v->Name) {
			v->Requires_Address = true;
		}
		if (Left_ptr > Right_ptr && n->Right->Name == v->Name) {
			v->Requires_Address = true;
		}
	}
	else if (n->is(CONTENT_NODE))
		for (auto i : n->Childs) {
			Analyze_Variable_Address_Pointing(v, i);
			if (v->Requires_Address)
				return;
		}
	else if (n->is(CALL_NODE)) {
		vector<int> v_index;
		for (int i = 0; i < n->Parameters.size(); i++)
			for (auto j : n->Parameters[i]->Get_all({ OBJECT_NODE, PARAMETER_NODE, OBJECT_DEFINTION_NODE }))
				if (j->Name == v->Name)
					v_index.push_back(i);
		for (auto i : v_index) {
			int Template_ptr = Get_Amount("ptr", n->Function_Implementation->Parameters[i]);
			int V_ptr = Get_Amount("ptr", v);
			if (Template_ptr > V_ptr)
				v->Requires_Address = true;
		}
	}
	else if (n->Name == "return" && n->Right != nullptr) {
		Analyze_Variable_Address_Pointing(v, n->Right);
		if (v->Requires_Address)
			return;

		//check if the return returs this v node
		for (auto i : n->Get_all({ OBJECT_DEFINTION_NODE, OBJECT_NODE, PARAMETER_NODE })) {
			if (i->Name == v->Name)
				if (i->Context == n) {
					Node* func = n->Get_Scope_As(FUNCTION_NODE, n);
					int Func_ptr = Get_Amount("ptr", func);
					int V_ptr = Get_Amount("ptr", i);
					if (Func_ptr > V_ptr)
						v->Requires_Address = true;
				}
		}

	}


	if (v->is(PARAMETER_NODE) && sys->Info.Debug)
		v->Requires_Address = true;
}

int Analyzer::Get_Amount(string t, Node* n)
{
	int result = 0;
	for (string s : n->Inheritted)
		if (s == t)
			result++;

	if (n->Cast_Type != nullptr && n->Cast_Type->Name != "address")
		for (auto i : n->Find(n->Cast_Type, n)->Inheritted)
			if (i == t)
				result++;

	return result;
}

void Analyzer::Define_Sizes(Node* p)
{
	//here we set the defined size of the variable
	for (Node* d : p->Defined) {
		//d->Get_Inheritted_Class_Members();
		d->Update_Size();
		d->Update_Format();
	}

	p->Update_Local_Variable_Mem_Offsets();
	p->Update_Member_Variable_Offsets(p);

}