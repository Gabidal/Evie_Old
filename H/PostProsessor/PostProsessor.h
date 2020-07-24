#ifndef _POSTPROSESSOR_H_
#define _POSTPROSESSOR_H_

#include "../Lexer/Component.h"
#include "../Flags.h"
#include "../Nodes/Node.h"

#include <vector>
#include <iostream>

using namespace std;

class PostProsessor
{
public:
	vector<Component> Components;
	vector<Node*> Input;
	vector<Node*> Output;
	Node* Parent = nullptr;

	PostProsessor(Node* p) : Parent(p){}
	PostProsessor(){}
	~PostProsessor(){}

	void Factory();
	void Transform_Component_Into_Node();			//transfer the components into pure nodes
	void Type_Definer(int i);						//defines all the members of type
	void Member_Function(int i);					//puts the func into parenting type class
	
	void Operator_Overload(int i);
	void Template_Parameter(int i);
	void Templates(int i);
	void Algebra();
private:
};

#endif