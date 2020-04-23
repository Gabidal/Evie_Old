#ifndef _SAFE_H_
#define _SAFE_H_
#include "../../H/Selector/Selector.h"
#include "../../H/Back/Token.h"
#include "../../H/OpC/IR.h"

class Safe
{
private:
	map<string, int> Cache_Usation;
    string Context = "Global";
    vector<string> Avoid_Duplication;
public:
    vector<IR*> Input;
    vector<IR*> Output;
    vector<Token*> Types;
    Safe(){}
    ~Safe(){}
    void Factory();
    void Insight(IR* t);

    void Safe_Cache_Usation(Token* t);
    void Safe_Type_Inheritance(Token* t);

    void Get_Token_Info(Token* t, int layer);

    void Append(vector<IR*> &d, vector<IR*> s);
    Token* Find(string name);
};



#endif