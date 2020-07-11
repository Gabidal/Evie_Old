#ifndef _PARSER_H_
#define _PARSER_H_

#include "../../H/Flags.h"
#include "../Lexer/Component.h"
#include "../Nodes/NODES.h"

#include <vector>
#include <iostream>

using namespace std;

class Parser
{
public:
	Parser(Scope_Node* p) : Parent(p){}
	~Parser(){}
	Scope_Node* Parent = nullptr;
	vector<Component> Input;
	vector<Component> Get_Inheritting_Components(int i);
	Node* Is_Defined(string name, Scope_Node* p);
	vector<int> Get_Amount_Of(int i, long Flag);
	void Definition_Pattern(int i);								//test ptr a
	void Object_Pattern(int i);									//a
	void Parenthesis_Pattern(int i);							//(a + a) * b
	void Math_Pattern(int i, vector<string> Operator);			//a = b + c * d
	void Number_Pattern(int i);									//123
	void String_Pattern(int i);									//"abc"
	void Operator_PreFix_Pattern(int i, vector<string> Prefix);	//++a/-2123/-(a-b)/-b()
	void Callation_Pattern(int i);								//b(a, b, c, d)
	void Array_Pattern(int i);									//a[1]/b[a]
	void Function_Pattern(int i);								//func int ptr f(int x) {..}
	void Type_Pattern(int i);
	void Factory();
private:

};

#endif
