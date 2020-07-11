#ifndef _TYPE_NODE_H_
#deifne _TYPE_NODE_H_

#include "Scope_Node.h"
#include "../Flags.h"

class Type_Node : public Scope_Node
{
public:
	Type_Node() { Type = CLASS_NODE; }
	vector<string> Inheritted;
	~Type_Node(){}
private:

};

#endif