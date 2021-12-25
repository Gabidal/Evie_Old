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
	return;
	//return;
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

	//go thróugh all the children and update the names
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

void Algebra::Exponent_Factorisation(Node* n)
{
	if (!n->is(COEFFICIENT_NODE))
		return;

	//Target number T 
	//Fraction F
	//Result X
	//F^X = T
	//First we need to know the context of this current number
	//So find next to number or variable toi comparte the operation to.

	//Now that the AST is already mushed to a clusterfuck we can analyze it to optimize it.
	//Try to put all the coefficient into same base.

	vector<Node*> Coefficients = n->Childs;

	bool Has_Been_Optimized = true;
	while (Has_Been_Optimized) {
		Has_Been_Optimized = false;

		for (auto& x : Coefficients) {
			for (auto& y : Coefficients) {
				if ((x == y) || (!x || !y))
					continue;

				Add_Same_Base_Orders(x, y, Has_Been_Optimized);
			}
		}
	}
}

void Algebra::Multiplication_Factorisation(Node* n)
{

}

//NOTE: This function shall only run if all the potenses are already compressed!!!
void Algebra::Compress_Multiplication(Node*& Operator)
{
	//This function compresses AST multiplications into a linear list of coefficients.
	//x * y * a * b * c -> xyabc
	if (Operator->Name != "*")
		return;

	vector<Node*> Components = Operator->Get_all({ OBJECT_NODE, PARAMETER_NODE, NUMBER_NODE }, [](Node* Op) { if (Op->Has({OPERATOR_NODE, CONDITION_OPERATOR_NODE, BIT_OPERATOR_NODE, LOGICAL_OPERATOR_NODE}) && Op->Name != "*") return true; });
	
	Node* Coefficient = new Node(COEFFICIENT_NODE, new Position());
	Coefficient->Childs = Components;
	Coefficient->Name = "__COEFFICIENT__";

	Operator = Coefficient;
}

void Algebra::Compress_Potens(Node*& Operator)
{
	if (Operator->Name != "^")
		return;

	Operator->Left->Order = Operator->Right;
	*Operator = *Operator->Left;
}

void Algebra::Add_Same_Base_Orders(Node*& x, Node*& y, bool& Has_Been_Optimized)
{
	if (!x->is(NUMBER_NODE) && !y->is(NUMBER_NODE)) {
		if (x->Name == y->Name) {
			//x^1 * x^3 -> x^(1+3)

			//First create a operator +
			Node* Plus = new Node(OPERATOR_NODE, new Position());
			Plus->Name = "+";
			Plus->Scope = x;
			Plus->Left = x->Order;
			Plus->Right = y->Order;

			//Then create a new container that will contain both of the exponents.
			//This is to maintain the Original operation order.
			Node* Container = new Node(CONTENT_NODE, new Position());
			Container->Childs = { Plus };

			x->Order = Container;
			//Release the y component
			y = nullptr;
		}
	}
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
