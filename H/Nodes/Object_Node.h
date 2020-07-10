#ifndef _OBJECT_NODE_H_
#define _OBJECT_NODE_H_

#include "Content_Node.h"
#include "Node.h"

class Object_Node : public Node
{
public:
	Object_Node(){}
	~Object_Node(){}
	//int ptr test a
	Content_Node Inheritted;
private:

};

#endif