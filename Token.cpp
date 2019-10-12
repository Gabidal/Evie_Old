
#include <string>
#include "H/Token.h"
#include "H/Register.h"
#include "H/Assembly_Definitions.h"
using namespace std;

int RegisterTurn = 0;

bool Token::is(int flag)
{
    return (Flags & flag) == flag;
}

string Token::getFullName()
{
    string name;
    
    if (is(Public))
    {
        name = Name;
    }
    else
    {
        if (is(Parameter))
        {
            name = EBP->Name + " + " + to_string(StackOffset);
        }
        else
        {
            name = EBP->Name + " - " + to_string(StackOffset);
        }
    }
}

Register Token::getNewRegister()
{
    if (RegisterTurn == 0)
    {
        return *EAX;
        RegisterTurn = 1;
    }
    else if (RegisterTurn == 1)
    {
        return *EBX;
        RegisterTurn = 2;
    }
    else if (RegisterTurn == 2)
    {
        return *ECX;
        RegisterTurn = 3;
    }
    else if (RegisterTurn == 3)
    {
        return *EDX;
        RegisterTurn = 4;
    }
    else if (RegisterTurn == 4)
    {
        return *ESI;
        RegisterTurn = 5;
    }
    else if (RegisterTurn == 5)
    {
        return *EDI;
        RegisterTurn = 0;
    }
}

string Token::getReg()
{
    if (Reg.Name == "null")
    {
        this->Reg = getNewRegister();
    }
    else
    {
        return Reg.Name;
    }
    
}


string Token::InitToken(Token *t)
{
    string result = "";
    if (t->is(Member))
    {
        Register ParentReg = t->ParentFunc->Reg;
        if (NULL(ParentReg.Name))
        {
            //allocate new Register for class address place holding.
            t->ParentFunc->Reg = t->getReg();
            result = MOV + ParentReg.Name + FROM + FRAME(t->ParentFunc->getFullName()) + NL;
        }
        result += MOV + t->Reg.Name + FROM + DWORD + FRAME(ParentReg.Name + OFFSET + to_string(t->StackOffset)) + NL;
    }
    else if (t->is(Public))
    {
        result = MOV + t->Reg.Name + FROM + DWORD + FRAME(t->getFullName()) + NL;
    }
    else if (t->is(Equ))
    {
        result = MOV + t->Reg.Name + FROM + t->getFullName() + NL;
    }
    return result;
    
}
