#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>
#include <vector>
#include "../UI/Usr.h"

using namespace std;

//Identifiers
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
#define _Register_ (1<<12)

//ADVANCED
#define _Inheritting_ (1<<13)

#define Task_For_Returning (1<<14)
#define Task_For_Type_Address_Basing (1<<15)
#define Task_For_Type_Address (1<<16)
#define Task_For_Moving_Parameter (1<<17)
#define Task_For_Offsetting (1<<18)
#define Task_For_Remainder (1<<19)
#define Task_For_General_Purpose (1<<20)
#define Task_For_Floating_Math (1<<21)

//for stack reservartion
#define _Need_For_Space_ (1<<22)
#define _Generated_ (1<<23)

//for pointting pointters
#define _Pointting_ (1<<24)
#define _Array_ (1<<25)
#define _Giving_Address_ (1<<26)
#define _String_ (1<<27)
#define _Preprosessor_ (1<<28)

class Token : public Symbol_Table
{
    private:
    int Flags = 0;
  public:
    map<string, Symbol_Table*> Get_Member_Pointters();
    map<string, Waiter*> Get_Member_Data();
    int Size = 0;
    int Reservable_Size = 0;
    int Initial_Value = 0;
    int Changable_Value = 0;
    int StackOffset = 0;
    int ParameterCount = 0;
    int ID = 0;
    bool Semanticked = false;
    bool _Dynamic_Size_ = false;
    //Token* Parent = nullptr;
    Token* Left_Side_Token = nullptr;
    Token* Right_Side_Token = nullptr; // also as the offsetter in array
    Token* Left_Non_Operative_Token = nullptr;
    Token* Right_Non_Operative_Token = nullptr;
    Token* Offsetter = nullptr;
    vector<Token*> Childs;
    string Name = "";
    string Type = "";
    string PreFix_Type = "";
    string UID = "";
    string State;
    Token(){}
    Token(string name, int size, Token* child) {
        Name = name;
        Size = size;
        Childs.push_back(child);
        add(_Register_);
    }
    Token(string name, int size, Token* child1, Token* child2) {
        Name = name;
        Size = size;
        Childs.push_back(child1);
        Childs.push_back(child2);
        add(_Register_);
    }
    Token(string name, int size) {
        Name = name;
        Size = size;
        add(_Register_);
    }

    bool is(int flag);
    bool Any(int flags);
    void add(int flag);
    void remove(int flag);
    int get();
    string Get_Additive_Operator();
};
#endif

