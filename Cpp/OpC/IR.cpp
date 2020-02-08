#include "..\..\H\OpC\IR.h"

Register* IR::Get_Register()
{
	for (Register* r : *Used_Registers)
	{
		if (r->Base->Name == T->Parameters.at(0)->Name)
		{
			Left = r->Name;
		}
		if (r->Base->Name == T->Childs.at(0)->Name)
		{
			Right = r->Name;
		}
	}
}

void IR::Factory()
{
	Get_Register();
	if (Left == "")
	{

	}
	if (Right == "")
	{

	}
}
