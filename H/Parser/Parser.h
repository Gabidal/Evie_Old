#ifndef _PARSER_H_
#define _PARSER_H_
#include <vector>
#include <string>
#include "../Lexer/Word.h"
#include "../Back/Token.h"
#include "../Back/StackFrame.h"
using namespace std;

class Parser
{
public:
    Token *ParentType = 0;
    Token *ParentFunc = 0;
    int Layer = 0;
    int ID = 0;
    bool InsideOfType = false;
    bool InsideOfFunction = false;
    string Assembly = "";
    vector<Word> Input;
    vector<Token> Output;
    void Pattern_Variable(int i);
    void Pattern_Function(int i);
    void Pattern_Type(int i);
    void Pattern_Parenthesis(int i);
    void Pattern_Operators(int i);
    void Pattern_Call_Func(int i);
    void Pattern_New(int i);
    void Pattern_Init_Operators(int i);
    void Pattern_Init_Type(int i);
    void Pattern_Init_Call_Func(int i);
    void Pattern_Init_Array(int i);
    int Find(string name, int flags, vector<Token> list);
    void Factory();
    Parser(vector<Word>in)
    {
        Input = in;
    }
    
    ~Parser()
    {
    }
};

#endif