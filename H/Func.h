#ifndef _FUNC_H_
#define _FUNC_H_
#include <vector>
#include <string>
#include "Token.h"
#include "Register.h"

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
};


#endif