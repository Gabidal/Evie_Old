#ifndef _PARSER_H_
#define _PARSER_H_

#include "../../H/Flags.h"
#include "../Lexer/Component.h"
#include "../Nodes/NODES.h"

#include <vector>

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
	void Paranthesis_Pattern(int i);
	void Factory();
private:

};

#endif
