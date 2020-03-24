#include "../../H/OpC/IR.h"

void IR::add(int Flag)
{
	this->Flags |= Flag;
}

int IR::get()
{
	return Flags;
}
