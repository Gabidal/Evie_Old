#ifndef _OPERATOR_NODE_H_
#define _OPERATOR_NODE_H_

#include "Node.h"
#include "../Flags.h"

class Operator_Node : public Node
{
public:
	Operator_Node() { Type = OPERATOR_NODE; }
	~Operator_Node(){}

	//for the AST
	Node* Right_Side_Nodes = nullptr;
	Node* Left_Side_Nodes = nullptr;
private:

};

#endif