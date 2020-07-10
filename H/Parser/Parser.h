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
	Parser(){}
	~Parser(){}
	vector<string> Defined;
	vector<Component> Input;
	void Definition_Pattern(int i);
	void Factory();
private:

};

#endif
