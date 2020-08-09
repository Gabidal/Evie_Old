#ifndef _POSTPROSESSOR_H_
#define _POSTPROSESSOR_H_

#include "../Lexer/Component.h"
#include "../Flags.h"
#include "../Nodes/Node.h"
#include "Algebra.h"

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
	//void Combine_Conditions(int i);					//combines the if and else
	void Open_Function_For_Prosessing(int i);		//just opens the functions insides for post prosessor.
	void Open_Condition_For_Prosessing(int i);		//just opens the condition insides for post prosessor.
	void Function_Callation(Node* n);					//justifyes the fucntion to call
	void Algebra_Laucher(int i);					//utilisez algebra to optimize the code in the function.
	void Combine_Member_Fetching(Node* n);			//combines the fether into the fetching member
	void Define_Sizes(Node* p);						//defines sizes of every type that the parent has init.
	void Combine_Condition(int i);					//combines the ifs and elses
	void Open_Operator_For_Prosessing(int i);
	void Determine_Return_Type(Node* n, Node* closest_type);
	void Operator_Type_Definer(Node* n);

	Node* Get_Combined(Node* n);
		
	void Operator_Overload(int i);					//makes new instance of using different operators
	void Template_Parameter(int i);					//dynamic parameters
	void Templates(int i);
private:
};

#endif