#ifndef _CONTENT_NODE_H_
#define _CONTENT_NODE_H_

#include "Node.h"

class Content_Node : public Node
{
public:
	Content_Node(){}
	~Content_Node(){}
	//for AST
	vector<Node*> Childs;
private:

};

#endif