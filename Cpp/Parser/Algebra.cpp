#include "../../H/Parser/Algebra.h"
#include "../../H/UI/Safe.h"
#include "../../H/UI/Usr.h"
#include "../../H/Parser/PostProsessor.h"

#include <cmath>

bool Optimized = false;
long long Inlined_Function_Count = 0;
long long Unique_ID_Count = 0;
vector<string> Defined_Labels;

extern Usr* sys;

void Algebra::Factory() {
	if (sys->Info.Is_Service && sys->Service_Info != Document_Request_Type::ASM)
		return;

	for (int i = 0; i < Input->size(); i++) {
		Function_Inliner(Input->at(i), i);
	}
}

void Algebra::Set_Return_To_Jump(Node* n, Node* Return_Value, Node* end)
{
	if (n->Name == "return") {
		Node* Return_Paranthesis = new Node(CONTENT_NODE, n->Location);
		Return_Paranthesis->Paranthesis_Type = '{';
		Return_Paranthesis->Name = "Paranthesis";
		Return_Paranthesis->Scope = n->Scope;
		Return_Paranthesis->Context = n->Context;

		if (Return_Value) {
			Node* Assign = new Node(ASSIGN_OPERATOR_NODE, n->Location);
			Assign->Name = "=";
			Assign->Scope = n->Scope;

			Node* Left = Return_Value->Copy_Node(Return_Value, n->Scope);
			Left->Type = OBJECT_NODE;
			Left->Context = Assign;

			Node* Right = n->Copy_Node(n->Right, n->Scope);
			Right->Context = Assign;

			Assign->Left = Left;
			Assign->Right = Right;

			Return_Paranthesis->Childs.push_back(Assign);
		}
		Node* Return = new Node(FLOW_NODE, n->Location);
		Return->Name = "jump";
		Return->Right = new Node(*end);
		Return->Scope = end->Scope;
		Return->Right->Context = Return;

		Return_Paranthesis->Childs.push_back(Return);

		*n = *Return_Paranthesis;
	}
}

vector<Node*> Trace_Function_Inlined;
void Algebra::Function_Inliner(Node* c, int i)
{
	if (!c->is(CALL_NODE) || c->Function_Ptr || c->is("import") || c->Function_Implementation->is("import"))
		return;

	//copy the nodes to a safe heaven
	vector<Node*> Parameters;
	vector<Node*> Defined;
	vector<Node*> Childs;

	//check if this function is somehow related to its self.
	for (auto& T : Trace_Function_Inlined)
		if (T == c->Function_Implementation)
			return;

	Trace_Function_Inlined.push_back(c->Function_Implementation);

	if (!c->Function_Implementation->is(PARSED_BY::FUNCTION_PROSESSOR)) {
		PostProsessor p(c->Function_Implementation);
		p.Open_Function_For_Prosessing(c->Function_Implementation);
	}
	
	for (auto j : c->Function_Implementation->Childs){
		for (auto k : j->Get_all(CALL_NODE)) {
			if (k->Function_Ptr)
				continue;
			//k->Function_Implementation->Calling_Count++;	//increase the calling count
			if (k->Function_Implementation == c->Function_Implementation) {
				Trace_Function_Inlined.pop_back();
				return;	//disable recursive funktions
			}
		}
	}

	for (auto j : c->Function_Implementation->Childs) {
		Childs.push_back(c->Copy_Node(j, c->Scope));
	}

	for (auto j : Childs) {
		for (auto k : j->Get_all(LABEL_NODE)) {
			if (k->Inline_Return_Label == LABEL_TYPE::RETURN_LABEL && k->Context == nullptr)
				k->Inline_Return_Label = LABEL_TYPE::CAN_MODIFY_ID;
		}
	}

	//give the parameters a new name;
	for (auto j : c->Function_Implementation->Parameters) {
		Node* tmp = c->Copy_Node(j, c->Scope);
		tmp->Type = OBJECT_DEFINTION_NODE;
		tmp->Name += "_" + to_string(Inlined_Function_Count);
		Parameters.push_back(tmp);
	}

	while (true) {
		for (auto j : Defined_Labels) {
			if (j == ("Return_Here_" + to_string(Unique_ID_Count)))
				goto Label_Already_Taken;
		}
		break;
	Label_Already_Taken:;
		Unique_ID_Count++;
	}

	//generate the end_of_function_label
	Node* End_of_Function_Label = new Node(LABEL_NODE, c->Location);
	End_of_Function_Label->Name = "Return_Here_" + to_string(Unique_ID_Count);
	End_of_Function_Label->Scope = c->Scope;
	End_of_Function_Label->Inline_Return_Label = LABEL_TYPE::RETURN_LABEL;

	Childs.push_back(End_of_Function_Label);
	Defined_Labels.push_back("Return_Here_" + to_string(Unique_ID_Count));

	Node* Return_Value = nullptr;
	if (c->Context) {
		Return_Value = new Node(OBJECT_DEFINTION_NODE, c->Location);
		Return_Value->Name = "Return_Value" + to_string(Inlined_Function_Count);
		Return_Value->Scope = c->Scope;
		Return_Value->Context = c->Context;
		Return_Value->Inheritted = c->Inheritted;

		Return_Value->Get_Inheritted_Class_Members();
	}

	//go thr�ugh all the children and update the names
	//the defined also have the parameters so only here we need to go through all th childrens.
	for (auto i : c->Function_Implementation->Defined) {
		Node* tmp = c->Copy_Node(i, c->Scope);
		tmp->Type = OBJECT_DEFINTION_NODE;
		tmp->Name += "_" + to_string(Inlined_Function_Count);
		Defined.push_back(tmp);
	}

	for (auto j : Childs) {
		for (auto k : j->Get_all({ FLOW_NODE })) {
			//replace all the return statement with a jump to a end label command
			Set_Return_To_Jump(k, Return_Value, End_of_Function_Label);
		}
		for (auto k : j->Get_all({ PARAMETER_NODE, OBJECT_DEFINTION_NODE, OBJECT_NODE, FLOW_NODE, LABEL_NODE })) {
			for (auto i : c->Function_Implementation->Defined) {
				if (k->Name == i->Name) {
					k->Name += "_" + to_string(Inlined_Function_Count);
					if (k->is(PARAMETER_NODE))
						k->Type = OBJECT_NODE;
				}
			}
			if (k->Inline_Return_Label == LABEL_TYPE::CAN_MODIFY_ID) {
				vector<Node*> Same_Named_Labels;
				for (auto i : Childs) {
					for (auto j : i->Get_all(LABEL_NODE))
						if (j->Name == k->Name)
							Same_Named_Labels.push_back(j);
				}

				while (true) {
					for (auto j : Defined_Labels) {
						if (j == ("Return_Here_" + to_string(Unique_ID_Count)))
							goto Label_Already_Taken_1;
					}
					break;
				Label_Already_Taken_1:;
					Unique_ID_Count++;
				}

				for (auto i : Same_Named_Labels) {
					i->Name = "Return_Here_" + to_string(Unique_ID_Count);
				}

				Defined_Labels.push_back("Return_Here_" + to_string(Unique_ID_Count));
			}
		}
	}

	//first anchor the parameters to setted with the value corresponding at the callers parameters.
	for (int i = 0; i < Parameters.size(); i++) {
		Node* Left_Side = Parameters[i]->Copy_Node(Parameters[i], Parameters[i]->Scope);
		
		Node* Right_Side = c->Copy_Node(c->Parameters[i], c->Scope);

		Node* Operator = new Node(ASSIGN_OPERATOR_NODE, c->Parameters[i]->Location);
		Operator->Name = "=";
		Operator->Left = Left_Side;
		Operator->Right = Right_Side;
		Operator->Scope = c->Scope;
		Operator->Inheritted = Operator->Left->Inheritted;

		Left_Side->Context = Operator;
		Right_Side->Context = Operator;

		Childs.insert(Childs.begin(), Operator);
	}

	Node* Scope = c->Scope;

	if (Return_Value)
		Scope->Defined.push_back(Return_Value);

	Scope->Defined.insert(Scope->Defined.end(), Defined.begin(), Defined.end());

	Scope->Defined.insert(Scope->Defined.end(), c->Defined.begin(), c->Defined.end());
	c->Defined.clear();

	//c->Function_Implementation->Calling_Count--;

	if (c->Context) {
		c->Context->Header.insert(c->Context->Header.end(), Childs.begin(), Childs.end());
	}
	else
		Input->insert(Input->begin() + i, Childs.begin(), Childs.end());

	if (Return_Value) {
		Return_Value->Cast_Type = c->Cast_Type;
		*c = *Return_Value;
	}
	else
		Input->erase(Input->begin() + Childs.size() + i);

	Inlined_Function_Count++;
	Optimized = true;

	for (auto& j : Scope->Defined) {
		j->Update_Size();
	}

	Trace_Function_Inlined.pop_back();
}

Node* Algebra::Get_Other_Pair(Node* ast, Node* other) {
	if (ast->Left == other)
		return ast->Right;
	else if (ast->Right == other)
		return ast->Left;

	else if (ast->Left && Get_Other_Pair(ast->Left, other))
		return Get_Other_Pair(ast->Left, other);
	else if (ast->Right && Get_Other_Pair(ast->Right, other))
		return Get_Other_Pair(ast->Right, other);

	else if (ast->is(CONTENT_NODE)) {
		if (ast->Childs[0]->Has({ OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE })) {
			if (Get_Other_Pair(ast->Childs[0], other))
				return Get_Other_Pair(ast->Childs[0], other);
		}
		else if (ast->Childs[0] == other){
			if (ast->Context->Left == ast)
				return ast->Context->Right;
			else if (ast->Context->Right == ast)
				return ast->Context->Left;
		}
	}
	return nullptr;
}

bool Algebra::Is_Untrustworthy(Node* v)
{
	if (!v->Scope->is(WHILE_NODE))
		return false;

	for (auto i : v->Scope->Parameters)
		for (auto j : i->Get_all(OBJECT_NODE)) {
			if (j->Context == nullptr)
				continue;
			else if (j->Context->Has({ POSTFIX_NODE, PREFIX_NODE }))
				return true;
		}
	return false;
}

void Algebra::Exponent_Factorisation(Node*& n)
{
	
}

//This function sets order of the left, the left side od the order can be null,
//but the potens handle can handle it.
void Algebra::Compress_Potens(Node*& Operator)
{
	if (Operator->Name != "^")
		return;

	Node* Order_Operator = new Node(OPERATOR_NODE, new Position());
	Order_Operator->Name = "^";
	Order_Operator->Left = Operator->Left->Order;
	Order_Operator->Left->Context = Order_Operator;

	Order_Operator->Right = Operator->Right;
	Order_Operator->Right->Context = Order_Operator;

	Operator = Operator->Left;
}

string Algebra::De_Compress_Operators(Node* Coefficient)
{
	//This function only can decompress multiplication compressed operators.
	//xyz^2b^2 -> x * y * z^2 * b^2
	if (Coefficient->Order) {
		string Result = "";

		//Clear the coefficient order for to prevent infinity looptiloops.
		Node* Order = Coefficient->Order;
		Coefficient->Order = nullptr;

		Result = " (" + De_Compress_Operators(Coefficient) + ") ^ (" + De_Compress_Operators(Order) + ") ";

		return Result;
	}
	else if (Coefficient->is(COEFFICIENT_NODE)) {
		string Result = "";

		if (Coefficient->Childs.size() % 2 > 0) {
			for (int i = 0; i < Coefficient->Childs.size() -1; i += 2) {
				Result += De_Compress_Operators(Coefficient->Childs[i]) + " * " + De_Compress_Operators(Coefficient->Childs[i + 1]) + " ";
			}
		}
		else if (Coefficient->Childs.size() % 2 != 0) {
			if (Coefficient->Childs.size() == 1) {
				Result = De_Compress_Operators(Coefficient->Childs[0]);
			}
			else {
				Result += " * " + De_Compress_Operators(Coefficient->Childs.back());
			}
		}
		return Result;
	}


}

void Algebra::Combine_Numbers(Node*& n){
	//First check if this Node n is  a operator, if som then call this same function for its left and right memebrs.
	if (n->Has({ OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE, LOGICAL_OPERATOR_NODE })) {
		Combine_Numbers(n->Left);
		Combine_Numbers(n->Right);
	}
	//Double check iof the Node n is a number so that we can start our number combination.
	if (n->is(NUMBER_NODE)){
		//now we can differiante decimals and integers.
		if (n->Format == "decimal"){
			double Left = stod(n->Left->Name);
			double Right = stod(n->Right->Name);

			double Result_Value = Left + Right;

			Node* Result = new Node(NUMBER_NODE, new Position());
			Result->Name = to_string(Result_Value);
			Result->Format = "decimal";
			Result->Scope = n->Scope;
			Result->Context = n->Context;

			n = Result;
		}
		else{
			int Left = stoi(n->Left->Name);
			int Right = stoi(n->Right->Name);

			int Result_Value = Left + Right;

			Node* Result = new Node(NUMBER_NODE, new Position());
			Result->Name = to_string(Result_Value);
			Result->Format = "integer";
			Result->Scope = n->Scope;
			Result->Context = n->Context;

			n = Result;
		}
	}
}

void Algebra::Combine_Non_Adjacent_Numbers(Node*& n){
	//First we need to combine the given ast Node n, to a linear Node list
	vector<Node*> Nodes = n->Get_all();

	//Few thing to point out here.
	//First of all, If there are two or more numbers they all must have a same context node somewhere in the AST.
	//Second a context is always a operator.
	for (int X = 0; X < Nodes.size(); X++){
		for (int Y = 0; Y < Nodes.size(); Y++){
			if (X != Y){
				//First we need to check if the two nodes are numbers.
				if (Nodes[X]->is(NUMBER_NODE) && !Nodes[X]->Bad_Number && Nodes[Y]->is(NUMBER_NODE) && !Nodes[Y]->Bad_Number){
					//Now we need to check if there is a connecting Context between the two nodes.
					//We also need to check if there is a +, - in the paths between the two nodes.
					Node* x = Nodes[X];
					Node* y = Nodes[Y];
					
					//First gather the both paths os the two nodes.
					vector<Node*> Path_X;
					vector<Node*> Path_Y;

					Get_Context_Paths(x, y, Path_X, Path_Y);

					//Now we need to check if there are any +, - operators in the paths.
					for (auto i : Path_X){
						if (i->Name == "+" || i->Name == "-"){
							x->Bad_Number = true;
						}
					}
					for (auto i : Path_Y){
						if (i->Name == "+" || i->Name == "-"){
							y->Bad_Number = true;
						}
					}

					//If either one of the nodes is bad, then we can't combine them.
					if (x->Bad_Number || y->Bad_Number){
						continue;
					}

					//This node represents the context in witch the two nodes contexts collide.
					Node* Context = Path_X.back(); // <-- both paths end with the same context node that connects two of em.

					//If the context is a * we multiply the two numbers.
					//If the context is a / we divide the two numbers.
					//If the context is a ^ we raise the first number to the power of the second number.
					
				}
			}
		}
	}
}

//This function takes two Number nodes, and goes through the context AST tree, to see were they have the same context node.
//after knowing this result, it will return the both paths to the context node.
void Algebra::Get_Context_Paths(Node* X, Node* Y, vector<Node*>& X_Path, vector<Node*>& Y_Path){
	for (auto X_Index : X->Get_Context_Path()){
		for (auto Y_Index : Y->Get_Context_Path()){
			if (X_Index == Y_Index){
				//We found the same context node.
				//Now we need to find the path to the context node.
				//We will use the Get_Path function to find the path.
				X_Path = *Get_Path(X, X_Index);
				Y_Path = *Get_Path(Y, Y_Index);

				return;
			}
		}
	}
}

vector<Node*>* Algebra::Get_Path(Node* n, Node* Goal){
	//This function will return the path to the given Context node.
	//This function will return a vector of Nodes that are the path to the Context node.
	//This function will return nullptr if the Context node is not found.
	vector<Node*>* Path = new vector<Node*>();

	//First we need to find the path to the Context node.
	//We will use the Get_Path function to find the path.
	Node* Current = n;
	while (Current != Goal) {
		Path->push_back(Current);
		Current = Current->Context;
	}
	Path->push_back(Current);

	return Path;
}

void Algebra::Multiply_Nodes(Node*& x, Node*& y){
	if (!Has_Same_Base(x, y))
		return;

	Node** Left = &x;
	Node** Right = &y;

	if (x->is(NUMBER_NODE) && !y->is(NUMBER_NODE)){
		Left = &y;
		Right = &x;
	}

	if ((*Left)->is(NUMBER_NODE) && (*Right)->is(NUMBER_NODE)){
		if ((*Left)->Format == "decimal" || (*Right)->Format == "decimal"){
			(*Left)->Name = to_string(stod((*Left)->Name) * stod((*Right)->Name));
			(*Left)->Format = "decimal";
		}
		else{
			(*Left)->Name = to_string(stoi((*Left)->Name) * stoi((*Right)->Name));
			(*Left)->Format = "integer";
		}
	}
	else{
		//if the Left side already has a coefficient we need it to compound with the Right side.
		//if the Left has a coefficient of null, then the CoEfficient Combinator will handdle it.
		Node* Coefficient_Operator = new Node(OPERATOR_NODE, new Position());
		Coefficient_Operator->Name = "*";

		Coefficient_Operator->Left = (*Left)->Coefficient;
		Coefficient_Operator->Context = Coefficient_Operator;

		Coefficient_Operator->Right = (*Right);
		Coefficient_Operator->Right = Coefficient_Operator;
	}

	//Also combine the order of the both sides.
	Node* Order_Combiner = new Node(OPERATOR_NODE, new Position());
	Order_Combiner->Name = "+";
	Order_Combiner->Left = (*Left)->Order;
	Order_Combiner->Left->Context = Order_Combiner;

	Order_Combiner->Right = (*Right)->Order;
	Order_Combiner->Right->Context = Order_Combiner;
	
	(*Left)->Order = Order_Combiner;

	//Now we need to cover for the bro, the Right side.
	//We do it by making the pair of the Right side can control the Context on itself.
	//the right side operator would look like: (Right * Right_Pair) -> (Right_Pair)
	
	//First we need to find the Right_Side_Pair.
	Node* Right_Side_Pair = (*Right)->Get_Pair();

	Replace_Node(*Right, Right_Side_Pair);
}

//Function replaces the context node of it's own (Current) with itself.
void Algebra::Replace_Node(Node* Current, Node* New){
	//Context can only be a operator node.
	if (Current->is(OPERATOR_NODE)){
		if (Current->Context->Has({OPERATOR_NODE, ASSIGN_OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE})){
			if (Current == Current->Context->Left){
				Current->Context->Left = New;
			}
			else{
				Current->Context->Right = New;
			}
		}
	}
}

//a^x * a^y = a^(x+y)
//b^x * a^x = (ba)^x
bool Algebra::Has_Same_Base(Node* x, Node* y){
	if (x->Name == y->Name) {
		return true;
	}
	else if (x->Order->Name == y->Order->Name) {
		return true;
	}
	else
		return false;
}