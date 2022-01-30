#include "../../H/Parser/Memory_Manager.h"

void Memory_Manager::Factory()
{
	Manage_Function();
	Manage_Class();
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
void Memory_Manager::Manage_Class()
{
	if (!Scope->is(CLASS_NODE))
		return;


}
