#ifndef _PARSER_H_
#define _PARSER_H_
#include <vector>
#include <string>
#include "../Lexer/Word.h"
#include "../Lexer/Definer.h"
#include "../Back/Token.h"
#include "../Back/StackFrame.h"
using namespace std;

class Parser
{
public:
	string Working_Dir = "";
    int Layer = 0;
    int ID = 0;
    vector<Word*> Input;
    vector<Token*> Output;
    vector<string*> Included_Files; //for loop holes to not exist
    vector<string> Defined_Keywords;
    void Init_Definition(int i);
    void Init_Operator(int i, string Filter);
    void Init_Parenthesis(int i);
    void Init_Conditions(int i);
    void Math_Order();
    void Init_Function(int i);
    void Factory();
    Parser &operator=(const Parser& other)
    {
        Layer = other.Layer;
        ID = other.ID;
        return *this;
    }
    ~Parser()
    {
    }
};

#endif