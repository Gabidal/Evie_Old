#ifndef _PARSER_H_
#define _PARSER_H_
#include <vector>
#include <string>
#include "../Lexer/Word.h"
#include "../Lexer/Definer.h"
#include "../Back/Token.h"
using namespace std;

class Parser
{
public:
	string Working_Dir = "";
    vector<Word*> Input;
    vector<Token*> Output;
    vector<string*> Included_Files; //for loop holes to not exist
    vector<string> Defined_Keywords;
    void Init_Definition(int i);
    void Init_Operator(int i, string Filter);
    void Init_Parenthesis(int i);
    void Init_Conditions(int i);
    void Math_Order();
    void Type_Definition(int i);
    bool Defined(string name);
    int Count_Familiar_Tokens(int F, int i);
    void Init_Variable(int i);
    void Check_For_Correlation(int i);
    void Factory();
    Parser &operator=(const Parser& other)
    {
        return *this;
    }
    ~Parser()
    {
    }
};

#endif