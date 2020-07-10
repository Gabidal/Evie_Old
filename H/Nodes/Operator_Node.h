#ifndef _OPERATOR_NODE_H_
#define _OPERATOR_NODE_H_

#include "Node.h"

class Operator_Node : public Node
{
public:
	Operator_Node(){}
	~Operator_Node(){}

	//for the AST
	Node* Right_Side_Nodes;
	Node* Left_Side_Nodes;
private:

};

#endif