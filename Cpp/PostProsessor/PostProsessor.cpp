#include "../../H/PostProsessor/PostProsessor.h"

void PostProsessor::Factory() {
	Transform_Component_Into_Node();
	for (int i = 0; i < Input.size(); i++)
		Type_Definer(i);
	for (int i = 0; i < Input.size(); i++) {
		Operator_Overload(i);
		Member_Function(i);
	}
}

void PostProsessor::Transform_Component_Into_Node()
{
	//<summary>
	//Extracts the Node ptr's from the component tokens
	//</summary>
	for (auto i : Components) {
		Node* n = i.node;
		Output.push_back(n);
	}
	return;
}

void PostProsessor::Type_Definer(int i)
{
	//<summary>
	//stack type info
	//</summary>
	if (!Input[i]->Type == CLASS_NODE)
		return;

	//test!!!: Node* type = Input[i];
	//point into the parents defined list not input list
	Node* type = Parent->Find(Input[i]->Name, Input[i]->Parent);

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
	if (!Input[i]->Type == FUNCTION_NODE)
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
