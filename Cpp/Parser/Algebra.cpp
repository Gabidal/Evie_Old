#include "../../H/Parser/Algebra.h"
#include "../../H/UI/Safe.h"

bool Optimized = false;

void Algebra::Factory() {
	for (int i = 0; i < Input->size(); i++) {
		Set_Coefficient_Value(i);
		Set_Defining_Value(i);
		Inline_Variables(i);
		Function_Inliner(Input->at(i));
		Prosess_Return(Input->at(i));
		Prosess_Paranthesis(Input->at(i));
	}
	for (int i = 0; i < Input->size(); i++)
		Clean_Inlined(i);
	for (auto i : *Input)
		Operate_Numbers_As_Constants(i);
	for (auto i : *Input)
		Operate_Coefficient_Constants(i);
	for (auto i : *Input)
		Reduce_Operator_Operations(i);
	for (auto i : *Input)
		Fix_Coefficient_Into_Real_Operator(i);
	Clean_Unused();
}

vector<Node*> Linearise(Node* ast, bool Include_Operator = false)
{
	vector<Node*> Result;
	if (ast->is(OPERATOR_NODE) || ast->is(CONDITION_OPERATOR_NODE) || ast->is(BIT_OPERATOR_NODE) || ast->is(ASSIGN_OPERATOR_NODE) || ast->is(ARRAY_NODE)) {
		vector<Node*> left = Linearise(ast->Left, Include_Operator);
		Result.insert(Result.end(), left.begin(), left.end());

		if (Include_Operator)
			Result.push_back(ast);

		vector<Node*> right = Linearise(ast->Right, Include_Operator);
		Result.insert(Result.end(), right.begin(), right.end());
	}
	else if (ast->is(CONTENT_NODE)) {
		vector<Node*> childs;
		for (auto c : ast->Childs) {
			vector<Node*> tmp = Linearise(c, Include_Operator);
			childs.insert(childs.end(), tmp.begin(), tmp.end());
		}
		Result.insert(Result.end(), childs.begin(), childs.end());
	}
	else if (ast->Name == "return") {
		Result.push_back(ast->Right);
	}
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
		Report(Observation(ERROR, c->Name +" doesn't have constructor function.", *c->Location));
		throw::exception("ERROR");
	}
	//make a result variable that the return always return the value to.
	vector<Node*> Inlined_Code;
	Node* Result_Definition = new Node(OBJECT_DEFINTION_NODE, c->Location);
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
		Node* set = new Node(OPERATOR_NODE, Func->Parameters[j]->Location);
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

	Node* End_Of_Func = new Node(LABEL_NODE, c->Location);
	End_Of_Func->Name = Result_Definition->Name + "_LABEL";
	c->Parent->Defined.push_back(End_Of_Func);

	//replace all return witha jump and a save the result if it returns enything.
	for (Node* r : Get_all(Func, FLOW_NODE)) {
		if (r->Name != "return")
			continue;
		Node* Content = new Node(CONTENT_NODE, r->Location);
		Content->Paranthesis_Type = '(';

		if (r->Right != nullptr) {
			Node* Result_N = Result_Definition->Copy_Node(Result_Definition, Result_Definition->Parent);
			Result_N->Type = OBJECT_NODE;

			Node* Set = new Node(OPERATOR_NODE, r->Location);
			Set->Name = "=";
			Set->Left = Result_N;
			Set->Right = r->Right;

			Content->Childs.push_back(Set);
		}

		Node* Label = new Node(LABEL_NODE, r->Location);
		Label->Name = End_Of_Func->Name;

		Node* jmp = new Node(FLOW_NODE, r->Location);
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

	Optimized = true;

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

void Algebra::Prosess_Return(Node* n)
{
	if (n->Name != "return")
		return;
	if (n->Right == nullptr)
		return;
	vector<Node*> tmp = { n->Right };
	Algebra a(n, &tmp);
	n->Right = tmp.back();
}

void Algebra::Prosess_Paranthesis(Node* n)
{
	if (!n->is(CONTENT_NODE))
		return;
	Algebra a(n, &n->Childs);
}

void Algebra::Inline_Variables(int i)
{
	//<summary>
	//finds a math equatin and tryes to inline the used variables set Values.
	//</summary>

	vector<Node*> Linear_Ast;
	if (Input->at(i)->is(OPERATOR_NODE) || Input->at(i)->is(ASSIGN_OPERATOR_NODE) || Input->at(i)->is(BIT_OPERATOR_NODE)) {
		if (Input->at(i)->Name != "=")
			Linear_Ast = Linearise(Input->at(i));
		else
			Linear_Ast = Linearise(Input->at(i)->Right);
	}
	else if (Input->at(i)->Name == "return") {
		if (Input->at(i)->Right != nullptr)
			Linear_Ast = Linearise(Input->at(i)->Right);
	}
	else {
		return;
	}


	for (Node* n : Linear_Ast) {
		if (n->is(CALL_NODE))
			continue;
		Node* d = Parent->Find(n->Name, Parent, OBJECT_DEFINTION_NODE);
		//if this is nullptr is means it is defined outside this scope.
		if (d != nullptr)
			if (d->Current_Value != nullptr) {
				//set right current coefficient value
				//n = -1
				//a = -n
				//Node* represents the -1 and n on this example
				//Node* n is same as the -n variable on example
				if (d->Current_Value->Expiring_Index >= i) {
					d->Current_Value->Var->Coefficient *= n->Coefficient;
					*n = *d->Current_Value->Var;
					d->Inlined = true;
					//maybe this is useless:
					n->Inlined = false;
					Optimized = true;
				}
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

	vector<Node*> Variables = Linearise(n);
	// a + 1 == a * 2
	//now go through one side and try to delete one coefficient amount of that variable on both sides.
	for (Node* v : Variables) {
		if (v->is(OBJECT_NODE) || v->is(OBJECT_DEFINTION_NODE)) {
			bool Removed_Coefficient = false;
			for (Node* other_v : Variables) {
				if (other_v == v)
					//skip same, at end we zero out this!
					continue;
				if (other_v->Name == v->Name) {
					other_v->Coefficient -= v->Coefficient;
					Removed_Coefficient = true;
					Optimized = true;
				}
			}
			//zero this variable out here:
			if (Removed_Coefficient)
				v->Coefficient -= v->Coefficient;
		}
	}

}

void Algebra::Clean_Inlined(int i)
{
	if (!Input->at(i)->is(OPERATOR_NODE) && !Input->at(i)->is(ASSIGN_OPERATOR_NODE))
		return;
	if (Input->at(i)->Name != "=")
		return;
	if (Parent->Find(Input->at(i)->Get_Most_Left()->Name, Input->at(i)->Get_Most_Left()->Get_Right_Parent())->Inlined == false)
		return;

	//!!! MUST COMBINE THE CALLATION AND THE CLASS FETCHER!!!
	vector<Node*> Calls = Input->at(i)->Has(CALL_NODE);
	Optimized = true;

	Input->erase(Input->begin() + i);

	if (Calls.size() > 0) {
		//put the function callations into the deleted operations location else.
		Input->insert(Input->begin() + i, Calls.begin(), Calls.end());
	}

	if (i < Input->size())
		Clean_Inlined(i);
		
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
	for (auto i : Linearise(Input->at(i)->Right))
		if (i->is(CALL_NODE))
			return;
	//remeber if functoin call has do something global/pointter-
	//dont let this function run on that!

	//if the right side is a operator wrap it in a parenthesis just because the '-' prefix!!
	Node* right = Input->at(i)->Right;

	if (Input->at(i)->Right->is(OPERATOR_NODE) || Input->at(i)->Right->is(CONDITION_OPERATOR_NODE) || Input->at(i)->Right->is(BIT_OPERATOR_NODE)) {
		//a = 1+2
		//b = a * 3 --> b = (1+2) *3;		maintain the math order
		right = new Node(CONTENT_NODE, right->Location);
		right->Paranthesis_Type = '(';
		right->Childs.push_back(Input->at(i)->Right);
		right->Parent = Input->at(i);
	}
	//give the defining node the current set-val.
	//this wont work with array offsets, because this doesnt save the current offsetter value to check later on.
	Variable_Descriptor* description = new Variable_Descriptor(right, i, *Input);
	Parent->Find(Input->at(i)->Left->Name, Input->at(i)->Left->Get_Right_Parent())->Current_Value = description;

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
		else if (linear_ast[j]->is(OBJECT_NODE) || linear_ast[j]->is(PARAMETER_NODE) || linear_ast[j]->is(OBJECT_DEFINTION_NODE))
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

	Optimized = true;

	*Operator = *Variable;
}

void Algebra::Clean_Unused()
{
	for (int d = 0; d < Parent->Defined.size(); d++) {
		if (Parent->Defined[d]->is("ptr") != -1)
			if (Parent->Defined[d]->is(PARAMETER_NODE))
				continue;
		if (Parent->Defined[d]->is("const") != -1)
			continue;
		//update the calling count.
		Parent->Defined[d]->Calling_Count = 0;
		for (int i = 0; i < Input->size(); i++) {
			if (!Input->at(i)->is(OPERATOR_NODE) && !Input->at(i)->is(ASSIGN_OPERATOR_NODE) && !Input->at(i)->is(CONDITION_OPERATOR_NODE) && !Input->at(i)->is(BIT_OPERATOR_NODE)) {
				if (Input->at(i)->Name == "return") {
					if (Input->at(i)->Right == nullptr)	//void return
						continue;
					vector<Node*> tmp = Linearise({ Input->at(i)->Right });
					for (int j = 0; j < tmp.size(); j++)
						if (Parent->Defined[d]->Name == tmp[j]->Name) {
							if ((size_t)j + 1 < tmp.size()) {
								if (!tmp[(size_t)j + 1]->is(ASSIGN_OPERATOR_NODE))
									Parent->Defined[d]->Calling_Count++;
							}
							else
								Parent->Defined[d]->Calling_Count++;
						}
				}
				else if (Input->at(i)->Childs.size() > 0) {
					for (auto c : Input->at(i)->Childs) {
						vector<Node*> tmp = Linearise(c);
						for (int j = 0; j < tmp.size(); j++)
							if (Parent->Defined[d]->Name == tmp[j]->Name) {
								if ((size_t)j + 1 < tmp.size()) {
									if (!tmp[(size_t)j + 1]->is(ASSIGN_OPERATOR_NODE))
										Parent->Defined[d]->Calling_Count++;
								}
								else
									Parent->Defined[d]->Calling_Count++;
							}
					}
				}
				else
					continue;
			}
			vector<Node*> linear = Linearise(Input->at(i), true);
			for (int l = 0; l < linear.size(); l++) {
				if (Parent->Defined[d]->Name == linear[l]->Name) {
					if ((size_t)l + 1 < linear.size()) {
						if (!linear[(size_t)l + 1]->is(ASSIGN_OPERATOR_NODE))
							Parent->Defined[d]->Calling_Count++;
					}
					else
						Parent->Defined[d]->Calling_Count++;
				}
			}
		}
	}
	for (int d = 0; d < Parent->Defined.size(); d++) {
		if (Parent->Defined[d]->is("ptr") != -1)
			if (Parent->Defined[d]->is(PARAMETER_NODE))
				continue;
		if (Parent->Defined[d]->is("const") != -1)
			continue;
		for (int i = 0; i < Input->size(); i++) {
			if (!Input->at(i)->is(OPERATOR_NODE) && !Input->at(i)->is(ASSIGN_OPERATOR_NODE) && !Input->at(i)->is(CONDITION_OPERATOR_NODE) && !Input->at(i)->is(BIT_OPERATOR_NODE))
				continue;
			vector<Node*> linear = Linearise(Input->at(i), false);
			for (int l = 0; l < linear.size(); l++) {
				if (Parent->Defined[d]->Name == linear[l]->Name) {
					if (Parent->Defined[d]->Calling_Count < 1) {
						Input->erase(Input->begin() + i--);
						Parent->Defined.erase(Parent->Defined.begin() + d);
						Optimized = true;
						break;
					}
				}
			}
		}
	}
}

void Algebra::Operate_Coefficient_Constants(Node* op)
{
	//b = 2x * -2x
	if (!op->is(OPERATOR_NODE) && !op->is(ASSIGN_OPERATOR_NODE))
		return;
	if (op->Left->is(OPERATOR_NODE) || op->Left->is(ASSIGN_OPERATOR_NODE))
		Operate_Coefficient_Constants(op->Left);
	if (op->Right->is(OPERATOR_NODE))
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
		Node* num = new Node(NUMBER_NODE, op->Location);
		num->Name = "0";
		*op = *num;
	}

	Optimized = true;

}

void Algebra::Operate_Numbers_As_Constants(Node* op)
{
	if (!op->is(OPERATOR_NODE) && !op->is(ASSIGN_OPERATOR_NODE) && !op->is(BIT_OPERATOR_NODE) && !op->is(CONDITION_OPERATOR_NODE))
			return;
	if (op->Left->is(OPERATOR_NODE) || op->Left->is(BIT_OPERATOR_NODE) || op->Left->is(CONDITION_OPERATOR_NODE))
		Operate_Numbers_As_Constants(op->Left);
	else if (op->Left->is(CONTENT_NODE)) {
		for (Node* i : op->Left->Childs)
			Operate_Numbers_As_Constants(i);
		if (op->Left->Childs.size() == 1) {
			op->Left->Childs[0]->Coefficient *= op->Left->Coefficient;
			*op->Left = *op->Left->Childs[0];
		}
	}
	if (op->Right->is(OPERATOR_NODE) || op->Right->is(BIT_OPERATOR_NODE) || op->Right->is(CONDITION_OPERATOR_NODE))
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

	Node* New_Num = new Node(NUMBER_NODE, op->Location);

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
	Optimized = true;
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
	Node* New_Operator = new Node(OPERATOR_NODE, n->Location);
	New_Operator->Name = "*";

	//making the coefficient into a real number token
	Node* Coefficient = new Node(NUMBER_NODE, n->Location);
	Coefficient->Name = to_string(n->Coefficient);

	//now clean the coefficient
	n->Coefficient = 1;

	//combine
	//this is because the override later
	New_Operator->Left = new Node(OBJECT_NODE, n->Location);

	*New_Operator->Left = *n;
	New_Operator->Right = Coefficient;

	*n = *New_Operator;
	Optimized = true;

	return;
}
