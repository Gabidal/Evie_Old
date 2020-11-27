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

Variable_Descriptor::Variable_Descriptor(string name, Node* v, int i, vector<Node*> source) {
	Define_Index = i;
	Var = v;
	for (int j = i+1; j < source.size(); j++) {
		if (source[j]->is(ASSIGN_OPERATOR_NODE))
			if (source[j]->Left->Name == name) {
				Expiring_Index = j;
				break;
			}
		if (source[j]->is(CALL_NODE)) {
			for (int p = 0; p < source[j]->Parameters.size(); p++) {
				if (source[j]->Parameters[p]->Name == name)
					if (source[j]->Template_Function != nullptr) {
						if (source[j]->Template_Function->Parameters[p]->is("ptr") != -1) {
							Expiring_Index = j;
							goto Skip;
						}
					}
					else
						cout << "Warning: " << source[i]->Name << " has no template function!" << endl;
			}
		}
		Expiring_Index = j;
	}
Skip:;
}