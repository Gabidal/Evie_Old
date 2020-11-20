#include "../../H/Nodes/Node.h"
#include "../../H/Nodes/Token.h"
#include <vector>
#include <string>

using namespace std;

void Node::Update_Defined_Stack_Offsets()
{
	int Parameter_Offset = 0;
	int Local_Offset = 0;

	for (auto i : Defined) {
		if (i->is(PARAMETER_NODE)) {
			if (!Token(i).is(TOKEN::REGISTER)) {
				i->Memory_Offset = Parameter_Offset;
				i->Update_Size_By_Inheritted();
				Parameter_Offset += i->Get_Size();
			}
		}
		else if (i->is(OBJECT_NODE) || i->is(OBJECT_DEFINTION_NODE)) {
			//every local variable is defined default as a value in a register.
		}
	}
}
