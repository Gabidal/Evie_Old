#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

#include "../Nodes/Node.h"

#include <vector>

using namespace std;

class Algebra {
public:
	vector<Node*>* Input = nullptr;
	Algebra(Node* parent) : Parent(parent) {}
	Algebra(Node* parent, vector<Node*>* in) : Input(in), Parent(parent) { Factory(); }

	void Factory();
private:
	Node* Parent;

	void Set_Return_To_Jump(Node* n, Node* Return_Value, Node* end);
	void Function_Inliner(Node* c, int i);
	vector<Node*> Get_all(Node* n, int Flag);
	void Prosess_Return(Node* n, int i);
	void Prosess_Call_Parameters(Node* n);
	void Prosess_Paranthesis(Node* n);

	void Set_Defining_Value(int i);
	void Set_Coefficient_Value(int i);
	void Reset_Defining_Value(int i);

	void Inline_Variables(int i);
	void Reduce_Operator_Operations(Node* n);

	void Clean_Inlined(int i);
	void Clean_Unused();

	void Operate_Coefficient_Constants(Node* op);
	void Operate_Distant_Coefficients(Node* op);
	void Operate_Numbers_As_Constants(Node* op);

	void Fix_Coefficient_Into_Real_Operator(Node* n);
	void Fix_Order_Into_Real_Operator(Node* n);
	Node* Operate_Constants(Node* l, Node* r);
	void Combine_Scattered(Node* op);
	Node* Get_Other_Pair(Node* ast, Node* other);

	void Un_Wrap_Parenthesis(Node* p);
};

#endif