#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>
#include <vector>

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
#define _Parenthesis_ (1<<10)
#define _Constructor_ (1<<11)

#define Task_For_Returning (1<<0)
#define Task_For_Type_Address_Basing (1<<1)
#define Task_For_Type_Address (1<<2)
#define Task_For_Moving_Parameter (1<<3)
#define Task_For_Offsetting (1<<4)
#define Task_For_Remainder (1<<5)

class Register;

class Token
{
  public:
    int Flags = 0;
    int Size = 0;
    int Const_Value = 0;
    int Dynamic_Value = 0;
    int Static = 0;
    int StackOffset = 4;
    int ParameterCount = 0;
    int ParameterOffset = 4;
    int ID = 0;
    bool Semanticked = false;
    Token* Offsetter = nullptr;
    Token* Parent = nullptr;
    Token* Left_Side_Token;
    Token* Right_Side_Token;
    vector<Token*> Childs;
    string Name = "";
    string Type = "";
    Register *Reg = nullptr; //used for real
    string SX();
    Token(){}
    Token &operator=(const Token& name);

    bool is(int flag);
    bool Any(int flags);
    string Get_Additive_Operator();
    //var
    //func
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

