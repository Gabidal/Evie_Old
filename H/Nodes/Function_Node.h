#ifndef _FUNCTION_NODE_H_
#define _FUNCTION_NODE_H_

#include "Scope_Node.h"
#include "../Flags.h"

class Function_Node : public Scope_Node
{
public:
	Function_Node() { Type = FUNCTION_NODE; }
	//import loyal ptr int
	vector<string> behavior;
private:

};

#endif