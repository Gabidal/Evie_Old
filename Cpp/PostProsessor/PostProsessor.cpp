#include "../../H/PostProsessor/PostProsessor.h"

void PostProsessor::Factory() {
	Transform_Component_Into_Node();
	for (int i = 0; i < Input.size(); i++)
		Type_Definer(i);
	for (int i = 0; i < Input.size(); i++) {
		Operator_Overload(i);
		Member_Function(i);
		Open_Function_For_Prosessing(i);
		Combine_Conditions(i);
	}
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
	if (Input[i]->is(".") == false)
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

void PostProsessor::Combine_Conditions(int i)
{
	if ((Input[i]->is(IF_NODE)) && (Input[i]->is(WHILE_NODE)))
		return;
	if ((size_t)i + 1 > Input.size() - 1)
		return;
	if (!Input[(size_t)i + 1]->is(ELSE_IF_NODE) && !Input[(size_t)i + 1]->is(ELSE_NODE))
		return;
	//<summary>
	//here we will combine the successor & Predecessor.
	//</sumarry>
	Input[i]->Succsessor = Input[(size_t)i + 1];
	Input.erase(Input.begin() + (size_t)i + 1);
	//update the sucessors Predecessor.
	Input[i]->Succsessor->Predecessor = Input[i];

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
	p.Factory();

	return;
}

void PostProsessor::Operator_Overload(int i)
{
	//todo: make the override syntax
}

void PostProsessor::Template_Parameter(int i)
{
}

void PostProsessor::Algebra()
{
}

void PostProsessor::Templates(int i)
{
}
