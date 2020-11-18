#include "../../H/Parser/Algebra.h"

void Algebra::Factory() {
	for (int i = 0; i < Input->size(); i++) {
		Set_Coefficient_Value(i);
		Set_Defining_Value(i);
		Inline_Variables(i);
		Function_Inliner(Input->at(i));
	}
	for (int i = 0; i < Input->size(); i++)
		Clean(i);
	for (auto i : *Input)
		Operate_Numbers_As_Constants(i);
	for (auto i : *Input)
		Operate_Coefficient_Constants(i);
	for (auto i : *Input)
		Reduce_Operator_Operations(i);
	for (auto i : *Input)
		Fix_Coefficient_Into_Real_Operator(i);
}

vector<Node*> Algebra::Linearise(Node* ast, bool Include_Operator = false)
{
	vector<Node*> Result;
	if (ast->is(OPERATOR_NODE) || ast->is(CONDITION_OPERATOR_NODE) || ast->is(BIT_OPERATOR_NODE)) {
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

void Algebra::Function_Inliner(Node* c)
{
	return;//TURN OFF
	//if (banana(1, 2) + apple(1, 2, 3))
	if (!c->is(CALL_NODE))
		return;
	if (c->is("ptr") != -1)
		return;
	//skip recusive functions, simply because theyr ass.
	for (auto j : Get_all(c->Template_Function, CALL_NODE))
		if (j->Name == c->Name)
			return;
	//TODO: make an exeption to ignore recursive functions!!!
	//we want to inline the fucniton contentsand make the parameters into a local variables
	//check if thos callation hasnt yet finded the template function.
	if (c->Template_Function == nullptr) {
		cout << "Error: " << c->Name << " doesn't have constructor function." << endl;
		exit(-1);
	}
	//make a result variable that the return always return the value to.
	vector<Node*> Inlined_Code;
	Node* Result_Definition = new Node(OBJECT_DEFINTION_NODE);
	//make a custon name
	Result_Definition->Name = c->Name;
	for (auto j : c->Parameters)
		Result_Definition->Name += "_" + j->Name;
	Result_Definition->Inheritted = c->Template_Function->Inheritted;
	Result_Definition->Update_Members_Size();
	Result_Definition->Parent = c->Parent;
	//add to later refrenses.
	Result_Definition->Parent->Defined.push_back(Result_Definition);

	Node* Func = c->Copy_Node(c->Template_Function, c->Parent);
	//rename all the inside variables
	for (Node* n : Get_all(Func, OBJECT_NODE))
		n->Name = "." + n->Name;
	for (Node* n : Get_all(Func, PARAMETER_NODE))
		n->Name = "." + n->Name;

	vector<Node*> Set_Val_For_Params;
	for (int j = 0; j < Func->Parameters.size(); j++) {
		Node* set = new Node(OPERATOR_NODE);
		set->Name = "=";
		//set the left
		set->Left = Func->Copy_Node(Func->Parameters[j], c->Parent);
		set->Left->Type = OBJECT_NODE;
		//and then right
		set->Right = c->Copy_Node(c->Parameters[j], c->Parent);
		//then push it
		Set_Val_For_Params.push_back(set);
	}
	//set the head
	c->Append(Inlined_Code, Set_Val_For_Params);

	Node* End_Of_Func = new Node(LABEL_NODE);
	End_Of_Func->Name = Result_Definition->Name + "_LABEL";
	c->Parent->Defined.push_back(End_Of_Func);

	//replace all return witha jump and a save the result if it returns enything.
	for (Node* r : Get_all(Func, FLOW_NODE)) {
		if (r->Name != "return")
			continue;
		Node* Content = new Node(CONTENT_NODE);
		Content->Paranthesis_Type = '(';

		if (r->Right != nullptr) {
			Node* Result_N = Result_Definition->Copy_Node(Result_Definition, Result_Definition->Parent);
			Result_N->Type = OBJECT_NODE;

			Node* Set = new Node(OPERATOR_NODE);
			Set->Name = "=";
			Set->Left = Result_N;
			Set->Right = r->Right;

			Content->Childs.push_back(Set);
		}

		Node* Label = new Node(LABEL_NODE);
		Label->Name = End_Of_Func->Name;

		Node* jmp = new Node(FLOW_NODE);
		jmp->Name = "jump";
		jmp->Right = Label;

		Content->Childs.push_back(jmp);

		*r = *Content;
	}
	c->Append(Inlined_Code, Func->Childs);

	//now time to transfers
	c->Parent->Append(c->Parent->Defined, Func->Defined);

	//re make the callation into the result holding variable.
	*c = *Result_Definition->Copy_Node(Result_Definition, Result_Definition->Parent);
	c->Type = OBJECT_NODE;

	//the later on this will be unwrapped.
	c->Header = Inlined_Code;

	return;
}

vector<Node*> Algebra::Get_all(Node* n, int f)
{
	vector<Node*> Result;
	if (n->Left != nullptr) {
		vector<Node*> left = Get_all(n->Left, f);
		Result.insert(Result.end(), left.begin(), left.end());
	}
	if (n->Right != nullptr) {
		vector<Node*> right = Get_all(n->Right, f);
		Result.insert(Result.end(), right.begin(), right.end());
	}
	if (n->Succsessor != nullptr) {
		vector<Node*> Succsessors = Get_all(n->Succsessor, f);
		Result.insert(Result.end(), Succsessors.begin(), Succsessors.end());
	}
	if (n->Predecessor != nullptr) {
		vector<Node*> Predecessors = Get_all(n->Predecessor, f);
		Result.insert(Result.end(), Predecessors.begin(), Predecessors.end());
	}
	if (n->Fetcher != nullptr) {
		vector<Node*> Fetchers = Get_all(n->Fetcher, f);
		Result.insert(Result.end(), Fetchers.begin(), Fetchers.end());
	}
	for (Node* i : n->Header) {
		vector<Node*> Headers = Get_all(i, f);
		Result.insert(Result.end(), Headers.begin(), Headers.end());
	}
	for (Node* i : n->Childs) {
		vector<Node*> childs = Get_all(i, f);
		Result.insert(Result.end(), childs.begin(), childs.end());
	}
	for (Node* i : n->Parameters) {
		vector<Node*> childs = Get_all(i, f);
		Result.insert(Result.end(), childs.begin(), childs.end());
	}
	for (Node* i : n->Defined) {
		vector<Node*> childs = Get_all(i, f);
		Result.insert(Result.end(), childs.begin(), childs.end());
	}

	if (n->is(f))
		Result.push_back(n);

	return Result;
}

void Algebra::Inline_Variables(int i)
{
	//<summary>
	//finds a math equatin and tryes to inline the used variables set Values.
	//</summary>

	if (!Input->at(i)->is(OPERATOR_NODE) && !Input->at(i)->is(ASSIGN_OPERATOR_NODE))
		return;

	vector<Node*> Linear_Ast;

	if (Input->at(i)->Name != "=")
		Linear_Ast = Linearise(Input->at(i));
	else
		Linear_Ast = Linearise(Input->at(i)->Right);

	for (Node* n : Linear_Ast) {
		Node* d = Parent->Find(n, Parent);
		//if this is nullptr is means it is defined outside this scope.
		if (d != nullptr)
			if (d->Current_Value != nullptr) {
				//set right current coefficient value
				//n = -1
				//a = -n
				//Node* represents the -1 and n on this example
				//Node* n is same as the -n variable on example
				d->Current_Value->Coefficient *= n->Coefficient;
				*n = *d->Current_Value;
				d->Inlined = true;
				//maybe this is useless:
				n->Inlined = false;
			}
	}

}

void Algebra::Reduce_Operator_Operations(Node* n)
{
	if (!n->is(OPERATOR_NODE) && !n->is(CONDITION_OPERATOR_NODE) && !n->is(ASSIGN_OPERATOR_NODE))
		return;
	//a * 2 < 1 - a
	//2a -a < a - a + 1
	//a < 1
	vector<Node*> tmp_L = { n->Left };
	Algebra tmp_l(Parent, &tmp_L);

	vector<Node*> tmp_R = { n->Right };
	Algebra tmp_r(Parent, &tmp_R);



	vector<Node*> Variables = Linearise(n);
	// a + 1 == a * 2
	//now go through one side and try to delete one coefficient amount of that variable on both sides.
	for (Node* v : Variables) {
		if (v->is(OBJECT_NODE)) {
			bool Removed_Coefficesnt = false;
			for (Node* other_v : Variables) {
				if (other_v == v)
					//skip same, at end we zero out this!
					continue;
				if (other_v->Name == v->Name) {
					other_v->Coefficient -= v->Coefficient;
					Removed_Coefficesnt = true;
				}
			}
			//zero this variable out here:
			if (Removed_Coefficesnt)
				v->Coefficient -= v->Coefficient;
		}
	}

}

void Algebra::Clean(int i)
{
	if (!Input->at(i)->is(OPERATOR_NODE) && !Input->at(i)->is(ASSIGN_OPERATOR_NODE))
		return;
	if (Input->at(i)->Name != "=")
		return;
	if (Parent->Find(Input->at(i)->Get_Most_Left()->Name, Input->at(i)->Get_Most_Left()->Get_Right_Parent())->Inlined == false)
		return;

	//!!! MUST COMBINE THE CALLATION AND THE CLASS FETCHER!!!
	vector<Node*> Calls = Input->at(i)->Has(CALL_NODE);

	Input->erase(Input->begin() + i);

	if (Calls.size() > 0) {
		//put the function callations into the deleted operations location else.
		Input->insert(Input->begin() + i, Calls.begin(), Calls.end());
	}

	if (i < Input->size())
		Clean(i);
		
	return;
}

void Algebra::Set_Defining_Value(int i)
{
	//x = 12 + a
	//y = x * 2
	//x = 12
	//z = x * 4
	if (!Input->at(i)->is(ASSIGN_OPERATOR_NODE))
		return;
	//ignore arrays
	if (Input->at(i)->Left->is(ARRAY_NODE))
		return;
	//remeber if functoin call has do something global/pointter-
	//dont let this function run on that!

	//if the right side is a operator wrap it in a parenthesis just because the '-' prefix!!
	Node* right = Input->at(i)->Right;

	if (Input->at(i)->Right->is(OPERATOR_NODE)) {
		//a = 1+2
		//b = a * 3 --> b = (1+2) *3;		maintain the math order
		right = new Node(CONTENT_NODE);
		right->Paranthesis_Type = '(';
		right->Childs.push_back(Input->at(i)->Right);
	}
	//give the defining node the current set-val.
	//this wont work with array offsets, because this doesnt save the current offsetter value to check later on.
	Parent->Find(Input->at(i)->Left->Name, Input->at(i)->Left->Get_Right_Parent())->Current_Value = right;

	return;
}

void Algebra::Set_Coefficient_Value(int i)
{
	//a = x * 2
	//b = x * 2 + a
	if (!Input->at(i)->is(OPERATOR_NODE) && !Input->at(i)->is(CONDITION_OPERATOR_NODE) && !Input->at(i)->is(ASSIGN_OPERATOR_NODE))
		return;

	vector<Node*> linear_ast = Linearise(Input->at(i), true);

	Node* Coefficient = nullptr;
	Node* Variable = nullptr;
	Node* Operator = nullptr;

	//now try to pair these
	for (int j = 0; j < linear_ast.size(); j++) {
		if (linear_ast[j]->is(NUMBER_NODE))
			Coefficient = linear_ast[j];
		else if (linear_ast[j]->is(OBJECT_NODE) || linear_ast[j]->is(PARAMETER_NODE))
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
	//b = 2x * -2x
	if (!op->is(OPERATOR_NODE) && !op->is(ASSIGN_OPERATOR_NODE))
		return;
	if (op->Left->is(OPERATOR_NODE) || op->Left->is(ASSIGN_OPERATOR_NODE))
		Operate_Coefficient_Constants(op->Left);
	if (op->Right->is(OPERATOR_NODE) || op->Right->is(ASSIGN_OPERATOR_NODE))
		Operate_Coefficient_Constants(op->Right);

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

	if (op->Coefficient == 0) {
		Node* num = new Node(NUMBER_NODE);
		num->Name = "0";
		*op = *num;
	}

}

void Algebra::Operate_Numbers_As_Constants(Node* op)
{
	if (!op->is(OPERATOR_NODE) && !op->is(ASSIGN_OPERATOR_NODE))
		return;
	if (op->Left->is(OPERATOR_NODE))
		Operate_Numbers_As_Constants(op->Left);
	else if (op->Left->is(CONTENT_NODE)) {
		for (Node* i : op->Left->Childs)
			Operate_Numbers_As_Constants(i);
		if (op->Left->Childs.size() == 1) {
			op->Left->Childs[0]->Coefficient *= op->Left->Coefficient;
			*op->Left = *op->Left->Childs[0];
		}
	}
	if (op->Right->is(OPERATOR_NODE))
		Operate_Numbers_As_Constants(op->Right);
	else if (op->Right->is(CONTENT_NODE)) {
		for (Node* i : op->Right->Childs)
			Operate_Numbers_As_Constants(i);
		if (op->Left->Childs.size() == 1) {
			op->Left->Childs[0]->Coefficient *= op->Left->Coefficient;
			*op->Left = *op->Left->Childs[0];
		}
	}

	if (!op->Left->is(NUMBER_NODE))
		return;
	if (!op->Right->is(NUMBER_NODE))
		return;

	Node* New_Num = new Node(NUMBER_NODE);

	//set sizes
	if (op->Left->Size < op->Right->Size)
		New_Num->Size = op->Right->Size;
	else
		New_Num->Size = op->Left->Size;

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

void Algebra::Fix_Coefficient_Into_Real_Operator(Node* n)
{
	//here we will fix the coefficient into a real operator as the name yells.
	if (n->is(OPERATOR_NODE) || n->is(CONDITION_OPERATOR_NODE) || n->is(ASSIGN_OPERATOR_NODE)) {
		if (n->Left->Coefficient != 0)
			Fix_Coefficient_Into_Real_Operator(n->Left);
		else {
			//this is needed to be cleaned!!
			//and remember the ((a <-- this is no more) - 1) <-- so this is -1 after the clean!!
			*n = *n->Right;
			return;
		}
		if (n->Right->Coefficient != 0)
			Fix_Coefficient_Into_Real_Operator(n->Right);
		else {
			//this is needed to be cleaned!!
			//and remember the ((a <-- this is no more) - 1) <-- so this is -1 after the clean!!
			*n = *n->Left;
			return;
		}
	}
	//only variables are accepted
	if (!n->is(OBJECT_NODE) && !n->is(PARAMETER_NODE))
		return;
	if (n->Coefficient == 1)
		return;

	//make operator that is going to hold the new coefficient and the variable
	Node* New_Operator = new Node(OPERATOR_NODE);
	New_Operator->Name = "*";

	//making the coefficient into a real number token
	Node* Coefficient = new Node(NUMBER_NODE);
	Coefficient->Name = to_string(n->Coefficient);

	//now clean the coefficient
	n->Coefficient = 1;

	//combine
	//this is because the override later
	New_Operator->Left = new Node(OBJECT_NODE);

	*New_Operator->Left = *n;
	New_Operator->Right = Coefficient;

	*n = *New_Operator;

	return;
}
