#include "IRPostProsessor.h"

void IRPostProsessor::Scale_To_Same_Size(int i)
{
	if (!Input->at(i)->is(TOKEN::OPERATOR))
		return;

	//there IR's are still universal so dont worry about, if there is more than 2 arguments with the operator.

}

void IRPostProsessor::Factory()
{
}
