#include "../../H/PostProsessor/Algebra.h"

void Algebra::Factory() {
	for (int i = 0; i < Input.size(); i++) {
		Set_Defining_Value(i);
		Inline_Variables(i);
	}
	for (auto i : Input)
		Operate_Numbers_As_Constants(i);
}

vector<Node*> Algebra::Linearise(Node* ast)
{
	vector<Node*> Result;
	if (ast->is(OPERATOR_NODE)) {
		vector<Node*> left = Linearise(ast->Left);
		Result.insert(Result.end(), left.begin(), left.end());

		vector<Node*> right = Linearise(ast->Right);
		Result.insert(Result.end(), right.begin(), right.end());
	}
	else if (ast->is(CONTENT_NODE))
		Result.insert(Result.end(), ast->Childs.begin(), ast->Childs.end());
	else
		Result.push_back(ast);

	return Result;
}

void Algebra::Inline_Variables(int i)
{
	//<summary>
	//finds a math equatin and tryes to inline the used variables set Values.
	//</summary>

	if (!Input[i]->is(OPERATOR_NODE))
		return;

	vector<Node*> Linear_Ast;

	if (Input[i]->Name != "=")
		Linear_Ast = Linearise(Input[i]);
	else
		Linear_Ast = Linearise(Input[i]->Right);

	for (Node* n : Linear_Ast) {
		Node* d = Parent->Find(n->Name, Parent);
		//if this is nullptr is means it is defined outside this scope.
		if (d != nullptr)
			if (d->Current_Value != nullptr)
				*n = *d->Current_Value;
	}

}

void Algebra::Set_Defining_Value(int i)
{
	//x = 12 + a
	//y = x * 2
	//x = 12
	//z = x * 4
	if (!Input[i]->is(OPERATOR_NODE))
		return;
	if (Input[i]->Name != "=")
		return;

	//give the defining node the current set-val.
	Parent->Find(Input[i]->Left->Name, Parent)->Current_Value = Input[i]->Right;

	return;
}

void Algebra::Set_Coefficient_Value(int i)
{

}

void Algebra::Operate_Coefficient_Constants(Node* op)
{
}

void Algebra::Operate_Numbers_As_Constants(Node* op)
{
	if (!op->is(OPERATOR_NODE))
		return;
	if (op->Left->is(OPERATOR_NODE))
		Operate_Numbers_As_Constants(op->Left);
	if (op->Right->is(OPERATOR_NODE))
		Operate_Numbers_As_Constants(op->Right);

	if (!op->Left->is(NUMBER_NODE))
		return;
	if (!op->Right->is(NUMBER_NODE))
		return;

	Node* New_Num = new Node(NUMBER_NODE);

	long left = atoi(op->Left->Name.c_str());
	long right = atoi(op->Right->Name.c_str());

	if (op->Name == "+")
		New_Num->Name = to_string(left + right);
	else if (op->Name == "-")
		New_Num->Name = to_string(left - right);
	else if (op->Name == "*")
		New_Num->Name = to_string(left * right);
	else if (op->Name == "/")
		New_Num->Name = to_string(left / right);
	else if (op->Name == "<<")
		New_Num->Name = to_string(left << right);
	else if (op->Name == ">>")
		New_Num->Name = to_string(left >> right);
	else if (op->Name == "&")
		New_Num->Name = to_string(left & right);
	else if (op->Name == "|")
		New_Num->Name = to_string(left | right);
	else if (op->Name == "¤")
		New_Num->Name = to_string(left ^ right);
	else if (op->Name == "%")
		New_Num->Name = to_string(left % right);
	else if (op->Name == "^")
		New_Num->Name = to_string(pow(left, right));

	*op = *New_Num;
}
