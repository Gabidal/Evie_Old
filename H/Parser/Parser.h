#ifndef _PARSER_H_
#define _PARSER_H_
#include <vector>
#include <string>
#include "../Lexer/Word.h"
#include "../Back/Token.h"
using namespace std;

class Parser
{
public:
    bool InsideOfType = false;
    bool InsideOfFunction = false;
    string Assembly = "";
    vector<Word> Input;
    vector<Token> Output;
    void Pattern_Variable(int i);
    void Pattern_Array(int i);
    void Factory();
    Parser()
    {

    }
    
    ~Parser()
    {
    }
};

#endif