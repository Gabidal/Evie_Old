#ifndef _RETURN_NODE_H_
#define _RETURN_NODE_H_

#include "Node.h"
#include "../Flags.h"

class Return_Node : public Node
{
public:
	Return_Node() { Type == FLOW_NODE; Name = "return"; }
	~Return_Node() {}
	Node* Return_Val = nullptr;	//if this is null this doesnt return enything
private:

};

#endif