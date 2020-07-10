#ifndef _SCOPE_NODE_H_
#define _SCOPE_NODE_H_

#include <vector>

#include "Node.h"
#include "Content_Node.h"

using namespace std;

class Scope_Node : public Node
{
public:
	Parent_Node(){}
	~Parent_Node(){}
	
	//for AST
	Content_Node Parameters;
	Content_Node Childs;
	//all the defined Nodes in this scope
	vector<Node*> Defined;
private:

};

#endif