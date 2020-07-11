#ifndef _STRING_NODE_H_
#define _STRING_NODE_H_

#include "Node.h"
#include "../Flags.h"

class String_Node : public Node
{
public:
	String_Node() { Type = STRING_NODE; }
	~String_Node(){}
	string Value = "";
private:

};
#endif