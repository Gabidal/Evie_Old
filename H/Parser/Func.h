#ifndef _FUNC_H_
#define _FUNC_H_
#include <vector>
#include <string>
#include "Token.h"
#include "Register.h"
#include "Assembly_Definitions.h"

class Father : public Token
{
  public:
    Father(string &output) : Token(output){}
    vector<Token*> Childs;
    void addChild(Token *t);
};

class Func : public Father
{
  public:
    Func(bool getsThisAsParameter, string &output);
    vector<Token*> Parameters;
    void addParameter(Token *Param);
    void InitFunction(string &output);
    void CallFunc(string &output);
};



#endif