#ifndef _CALL_NODE_H_
#define _CALL_NODE_H_

#include "Object_Node.h"
#include "Content_Node.h"
#include "../Flags.h"

class Call_Node : public Object_Node
{
public:
	Call_Node(Object_Node& obj) : Object_Node(obj){ Type = CALL_NODE; }
	Call_Node() { Type = CALL_NODE; }
	~Call_Node(){}
	Content_Node Paranthesis;
private:

};

#endif