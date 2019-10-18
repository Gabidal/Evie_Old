#ifndef _FUNC_H_
#define _FUNC_H_
#include <vector>
#include <string>
#include "Token.h"
#include "Register.h"
#include "Assembly_Definitions.h"

class Father : public Token
{
    vector<Token*> Childs;
    void addChild(Token *t);
};

class Func : public Father
{
  public:
    vector<Token*> Parameters;
    Token *Parent;
    void addParameter(Token *Param);
    Func(bool getsThisAsParameter);
    void InitFunction(string &output);
    void CallFunc(string &output);
};



#endif