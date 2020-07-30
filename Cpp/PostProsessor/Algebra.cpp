#include "../../H/PostProsessor/Algebra.h"

void Algebra::Factory() {
	for (int i = 0; i < Input->size(); i++) {
		Set_Coefficient_Value(i);
		Set_Defining_Value(i);
		Inline_Variables(i);
	}
	for (auto i : *Input)
		Operate_Numbers_As_Constants(i);
	for (auto i : *Input)
		Operate_Coefficient_Constants(i);
}

vector<Node*> Algebra::Linearise(Node* ast, bool Include_Operator = false)
{
	vector<Node*> Result;
	if (ast->is(OPERATOR_NODE)) {
		vector<Node*> left = Linearise(ast->Left, Include_Operator);
		Result.insert(Result.end(), left.begin(), left.end());

		if (Include_Operator)
			Result.push_back(ast);

		vector<Node*> right = Linearise(ast->Right, Include_Operator);
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

	if (!Input->at(i)->is(OPERATOR_NODE))
		return;

	vector<Node*> Linear_Ast;

	if (Input->at(i)->Name != "=")
		Linear_Ast = Linearise(Input->at(i));
	else
		Linear_Ast = Linearise(Input->at(i)->Right);

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
	if (!Input->at(i)->is(OPERATOR_NODE))
		return;
	if (Input->at(i)->Name != "=")
		return;

	//give the defining node the current set-val.
	Parent->Find(Input->at(i)->Left->Name, Parent)->Current_Value = Input->at(i)->Right;

	//not shure delete this if thing broke up!!!
	//Input->erase(Input->begin() + i);
	//Set_Defining_Value(i);

	return;
}

void Algebra::Set_Coefficient_Value(int i)
{
	//a = x * 2
	//b = x * 2 + a
	if (!Input->at(i)->is(OPERATOR_NODE))
		return;

	vector<Node*> linear_ast = Linearise(Input->at(i), true);

	Node* Coefficient = nullptr;
	Node* Variable = nullptr;
	Node* Operator = nullptr;

	//now try to pair these
	for (int j = 0; j < linear_ast.size(); j++) {
		if (linear_ast[j]->is(NUMBER_NODE))
			Coefficient = linear_ast[j];
		else if (linear_ast[j]->is(OBJECT_NODE))
			Variable = linear_ast[j];
		else if (linear_ast[j]->Name == "*")
			Operator = linear_ast[j];
		else {
			//if it is not either one of those the conditions are not met and then just zero all.
			Coefficient = nullptr;
			Variable = nullptr;
			Operator = nullptr;
		}
		if ((Coefficient != nullptr) && (Variable != nullptr) && (Operator != nullptr))
			break;
	}

	//the required nodes where not found thus return. 
	if ((Coefficient == nullptr) || (Variable == nullptr) || (Operator == nullptr))
		return;

	//now apply the coefficient to the variable
	Variable->Coefficient = atoi(Coefficient->Name.c_str());

	*Operator = *Variable;
}

void Algebra::Operate_Coefficient_Constants(Node* op)
{
	//b = x2 + x2
	if (!op->is(OPERATOR_NODE))
		return;
	if (op->Left->is(OPERATOR_NODE))
		Operate_Coefficient_Constants(op->Left);
	if (op->Right->is(OPERATOR_NODE))
		Operate_Coefficient_Constants(op->Right);

	if (op->Left->Coefficient == 0)
		return;
	if (op->Right->Coefficient == 0)
		return;
	if (op->Left->Name != op->Right->Name)
		return;


	Node* New_Num = new Node(*op->Left);

	long left = op->Left->Coefficient;
	long right = op->Right->Coefficient;

	if (op->Name == "+")
		New_Num->Coefficient = left + right;
	else if (op->Name == "-")
		New_Num->Coefficient = left - right;
	else if (op->Name == "*")
		New_Num->Coefficient = left * right;
	else if (op->Name == "/")
		New_Num->Coefficient = left / right;
	else if (op->Name == "<<")
		New_Num->Coefficient = left << right;
	else if (op->Name == ">>")
		New_Num->Coefficient = left >> right;
	else if (op->Name == "&")
		New_Num->Coefficient = left & right;
	else if (op->Name == "|")
		New_Num->Coefficient = left | right;
	else if (op->Name == "¤")
		New_Num->Coefficient = left ^ right;
	else if (op->Name == "%")
		New_Num->Coefficient = left % right;
	else if (op->Name == "^")
		New_Num->Coefficient = pow(left, right);

	*op = *New_Num;

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
