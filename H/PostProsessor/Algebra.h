#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

#include "../Nodes/Node.h"

#include <vector>

using namespace std;

class Algebra {
public:
	Algebra(Node* parent) : Parent(parent) {}
	vector<Node*>* Input = nullptr;

	void Factory();
private:
	Node* Parent;
	vector<Node*> Linearise(Node* ast, bool Include_Operator);

	void Function_Inliner(Node* c);

	void Set_Defining_Value(int i);
	void Set_Coefficient_Value(int i);

	void Inline_Variables(int i);
	void Reduce_Condition_Operations(Node* n);

	void Clean(int i);

	void Operate_Coefficient_Constants(Node* op);
	void Operate_Numbers_As_Constants(Node* op);

	void Fix_Coefficient_Into_Real_Operator(Node* n);
};

#endif