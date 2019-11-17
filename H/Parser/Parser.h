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
    Token *ParentCondition = 0;
    int Layer = 0;
    int ID = 0;
    int Started = 0;
    bool InsideOfType = false;
    bool InsideOfFunction = false;
    bool InsideOfCondition = false;
    bool Priority = false;
    bool GetDirect = false;
    string &Assembly;
    vector<Word*> Input;
    vector<Token*> Output;
    vector<Token*> Direct;
    void Pattern_Variable(int i);
    void Pattern_Function(int i);
    void Pattern_Type(int i);
    void Pattern_Condition(int i);
    void Pattern_Parenthesis(int i);
    void Pattern_Operators(int i);
    void Pattern_Call_Func(int i);
    void Pattern_New(int i);
    void Pattern_Init_Condition(int i);
    void Pattern_Init_Variable(int i);
    void Pattern_Init_Operators(int &i);
    void Pattern_Init_Type(int i);
    void Pattern_Init_Call_Func(int i);
    void Pattern_Init_Array(int i);
    void Pattern_Init_New(int i);
    void Pattern_Return(int i);
    Token *Pattern_Fetcher(int i);
    void Clean_Cilds();
    void Give_Output(vector<Token*> *&T);
    void Give_Input(vector<Token*> *&T);
    int Find(string name, int flags, vector<Token*> list);
    void Factory();
    Parser &operator=(const Parser& other)
    {
        ParentType = other.ParentType;
        ParentFunc = other.ParentFunc;
        Layer = other.Layer;
        ID = other.ID;
        Started = other.Started;
        InsideOfType = other.InsideOfType;
        InsideOfFunction = other.InsideOfFunction;
        //Priority = other.Priority; DO NOT USE THIS <THIS IS THE RED BUTTON>
        Priority = false;
        Assembly = other.Assembly;
        Input = other.Input;
        Output = other.Output;
        InsideOfCondition = other.InsideOfCondition;
        return *this;
    }
    Parser(Parser & other) : Assembly(other.Assembly)
    {
        ParentType = other.ParentType;
        ParentFunc = other.ParentFunc;
        ParentCondition = other.ParentCondition;
        Layer = other.Layer;
        ID = other.ID;
        Started = other.Started;
        InsideOfType = other.InsideOfType;
        InsideOfFunction = other.InsideOfFunction;
        InsideOfCondition = other.InsideOfCondition;
        //Priority = other.Priority; DO NOT USE THIS <THIS IS THE RED BUTTON>
        Priority = false;
        Input = other.Input;
        Output = other.Output;
    }
    Parser(vector<Word*> in, string &a) : Assembly(a) 
    {
        Input = in;
    }
    Parser(vector<Word*> in, vector<Token*> out, string &a) : Assembly(a)
    {
        Input = in;
        Output = out;
        Started = out.size();
    }
    ~Parser()
    {
    }
};

#endif