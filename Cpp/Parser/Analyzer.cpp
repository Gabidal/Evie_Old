#include "../../H/Parser/Analyzer.h"
#include "../../H/Parser/Algebra.h"
#include "../../H/Parser/Memory_Manager.h"
#include "../../H/Parser/PostProsessor.h"
#include "../../H/UI/Safe.h"

extern Usr* sys;

extern bool Optimized;

void Analyzer::Factory()
{
	//gather information about the AST that we have made
	Detect_Abnormal_Start_Address();
	Safe::Go_Through_AST(Safe::Report_Missing_Cast);
	Safe::Flush_Errors();
	List_All_Exported();

	for (auto* f : Start_Of_Proccesses) {
		Calling_Count_Incrementer(f);
	}
}

void Analyzer::Detect_Abnormal_Start_Address()
{
	Node* Main = Global_Scope->Find(sys->Info.Start_Function_Name, Global_Scope, FUNCTION_NODE);

	vector<Node*> Initializers;
	vector<int> Indicies;
	for (int i = 0; i < Global_Scope->Childs.size(); i++) {
		if (!Global_Scope->Childs[i]->is(ASSIGN_OPERATOR_NODE))
			continue;

		Initializers.push_back(Global_Scope->Childs[i]);
		Indicies.push_back(i);
	}

	if (Main && sys->Info.Format == "exe") {
		Start_Of_Proccesses.push_back(Main);

		for (auto& i : Initializers) {
			i->Copy_Node(i, i, Main);
		}

		//Because the global variable initializers are not in any function particulary before this.
		//Thus: they are not PostProsessed.
		PostProsessor p(Main, Initializers);

		//Insert the global variable initializations to Main
		Main->Childs.insert(Main->Childs.begin(), Initializers.begin(), Initializers.end());

	}
	else {
		//create a new initialization function for the global variables.
		Node* Func = new Node(FUNCTION_NODE, new Position());
		Func->Name = "_INIT_";
		Func->Childs = Initializers;
		Func->Inheritted = { "func", "export" };

		for (auto& i : Func->Childs) {
			i->Copy_Node(i, i, Main);
		}

		Func->Scope = Global_Scope;

		Global_Scope->Defined.push_back(Func);

		//Because the global variable initializers are not in any function particulary before this.
		//Thus: they are not PostProsessed.
		PostProsessor p(Func, Func->Childs);

		Dependency_Injector(Func->Childs);

	}

	//now that the global variables are transferred to the right functions, 
	//we may proceed to delete those ghost fragments from the global scope.
	for (int i = 0; i < Indicies.size(); i++) {
		//we remove the index i from the current index, 
		//because for every list index removal the latter indicies are offsetted wrongly by the amount i.
		int Index = Indicies[i] - i;
		Global_Scope->Childs.erase(Global_Scope->Childs.begin() + Index);
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

void Analyzer::Dependency_Injector(vector<Node*>& nodes){

	std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
		
		bool Result = false;

		//Ceck if the a if a function
		//If a is a function, then check if a contains b
		//If a contains b, then  put b before a
		for (auto i : a->Get_all({ CALL_NODE })) {
			for (auto j : i->Function_Implementation->Childs){

				if (j->Has(b)) {
					Result = true;
					break;
				}

			}
		}

		for (auto i : b->Get_all({ CALL_NODE })) {
			for (auto j : i->Function_Implementation->Childs){

				bool Has_a = j->Has(a);

				if (Result && Has_a) {
					//If a contains b, but b also contains a, then dont do shit.
					Result = false;
					break;
				}

			}
		}


		return Result;

	});

}