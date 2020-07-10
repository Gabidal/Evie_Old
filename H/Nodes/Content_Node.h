#ifndef _CONTENT_NODE_H_
#define _CONTENT_NODE_H_

#include "Node.h"
#include "../Flags.h"

class Content_Node : public Node
{
public:
	Content_Node() { Type = CONTENT_NODE; }
	//for AST
	vector<Node*> Childs;
private:

};

#endif