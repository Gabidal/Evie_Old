#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

#include "../Nodes/Node.h"

#include <vector>

using namespace std;


vector<Node*> Linearise(Node* ast, bool Include_Operator);

class Algebra {
public:
	vector<Node*>* Input = nullptr;
	Algebra(Node* parent) : Parent(parent) {}
	Algebra(Node* parent, vector<Node*>* in) : Input(in), Parent(parent) { Factory(); }

	void Factory();
private:
	Node* Parent;

	void Function_Inliner(Node* c);
	vector<Node*> Get_all(Node* n, int Flag);

	void Set_Defining_Value(int i);
	void Set_Coefficient_Value(int i);

	void Inline_Variables(int i);
	void Reduce_Operator_Operations(Node* n);

	void Clean(int i);

	void Operate_Coefficient_Constants(Node* op);
	void Operate_Numbers_As_Constants(Node* op);

	void Fix_Coefficient_Into_Real_Operator(Node* n);
};

#endif