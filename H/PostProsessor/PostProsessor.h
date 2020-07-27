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
	void Combine_Conditions(int i);					//combines the if and else
	void Open_Function_For_Prosessing(int i);		//just opens the functions insides for post prosessor.
	void Function_Callation(int i);
	
	Node* Copy_Node(Node* What_Node);
	void Operator_Overload(int i);					//makes new instance of using different operators
	void Template_Parameter(int i);					//dynamic parameters
	void Templates(int i);
	void Algebra();
private:
};

#endif