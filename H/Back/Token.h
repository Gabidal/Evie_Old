#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>
#include <vector>
#include "../Selector/Selector.h"

using namespace std;

//creators
#define _Number_ (1<<0)
#define _External_ (1<<1)
#define _Type_ (1<<2)
#define _Function_ (1<<3)
#define _Array_ (1<<4)
#define _Condition_ (1<<5)
#define _Operator_ (1<<6)
#define _Returning_ (1<<7)
#define _Call_ (1<<8)
#define _Parameter_ (1<<9)
extern int SYNTAX;

#define Task_For_Returning (1<<0)
#define Task_For_Type_Address_Basing (1<<1)
#define Task_For_Type_Address (1<<2)
#define Task_For_Moving_Parameter (1<<3)

class Register;

class Token
{
  public:
    int Flags = 0;
    int Size = 0;
    int Value = 0;
    int StackOffset = 4;
    int ParameterCount = 0;
    int ParameterOffset = 4;
    int ID = 0;
    int &Syntax = SYNTAX;
    bool Semanticked = false;
    Token* Offsetter = nullptr;
    Token* Parent = nullptr;
    vector<Token*> Paralell_Tokens;
    vector<Token*> Left_Side_Token;
    vector<Token*> Right_Side_Token;
    string Name = "";
    string Type = "";
    Register *Reg = nullptr; //used for real
    string SX();
    Token();
    Token &operator=(const Token& name);

    bool is(int flag);
    bool Any(int flags);
    string Get_Agent(bool Giver);
    //agent prepensitives
    string Get_Reg();
    string Get_Mem_Address();
    string Get_Additive_Operator();
    //var
    string Make(Token *Source, string Do);
	bool Passing_String = false;
    //func
    vector<Token*> Calling_Amount;
};


class Register
{
public:
    int Flags = 0;
    string Name = "";
    int Value = 0;
    string ID = "";
    Token *Base;
    int Bit_Size = 0;
    bool is(int flag);
    vector<Token*> History;
    Register(string name, int BS)
    {
        Name = name;
        Bit_Size = BS;
    }
    Register(string name, int BS, string id)
    {
        Name = name;
        Bit_Size = BS;
        ID = id;
    }
    void Link(Token *Requester);
};
#endif

