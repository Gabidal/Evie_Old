#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <string>
using namespace std;

class Register
{
public:
    bool TaskForReturning = false;
    bool TaskForTypeAddress = false;
    bool TaskForMovingParameter = false;
    string Name = "";
    int Value = 0;
    Register(string name)
    {
        Name = name;
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