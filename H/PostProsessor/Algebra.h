#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

#include "../Nodes/Node.h"

#include <vector>

using namespace std;

class Algebra {
public:
	Algebra(Node* parent) : Parent(parent) {}
	vector<Node*> Input;

	void Factory();
private:
	Node* Parent;
	vector<Node*> Linearise(Node* ast);

	void Set_Defining_Value(int i);
	void Set_Coefficient_Value(int i);

	void Inline_Variables(int i);

	void Operate_Coefficient_Constants(Node* op);
	void Operate_Numbers_As_Constants(Node* op);
};

#endif