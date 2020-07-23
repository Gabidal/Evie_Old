#include "../../H/PostProsessor/PostProsessor.h"

void PostProsessor::Factory() {
	Transform_Component_Into_Node();
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
	Type_Node* type = (Type_Node*)Input[i]->Parent->Find(Input[i]->Name, Input[i]->Parent);

	//update the member stack offsets
	type->Update_Member_Stack_Offset();

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
	if (((Function_Node*)Input[i])->Constructor->is(".") == -1)
		return;

	Function_Node* func = ((Function_Node*)Input[i]);
	
	Type_Node* type = (Type_Node*)func->Parent->Find(
		func->Constructor->Inheritted[
			func->Constructor->is(".") - 1
		], func->Parent
	);

	//for member variables accessing
	func->Parent = type;

	type->Member_Functions.push_back(func);

	return;
}

void PostProsessor::Override(int i)
{
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
