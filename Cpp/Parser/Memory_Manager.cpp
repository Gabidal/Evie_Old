#include "../../H/Parser/Memory_Manager.h"
#include "../../H/BackEnd/Selector.h"
#include "../../H/Docker/Mangler.h"

extern Selector* selector;


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

	if (MANGLER::Is_Base_Type(Scope))
		return;
	
	//This memory padding is not applied to plain data structures
	if (!Scope->is("plain")) {
		//Try to compress memory usage, if the user agrees to it.
		Manage_Class_Re_Order();

		const int BITS = selector->Get_Largest_Register_Size(); //<- this can be the maximun register size
		int Remainder = Scope->Size % BITS;

		Scope->Parsed_By |= PARSED_BY::CLASS_MEMORY_PADDER;
		if (Remainder == 0)
			return;

		Report(Observation(INFO, "Added " + to_string(Remainder) + " bytes to the end of '" + Scope->Name + "'.", *Scope->Location));

		//If the base class has already a padder, then modify it.
		Node* Padder = Scope->Find("__CLASS_MEMORY_PADDER__", Scope, OBJECT_DEFINTION_NODE, false);
		if (Padder) {
			Padder->Name = to_string(stoi(Padder->Name) + Remainder);
		}
		else {
			Padder = new Node(OBJECT_DEFINTION_NODE, Scope->Location);
			Padder->Name = "__CLASS_MEMORY_PADDER__";
			//NOTE: const as inheritance may not negate re-sizing!
			Padder->Inheritted.push_back("const");
			Padder->Size = Remainder;
			Padder->Scope = Scope;

			Scope->Defined.push_back(Padder);
		}
	}
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
	if (!Scope->Has({ (string)"evie", "vivid" }))
		return;

	Re_Order_Vector(Scope->Defined);

	Scope->Parsed_By |= PARSED_BY::CLASS_RE_ORDERER;
}


// puts big at start and smoll at end :)
void Memory_Manager::Re_Order_Vector(vector<Node*>& List)
{
	std::sort(List.begin(), List.end(), [](Node* a, Node* b) { return a->Size > b->Size; });
}
