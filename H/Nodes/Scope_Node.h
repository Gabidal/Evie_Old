#ifndef _SCOPE_NODE_H_
#define _SCOPE_NODE_H_

#include <vector>

#include "Node.h"
#include "Content_Node.h"
#include "../Flags.h"

using namespace std;

class Scope_Node : public Node
{
public:
	using Node::Node;
	
	//for AST
	Content_Node Childs;
	//all the defined Nodes in this scope
	vector<Object_Definition_Node*> Defined;

	int Get_Size() {
		int Result = 0;
		for (auto i : Defined)
			//dont worry about pointters: 
			//ptr scaler is in different place than size is.
			Result += i->Size;
	}

	void Update_Member_Stack_Offset() {
		int Offset = 0;
		for (auto i : Defined) {
			i->Location = Offset;
			Offset += i->Size;
		}
		return;
	}
private:

};

#endif