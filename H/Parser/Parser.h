#ifndef _PARSER_H_
#define _PARSER_H_

#include "../../H/Flags.h"
#include "../Lexer/Component.h"
#include "../Nodes/Node.h"

#include <vector>
#include <iostream>

using namespace std;

class Parser
{
public:
	Parser(Node* p) : Parent(p){}
	~Parser(){}
	Node* Parent = nullptr;
	vector<Component> Input;
	vector<Component> Get_Inheritting_Components(int i);
	vector<int> Get_Amount_Of(int i, long Flag);
	//PATTERNS
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	void Definition_Pattern(int i);								//test ptr a
	void Object_Pattern(int i);									//a
	void Parenthesis_Pattern(int i);							//(a + a) * b
	void Math_Pattern(int i, vector<string> Operator, int Flag);			//a = b + c * d
	void Number_Pattern(int i);									//123
	void String_Pattern(int i);									//"abc"
	void Operator_PreFix_Pattern(int i, vector<string> Prefix);	//++a/--b
	void PreFix_Variable_Pattern(int i);						//-a, -b()
	void Callation_Pattern(int i);								//b(a, b, c, d)
	void Array_Pattern(int i);									//a[1]/b[a]
	void Function_Pattern(int i);								//func int ptr f(int x) {..}
	void Type_Pattern(int i);									//type [inheritted] foo{member 1,}
	void Member_Pattern(int i);									//Dot operator is in Operator_Pattern()
	void If_Pattern(int i);
	void Return_Pattern(int i);
	void Size_Pattern(int i);									//if (contidion){..}
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	//Pattern Users
	void Operator_Order();
	void Factory();
private:
};

#endif
