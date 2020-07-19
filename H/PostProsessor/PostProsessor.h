#ifndef _POSTPROSESSOR_H_
#define _POSTPROSESSOR_H_

#include "../Lexer/Component.h"
#include "../Nodes/NODES.h"

#include <vector>
#include <iostream>

using namespace std;

class PostProsessor
{
public:
	vector<Component> Input;
	vector<Node*> Output;

	PostProsessor(){}
	~PostProsessor(){}

	void Factory();
	void Transform_Component_Into_Node(int i);
	void Return(int i);
	void Size(int i);
	void Override(int i);
	void Template_Parameter(int i);
	void Templates(int i);
	void Algebra();
private:

};

#endif