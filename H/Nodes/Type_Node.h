#ifndef _TYPE_NODE_H_
#define _TYPE_NODE_H_

#include "Scope_Node.h"
#include "../Flags.h"
#include <map>
#include "Function_Node.h"

class Type_Node : public Scope_Node
{
public:
	Type_Node() { Type = CLASS_NODE; }
	vector<string> Inheritted;
	map<string, Function_Node*> Operation_Overrides;
	vector<Function_Node*> Member_Functions;
	~Type_Node(){}
private:

};

#endif