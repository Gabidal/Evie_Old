#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

#include "../Nodes/Node.h"

#include <vector>

using namespace std;

class Algebra {
public:
	vector<Node*>* Input = nullptr;
	Algebra(Node* parent) : Scope(parent) {}
	Algebra(Node* parent, vector<Node*>* in) : Input(in), Scope(parent) { Factory(); }

	void Factory();
private:
	Node* Scope;

	//Function inlining tools
	void Set_Return_To_Jump(Node* n, Node* Return_Value, Node* end);
	void Function_Inliner(Node* c, int i);
	Node* Get_Other_Pair(Node* ast, Node* other);
	bool Is_Untrustworthy(Node* v);

	//Number factorisation
	void Exponent_Factorisation(Node* n);
	void Multiplication_Factorisation(Node* n);

	//Compress multiplication into coefficient whole.
	void Compress_Multiplication(Node*& Operator);

	//Compress Potens operators into order factors.
	void Compress_Potens(Node*& Operator);

	//Number factorization tools
	void Add_Same_Base_Orders(Node*& x, Node*& y, bool& Has_Been_Optimized);

	//Decompress the operators into AST
	string De_Compress_Operators(Node* Coefficient);
};

#endif