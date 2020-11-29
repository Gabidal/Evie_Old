#include "../../H/Nodes/Node.h"
#include "../../H/Nodes/Token.h"
#include <vector>
#include <string>
#include "../../H/Parser/Algebra.h"

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

Variable_Descriptor::Variable_Descriptor(Node* v, int i, vector<Node*> source) {
	Define_Index = i;
	Var = v;

	vector<Node*> Linear_Ast = Linearise(v, false);
	//for complex inlinings
	for (int n = i; n < source.size(); n++) {
		if (source[n]->is(ASSIGN_OPERATOR_NODE)) {
			for (auto c : Linear_Ast) {
				if (source[n]->Left->Name == c->Name) {
					Expiring_Index = n;
					goto Stop;
				}
			}
		}
		if (source[n]->is(CALL_NODE)) {
			for (auto c : Linear_Ast) {
				for (auto p : source[n]->Template_Function->Parameters) {
					if (p->is("ptr") != -1)
						if (p->Name == c->Name) {
							Expiring_Index = n;
							goto Stop;
						}
				}
			}
		}
		Expiring_Index = n;
	}
Stop:;
}