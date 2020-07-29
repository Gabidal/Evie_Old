#include "../../H/PostProsessor/Algebra.h"

void Algebra::Factory() {

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



}

void Algebra::Set_Defining_Value(int i)
{
	//x = 12 + a
	//y = x * 2
	//x = 12
	//z = x * 4
	if (!Input[i]->is(OPERATOR_NODE))
		return;

	//give the defining node the current set-val.
	Parent->Find(Input[i]->Left->Name, Parent)->Current_Value = Input[i]->Right;

	return;
}
