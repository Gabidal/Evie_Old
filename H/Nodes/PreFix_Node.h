#ifndef _PREFIX_NODE_H_
#define _PREFIX_NODE_H_

#include "Node.h"
#include "../Flags.h"

class PreFix_Node : public Node
{
public:
	PreFix_Node() { Type = PREFIX_NODE; }
	~PreFix_Node(){}
	string Fix = "";
	Node* node = nullptr;
private:

};
#endif