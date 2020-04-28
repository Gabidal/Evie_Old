#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>
#include <vector>
#include "../UI/Usr.h"

using namespace std;

//Identifiers
constexpr int _Number_(1 << 0);
constexpr int _External_ (1<<1);
constexpr int _Type_ (1<<2);
constexpr int _Function_ (1<<3);
constexpr int _Array_ (1<<4);
constexpr int _Condition_ (1<<5);
constexpr int _Operator_ (1<<6);
constexpr int _Returning_ (1<<7);
constexpr int _Call_ (1<<8);
constexpr int _Parameter_ (1<<9);
constexpr int _Parenthesis_ (1<<10);
constexpr int _Constructor_ (1<<11);
constexpr int _Register_ (1<<12);

//  registers
constexpr int Task_For_Non_Volatiling (1<<13);
constexpr int Task_For_Returning (1<<14);
constexpr int Task_For_Type_Address_Basing (1<<15);
constexpr int Task_For_Type_Address (1<<16);
constexpr int Task_For_Moving_Parameter (1<<17);
constexpr int Task_For_Offsetting (1<<18);
constexpr int Task_For_Remainder (1<<19);
constexpr int Task_For_General_Purpose (1<<20);
constexpr int Task_For_Floating_Math (1<<21);

//for stack reservartion
constexpr int _Need_For_Space_ (1<<22);
constexpr int _Generated_ (1<<23);

//for pointting pointters
constexpr int _Pointting_ (1<<24);
constexpr int _Giving_Address_ (1<<25);
constexpr int _String_ (1<<26);
constexpr int _Preprosessor_ (1<<27);
constexpr int _Skip_ (1<<28);
constexpr int _Combined_ (1<<29);
constexpr int _Initialized_ (1<<30);
constexpr int _Locked_(1 << 31); //!!!

class Token : public Object
{
    private:
    int Flags = 0;
  public:
    map<string, Object*> Get_Members();
    int Size = 0;
    int Reservable_Size = 0;
    int Changable_Value = 0;
    int StackOffset = 0;
    int ParameterCount = 0;
    int ID = 0;
    bool Semanticked = false;
    bool _Dynamic_Size_ = false;
    Token* Left_Side_Token = nullptr;
    Token* Right_Side_Token = nullptr; 
    Token* Offsetter = nullptr;// also as the offsetter in array
    Token* Initial_Value = nullptr;
    //EXPERIMENTAL!!
    Token* Right_Non_Operative_Token = nullptr;
    Token* Left_Non_Operative_Token = nullptr;
    vector<Token*> Childs;
    vector<string> Types;
    string Context = "";
    string Name = "";
    string UID = "";
    string State = "";
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

    string Gather_Types(string comma);
    bool is(int flag);
    bool Any(int flags);
    void add(int flag);
    void remove(int flag);
    int get();
    bool is(string type);
    string Get_Additive_Operator();
    //From this point on there are optimizing
    //Member's.
    //Have fun!
    string Name_Of_Same_Using_Register = "";
};
#endif

