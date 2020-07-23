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
	int Size = 0;
	int Location = 0;

	int is(string type) {
		for (int i = 0; i < Inheritted.size(); i++)
			if (type == Inheritted[i])
				return i;
		return -1;
	}
private:

};

#endif