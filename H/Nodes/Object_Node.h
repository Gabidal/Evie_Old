#ifndef _OBJECT_NODE_H_
#define _OBJECT_NODE_H_

#include "Content_Node.h"
#include "Node.h"
#include "../Flags.h"

class Object_Node : public Node
{
public:
	Object_Node() { Type = OBJECT_NODE; }
	//int ptr test a
	Content_Node Inheritted;
private:

};

#endif