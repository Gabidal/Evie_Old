#ifndef _POSTFIX_NODE_H_
#deifne _POSTFIX_NODE_H_

#include "Node.h"
#include "../Flags.h"

class PostFix_Node : public Node
{
public:
	PostFix_Node() { Type = POSTFIX_NODE; }
	~PostFix_Node() {}
	string Fix = "";
	Node* node = nullptr;
private:

};

#endif