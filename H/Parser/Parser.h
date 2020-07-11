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
	void Definition_Pattern(int i);
	void Object_Pattern(int i);
	void Paranthesis_Pattern(int i);
	void Math_Pattern(int i, vector<string> Operator);
	void Number_Pattern(int i);
	void Operator_PreFix(int i, vector<string> Prefix);
	void Factory();
private:

};

#endif
