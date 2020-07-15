#ifndef _OBJECT_DEFINITION_NODE_H_
#define _OBJECT_DEFINITION_NODE_H_

#include "Node.h"
#include "../Flags.h"
#include <vector>

class Object_Definition_Node : public Node
{
public:
	Object_Definition_Node() { Type = OBJECT_DEFINTION_NODE; }
	Object_Definition_Node(vector<string> inherit, string name) {
		Inheritted = inherit;
		Name = name;
	}
	~Object_Definition_Node(){}
	vector<string> Inheritted;
private:

};

#endif