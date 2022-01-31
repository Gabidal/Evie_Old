#include "../../H/Parser/Memory_Manager.h"


void Memory_Manager::Factory()
{
	Manage_Function();
	Manage_Class_Padding();
}


/// <summary>
/// 
/// </summary>
void Memory_Manager::Manage_Function()
{
	if (!Scope->is(FUNCTION_NODE))
		return;


}

/// <summary>
/// Memory alignments managing.
/// Tells how many bytes are recyclable because of memory padding.
/// </summary>
void Memory_Manager::Manage_Class_Padding()
{
	if (!Scope->is(CLASS_NODE))
		return;
	if (Scope->is(PARSED_BY::CLASS_MEMORY_PADDER))
		return;
	
	//This memory padding is not applied to plain data structures
	if (Scope->is("plain"))
		return;

	

	Scope->Parsed_By |= PARSED_BY::CLASS_MEMORY_PADDER;
}

/// <summary>
/// Gathers members of a class and re-orders them in size order.
/// </summary>
void Memory_Manager::Manage_Class_Re_Order()
{
	if (!Scope->is(CLASS_NODE))
		return;
	if (Scope->is(PARSED_BY::CLASS_RE_ORDERER))
		return;

	//This system is only for Evie own structures.
	if (!Scope->is("evie"))
		return;

	Re_Order_Vector(Scope->Defined);

	Scope->Parsed_By |= PARSED_BY::CLASS_RE_ORDERER;
}


// puts big at start and smoll at end :)
void Memory_Manager::Re_Order_Vector(vector<Node*>& List)
{
	std::sort(List.begin(), List.end(), [](Node* a, Node* b) { return a->Size > b->Size; });
}
