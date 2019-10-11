#include "H/Token.h"
#include "H/Register.h"

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
