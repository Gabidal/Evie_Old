#ifndef _OPERATOR_NODE_H_
#define _OPERATOR_NODE_H_

#include "Node.h"
#include "../Flags.h"

class Operator_Node : public Node
{
public:
	Operator_Node() { Type = OPERATOR_NODE; }

	//for the AST
	Node* Right_Side_Nodes;
	Node* Left_Side_Nodes;
private:

};

#endif