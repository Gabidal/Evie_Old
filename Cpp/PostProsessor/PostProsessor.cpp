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
	Type_Node* type = (Type_Node*)Input[i];

	//update the member stack offsets
	type->Update_Member_Stack_Offset();

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
