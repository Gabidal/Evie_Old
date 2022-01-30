#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

#include "../Nodes/Node.h"

#include <vector>

using namespace std;

class Algebra {
public:
	vector<Node*>* Input = nullptr;
	Algebra(Node* parent) : Scope(parent) {}
	Algebra(Node* parent, vector<Node*>* in) : Input(in), Scope(parent) { Start_Factory(); }

	void Start_Factory();
private:
	Node* Scope;

	static void Factory(Node*& n);

	//Function inlining tools
	void Set_Return_To_Jump(Node* n, Node* Return_Value, Node* end);
	void Function_Inliner(Node* c, int i);
	Node* Get_Other_Pair(Node* ast, Node* other);
	bool Is_Untrustworthy(Node* v);

	//Number factorisation
	void Exponent_Factorisation(Node*& n);

	//Multiplication and potense handle functions
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
	static void Potens_And_Multiplication(Node*& Operator);
	static void Replace_Node(Node* Current, Node* New);
	static void Remove_As_Much(Node** n, string Name, int& count);
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

	//This function takes two nodes and multiplies them together.
	static void Multiply_Nodes(Node*& x, Node*& y);

	//Decompress the operators into AST
	static string De_Compress_Operators(Node* Coefficient);

	//This function is used to combine two ajacents numbers.
	static void Combine_Numbers(Node*& n);

	//This function combines numbers that are not adjacent to each other.
	//Nonetheless this function still needs to go by the mathematical rules.
	static void Combine_Non_Adjacent_Variables(Node*& n);

	//This function takes two Number nodes, and goes through the context AST tree, to see were they have the same context node.
	//after knowing this result, it will return the both paths to the context node.
	static void Get_Context_Paths(Node* n1, Node* n2, vector<Node*>& path1, vector<Node*>& path2);

	//This function will go through the AST tree, and find the first node that has the same context node.
	static vector<Node*>* Get_Path(Node* n, Node* Context);

	//Inlining functions
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
	static void Update_Inline_Content(Node* n);
	static void Run_Variable_Inliner(Node* n);
	static bool Has_Inlining_Value(Node* n);
	static void Inline_Variable(Node*& n);
	static Node** Interpreter_Value(Node* n);
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
};

#endif