#ifndef _NUMBER_NODE_H_
#define _NUMBER_NODE_H_

#include "Node.h"
#include "Operator_Node.h"
#include "../Flags.h"

class Number_Node : public Node
{
public:
	Number_Node() { Type = NUMBER_NODE; }
	~Number_Node(){}
	string Value = "";	//123
private:

};

#endif