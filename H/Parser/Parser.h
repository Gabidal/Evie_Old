#ifndef _PARSER_H_
#define _PARSER_H_
#include <vector>
#include <string>
#include "../Lexer/Word.h"
#include "../Back/Token.h"
#include <algorithm>
using namespace std;

class Parser
{
public:
	string Working_Dir = "";
    vector<Word*> Input;
    vector<Token*> Output;
    vector<string*> Included_Files; //for loop holes to not exist
    vector<Token*> Defined_Keywords;
    void Init_Definition(int i);
    void Init_Operator(int i);
    void Reserve_Operator_Tokens(int i);
    void Patternize_Operations(int& i, string f);
    void Do_In_Order();
    void Init_Parenthesis(int i);
    void Init_Conditions(int i);
    void Type_Definition(int i);
    void Set_Right_Stack_Offset(Token* t);
    void Set_Right_Flag_Info(Token* t);
    string Defined(string name);
    int Count_Familiar_Tokens(int F, int i);
    void Init_Variable(int i);
    void Check_For_Correlation(int i);
    void Factory();
    void Append(vector<Token*>* Dest, vector<Token*> Source);
    Parser &operator=(const Parser& other)
    {
        Working_Dir = other.Working_Dir;
        //Input = other.Input;
        //Output = other.Output;
        Included_Files = other.Included_Files;
        Defined_Keywords = other.Defined_Keywords;
        return *this;
    }
    ~Parser()
    {
    }
};

#endif