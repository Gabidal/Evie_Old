#ifndef _FUNCTION_NODE_H_
#define _FUNCTION_NODE_H_

#include "Scope_Node.h"
#include "../Flags.h"
#include "Object_Definition_Node.h"

class Function_Node : public Scope_Node
{
public:
	Function_Node() { Type = FUNCTION_NODE; }
	Object_Definition_Node* Constructor = nullptr;
	Content_Node Parameters;
private:

};

#endif