#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <string>
#include <vector>
using namespace std;

class Token;

class Register
{
public:
    bool TaskForReturning = false;
    bool TaskForTypeAddress = false;
    bool TaskForMovingParameter = false;
    string Name = "";
    int Value = 0;
    vector<Token*> Users;
    Token *Owner;
    Register(string name)
    {
        Name = name;
    }
    void Link(Token *Reguester)
    {
        Users.push_back(Reguester);
        Owner = Reguester;
    }
};

static Register *NUL = new Register("null");
static Register *EAX = new Register("eax");
static Register *EBX = new Register("ebx");
static Register *ECX = new Register("ecx");
static Register *EDX = new Register("edx");
static Register *ESI = new Register("esi");
static Register *EDI = new Register("edi");
static Register *EBP = new Register("ebp");
static Register *ESP = new Register("esp");


#endif