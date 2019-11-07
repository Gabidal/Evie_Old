#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>
#include <vector>
#include "Register.h"

using namespace std;

//creators
#define _NULL_ (1<<0)
#define Public (1<<1)
#define Member (1<<2)
#define Used (1<<3)
#define Real (1<<4)
#define Function (1<<6)
#define Macro (1<<7)
#define TypE (1<<8)
#define Define (1<<9)
//Variables
#define Number (1<<10)
#define Ptr (1<<11)
#define Variable (1<<12)
#define Array (1<<13)
#define Equ (1<<14)
//Logical
#define If (1<<15)
#define Else (1<<16)
#define While (1<<17)
#define Returning (1<<18)
//Arithmetic
#define OPERATOR (1<<19)

//Personan
#define Registered (1<<20)
#define Stacked (1<<21)
#define Stored (1<<22)
#define NotOriginal (1<<23)
#define Parameter (1<<24)
#define Private (1<<25)
#define This (1<<26)
#define PARENT (1<<27)
#define Call (1<<28)
#define __NEW (1<<29)

class Token
{
  public:
    int Flags = 0;
    int Size = 0;
    int Value = 0;
    int StackOffset = 0;
    int ParameterCount = 0;
    int AddedOffset = 0;
    int ParameterOffset = 0;
    int ID = 0;
    Token *Offsetter;
    Token *ParentType;
    Token *ParentFunc;
    vector<Token> Parameters;
    vector<Token> Childs;
    string Name = "";
    Register *Reg;
    string &output;
    Token(string &out) : output(out){}
    Token &operator=(const Token& name);

    bool is(int flag);
    string getFullName();
    Register *getNewRegister();
    Register *getReg();
    //var
    string InitVariable();
    string MOVE(Token *Source);
    string SUM(Token *Source);
    string SUBSTRACT(Token *Source);
    string MULTIPLY(Token *Source);
    string DIVIDE(Token *Source);
    string COMPARE(Token *Source);
    string MOVEINSTACK();
    //func
    void addChild(Token t);
    void addParameter(Token Param);
    void InitFunction();
    //void CallFunc();
    //type
    bool initted = false;
    Token *Origin;
    vector<Token> Functions;
    void addFunc(Token func);
    void InitType();
};


#endif