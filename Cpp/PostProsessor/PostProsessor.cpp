#include "../../H/PostProsessor/PostProsessor.h"

void PostProsessor::Factory() {
	Transform_Component_Into_Node();
}

void PostProsessor::Transform_Component_Into_Node()
{
	//<summary>
	//Extracts the Node ptr's from the component tokens
	//</summary>
	for (auto i : Input) {
		Node* n = i.node;
		Output.push_back(n);
	}
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
