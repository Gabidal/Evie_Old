#ifndef _FUNCTION_NODE_H_
#define _FUNCTION_NODE_H_

#include "Scope_Node.h"

class Function_Node : public Scope_Node
{
public:
	Function_Node(){}
	~Function_Node(){}
	//import loyal
	Node* Prefix = nullptr;
	//int ptr
	Node* Return_Type = nullptr;
private:

};

#endif