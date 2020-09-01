#include "../../H/PostProsessor/PostProsessor.h"

extern Node* Global_Scope;

void PostProsessor::Factory() {
	Transform_Component_Into_Node();
	for (int i = 0; i < Input.size(); i++)
		Type_Definer(i);
	for (int i = 0; i < Input.size(); i++)
		Handle_Prototypes(i);
	//Define_Sizes(Parent);
	for (int i = 0; i < Input.size(); i++) {
		Operator_Overload(i);
		Member_Function(i);
		Open_Function_For_Prosessing(i);
		Open_Condition_For_Prosessing(i);
		//Combine_Conditions(i);
		Combine_Member_Fetching(Input[i]);
		Algebra_Laucher(i);
		Open_Operator_For_Prosessing(i);
		Function_Callation(Input[i]);
	}
	for (int i = 0; i < Input.size(); i++)
		Combine_Condition(i);
}

void PostProsessor::Transform_Component_Into_Node()
{
	//<summary>
	//Extracts the Node ptr's from the component tokens
	//</summary>
	for (auto i : Components) {
		if (i.node == nullptr)
			continue;
		Node* n = i.node;
		Input.push_back(n);
	}
	return;
}

void PostProsessor::Type_Definer(int i)
{
	//<summary>
	//stack type info
	//</summary>
	if (Input[i]->Type != CLASS_NODE)
		return;

	//point into the parents defined list not input list
	Node* type = Parent->Find(Input[i]->Name, Parent, true);

	//combine inheritted memebrs
	type->Get_Inheritted_Class_Members();

	//update members sizes
	type->Update_Members_Size();

	//update the member stack offsets
	type->Update_Members_Mem_Offset();

	return;
}

void PostProsessor::Member_Function(int i)
{
	//<summary>
	//check if the funciton node has inherittes '.'
	//and sets the function into types function list
	//and changes the parent pointter into the class type
	//</summary>
	if (Input[i]->Type != FUNCTION_NODE)
		return;
	if (Input[i]->is(".") == -1)
		return;

	Node* func = Input[i];
	
	//get the parent type that this member function belong to.
	Node* type = Parent->Find(
		func->Inheritted[
			(size_t)func->is(".") - 1
		], 
		func->Parent
	);

	//for member variables accessing
	func->Parent = type;

	type->Member_Functions.push_back(func);

	return;
}

void PostProsessor::Open_Function_For_Prosessing(int i)
{
	if (!Input[i]->is(FUNCTION_NODE))
		return;
	//here we just go trugh the insides of the function
	//for optimization and other cool stuff :D
	PostProsessor p(Input[i]);
	p.Input = Input[i]->Childs;

	//preprare the local variables
	p.Define_Sizes(Input[i]);

	p.Factory();

	return;
}

void PostProsessor::Open_Condition_For_Prosessing(int i)
{
	if (!Input[i]->is(IF_NODE) && !Input[i]->is(ELSE_IF_NODE))
		return;

	//here we pass the condition operator into algebra optimizer
	Algebra a(Input[i]);
	a.Input = &Input[i]->Parameters;
	a.Factory();

	//here we now postprosess also the insides of the condition
	PostProsessor p(Input[i]);
	p.Input = Input[i]->Childs;

	//preprare the local variables
	p.Define_Sizes(Input[i]);
	p.Factory();

	return;
}

void PostProsessor::Function_Callation(Node* n)
{
	if (!n->is(CALL_NODE))
		return;
	if (n->Template_Function != nullptr)
		return;
	//<summary>
	//this function tryes to find the function to call
	//</summary>
	//first try to find if this fucntion is a virtual function
	Node* defition = Parent->Find(n->Name, Parent);
	//other wise we have normal functions
	//now lets check for template arguments-
	//as parameters on the function this callation calls

	//first make a mangled name outof the caller
	n->Mangled_Name = n->Get_Mangled_Name();

	//also the returning type of this callation is not made,
	//we can determine it by the operations other side objects type.
	//if the 

	//first ignore the template parameters for now
	for (auto f : Global_Scope->Defined)
		if (f->is(FUNCTION_NODE) || f->is(PROTOTYPE))
			if (f->Get_Mangled_Name() == n->Mangled_Name) {
				n->Template_Function = f;
				//we dont need to do enything, everything is fine.
				return;
			}

	Node* OgFunc = nullptr;

	//TODO:
	//make that even the returning type affect the choosing of og-function.

	//if the code gets here it means the og-function has template paramters!
	for (auto f : Global_Scope->Defined) {
		if (!f->is(FUNCTION_NODE) && !f->is(PROTOTYPE))
			continue;
		if (n->is("ptr") == -1)
			if (f->Name != n->Name)
				continue;
		bool Direct_Type = false;
		if (f->is(PROTOTYPE))
			Direct_Type = true;
		if (f->Parameters.size() != n->Parameters.size())
			continue;
		for (int p = 0; p < f->Parameters.size(); p++) {
			if (Direct_Type && f->Parameters[p]->Name == "type")
				continue;
			else if (!Direct_Type && f->Parameters[p]->is("type") != -1)
				continue;	//just ignore the template parameters for now.
			//here we will determine if this function is the og-fucntion or not.
			else if (Direct_Type && (f->Parameters[p]->Name != n->Parameters[p]->Get_Inheritted("")))
				goto Next_Function;
			else if (!Direct_Type && f->Parameters[p]->Get_Inheritted("") != n->Parameters[p]->Get_Inheritted("")) {
				goto Next_Function;
			}
		}
		//here if we get this function is the og-function.
		OgFunc = f;
		break;
	Next_Function:;
	}

	if (n->is("ptr") != -1)
		return;

	if (OgFunc == nullptr) {
		cout << "Error: Can't find suitable funciton to call with parameters:\n";
		for (int j = 0; j < n->Parameters.size(); j++) {
			cout << "  " << n->Parameters[j]->Name << "\n";
		}
		cout << endl;
	}

	if (OgFunc->is(PROTOTYPE))
		for (auto j : OgFunc->Parameters)
			if (j->Name == "type")		//REMEBER THE DIRECT TYPING!!	
				cout << "Error: Can't copy a foreingh function " << OgFunc->Name << "." << endl;

	Node* func = nullptr;
	if (!OgFunc->is(PROTOTYPE)) {
		//now we want to copy that function again but this time we will put the called parameter types
		func = OgFunc->Copy_Node(OgFunc);

		//now we want to through the templates and put on them the right parameter infos
		for (int p = 0; p < func->Parameters.size(); p++) {
			vector<string> tmp = func->Parameters[p]->Inheritted;
			//update the parent
			func->Parameters[p]->Parent = func;

			func->Parameters[p]->Inheritted = n->Parameters[p]->Inheritted;
			//now iterate the leftover types like ptr
			for (string s : tmp) {
				if (s == "type")
					continue;
				if (func->Parameters[p]->is(s) == -1)
					func->Parameters[p]->Inheritted.push_back(s);
			}
			//alsoset the defined types into right inheritance.
			func->Find(func->Parameters[p]->Name, func)->Inheritted = func->Parameters[p]->Inheritted;
		}
	}
	else {
		func = OgFunc;
	}
	n->Template_Function = func;
	func->Mangled_Name = func->Get_Mangled_Name();
	
	//now we want to inject it to global scope to be reached next time.
	Global_Scope->Childs.push_back(func);
	Global_Scope->Defined.push_back(func);

	return;
}

void PostProsessor::Algebra_Laucher(int i)
{
	if (!Input[i]->is(FUNCTION_NODE))
		return;
	Algebra a(Input[i]);
	a.Input = &Input[i]->Childs;
	a.Factory();
}

void PostProsessor::Combine_Member_Fetching(Node* n)
{
	//(a.x).m
	//(a.x).m()
	//(a.x[0]).m()
	//a[b[c[0]]]
	//(a.x).m[1][2][3]
	if (n->is(OPERATOR_NODE)) {
		if (n->Name == ".") {
			//x.m()
			if (n->Right->is(CALL_NODE)) {
				//put the fetcher to the first parameters slot
				n->Right->Parameters.insert(n->Right->Parameters.begin(), Get_Combined(n->Left));
			}
			else if (n->Right->is(ARRAY_NODE)) {
				n->Right->Get_Most_Left()->Fetcher = Get_Combined(n->Left);
				Combine_Member_Fetching(n->Right->Right);
			}
			else
				n->Right->Fetcher = Get_Combined(n->Left);
			*n = *n->Right;
		}
		else {
			//a = b + x.m()
			Combine_Member_Fetching(n->Left);
			Combine_Member_Fetching(n->Right);
		}
	}
	if (n->is(CONTENT_NODE)) {
		for (auto i : n->Childs)
			Combine_Member_Fetching(i);
	}
}

void PostProsessor::Define_Sizes(Node* p)
{
	//here we set the defined size of the variable
	for (Node* d : p->Defined) {
		d->Update_Members_Size();
		d->Update_Members_Mem_Offset();
	}
}

void PostProsessor::Combine_Condition(int i)
{
	if (!Input[i]->is(IF_NODE))
		return;

	Node* current_condition = Input[i];
	int j;
	//loop through the next nodes if theyre else ifs
	for (j = i + 1; j < Input.size(); j++) {
		if (Input[j]->is(ELSE_IF_NODE) || Input[j]->is(ELSE_NODE)) {
			//give the else if the parent as the if
			Input[j]->Predecessor = current_condition;
			//give the if the child as successor else if
			current_condition->Succsessor = Input[j];
			//give the successor as the current pointter
			current_condition = Input[j];
		}
		else {
			break;
		}
	}

	//now remove the elses
	Input.erase(Input.begin() + i + 1, Input.begin() + j);
}

void PostProsessor::Open_Operator_For_Prosessing(int i)
{
	if (Input[i]->is(CALL_NODE))
		Determine_Return_Type(Input[i], nullptr);
	else if (Input[i]->is(OPERATOR_NODE)) {
		Determine_Return_Type(Input[i]->Left, Input[i]->Right);
		Determine_Return_Type(Input[i]->Right, Input[i]->Left);
	}
	else if (Input[i]->is(CONTENT_NODE))
		for (Node* n : Input[i]->Childs)
			Determine_Return_Type(n, nullptr);
}

void PostProsessor::Determine_Return_Type(Node* n, Node* closest_type)
{
	//int a = banana() + apple()	<-- this local type is 'int'
	//string a = to_string(banana() + apple() * 1) <--here the local type is what to_string takes as a parameter
	//an paranthesis can work as a own local space where there can be a local type
	if (n->is(CALL_NODE)) {
		//if the closest type is a nullptr it is a void function
		if (closest_type != nullptr) {
			n->Inheritted = closest_type->Inheritted;
		}
		else
			n->Inheritted.push_back("func");	//void
		Function_Callation(n);
	}
	if (!n->is(OPERATOR_NODE))
		return;
	if (n->Left->is(OPERATOR_NODE) || n->Left->is(CONTENT_NODE))
		Determine_Return_Type(n->Left, n->Right);
	if (n->Right->is(OPERATOR_NODE) || n->Right->is(CONTENT_NODE))
		Determine_Return_Type(n->Right, n->Left);

}

void PostProsessor::Operator_Type_Definer(Node* n)
{
	//go trhough the ast tree
	if (n->is(OPERATOR_NODE)) {
		Operator_Type_Definer(n->Left);
		Operator_Type_Definer(n->Right);
	}
	if (n->is(CONTENT_NODE))
		for (Node* i : n->Childs)
			Operator_Type_Definer(i);

	//now set the values
	if (n->is(OPERATOR_NODE)) {
		n->Inheritted = n->Left->Inheritted;
		if (n->Inheritted.size() == 0)
			//for callation instances
			n->Inheritted = n->Right->Inheritted;
	}
	if (n->is(CONTENT_NODE)) {
		n->Inheritted = n->Childs[0]->Inheritted;
	}
	return;
}

void PostProsessor::Handle_Prototypes(int i)
{
	if (!Input[i]->is(PROTOTYPE))
		return;
	//import func new (4, ABC)
	//all numbers need to be redefined by type size.
	//and all other text is already classes.
	//pointters are inside the parameter as inheritance.
	for (int j = 0; j < Input[i]->Parameters.size(); j++) {
		if (Input[i]->Parameters[j]->is(NUMBER_NODE)) {
			Input[i]->Parameters[j] = Global_Scope->Find(atoi(Input[i]->Parameters[j]->Name.c_str()), Global_Scope);
		}
	}
	//now all types are good to go.
	//although function calling might get tricky with just types as the parameters.
}

void PostProsessor::Find_Inlining_Space()
{

}

Node* PostProsessor::Get_Combined(Node* n)
{
	Node* Result;
	//((a.x).m()).b
	//((a.x[0]).m()).b
	if (n->is(OPERATOR_NODE)) {
		if (n->Name == ".") {
			Result = n->Right;
			if (n->Right->is(CALL_NODE)) {
				//put the fetcher to the first parameters slot
				Result->Parameters.insert(Result->Parameters.begin(), Get_Combined(n->Left));
			}
			else
				Result->Fetcher = Get_Combined(n->Left);
		}
	}
	else if (n->is(CONTENT_NODE)) {
		Result = n;
	}
	else {
		Result = n;
	}
	return Result;
}

void PostProsessor::Operator_Overload(int i)
{
	//todo: make the override syntax
}

void PostProsessor::Template_Parameter(int i)
{
}

void PostProsessor::Templates(int i)
{
}
