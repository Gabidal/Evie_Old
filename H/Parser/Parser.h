#ifndef _PARSER_H_
#define _PARSER_H_
#include "../Lexer/Component.h"

#include <vector>

using namespace std;

class Parser
{
public:
	Parser(){}
	~Parser(){}
	vector<Component> Input;
	void Factory();
private:

};

#endif
