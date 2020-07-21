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

void PostProsessor::Return(int i)
{
	if (Input[i].Value != "return")
		return;
	bool No_Return_Value = ((size_t)i + 1 > Input.size() - 1);

	//return a + b
	//return;
	Return_Node* ret = new Return_Node;
	if (!No_Return_Value)
		ret->Return_Val = Input[(size_t)i + 1].node;
	Input[i].node = ret;
	return;
}

void PostProsessor::Size(int i)
{
	//size 4
	if (Input[i].Value != "size")
		return;
	Object_Definition_Node* size = new Object_Definition_Node;

	size->Size = atoi(((Number_Node*)Input[(size_t)i + 1].node)->Value.c_str());

	size->Name = "_SIZE_";
	size->Inheritted.push_back("type");

	Input[i].node = size;
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
