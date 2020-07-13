#ifndef _CONDITION_NODE_H_
#define _CONDITION_NODE_H_

#include "Scope_Node.h"
#include "Operator_Node.h"
#include "Object_Definition_Node.h"
#include "../Flags.h"
#include <iostream>

using namespace std;

class Condition_Node : public Scope_Node
{
public:
	Condition_Node(int type) {
		Type = type;	
	}
	~Condition_Node(){}
	void Condition_Initializer(Node* first, Node* Second) {
		if (((Content_Node*)first)->Childs.size() == 1)
			Condition = *(Operator_Node*)((Content_Node*)first)->Childs[0];
		else {
			Index = *(Operator_Node*)((Content_Node*)first)->Childs[0];
			Condition = *(Operator_Node*)((Content_Node*)first)->Childs[1];
			Footer = *(Operator_Node*)((Content_Node*)first)->Childs[2];
		}
	}
	//{
	Operator_Node Index;
	Operator_Node Condition;
	//if footter has some other thatn null then that means the condition is a loop
	Operator_Node Footer;
	//}
	int ID = 0;
	//the code is in the scope
private:

};

#endif