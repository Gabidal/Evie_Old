
#include <string>
#include "H/Parser/Token.h"
#include "H/Parser/Register.h"
#include "H/Parser/Assembly_Definitions.h"
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
            name = EBP->Name + OFFSET + to_string(StackOffset);
        }
        else
        {
            name = EBP->Name + DEOFFSET + to_string(StackOffset);
        }
    }
    return name;
}

Register *Token::getNewRegister()
{
    if (RegisterTurn == 0)
    {
        return EAX;
        RegisterTurn = 1;
    }
    else if (RegisterTurn == 1)
    {
        return EBX;
        RegisterTurn = 2;
    }
    else if (RegisterTurn == 2)
    {
        return ECX;
        RegisterTurn = 3;
    }
    else if (RegisterTurn == 3)
    {
        return EDX;
        RegisterTurn = 4;
    }
    else if (RegisterTurn == 4)
    {
        return ESI;
        RegisterTurn = 5;
    }
    else if (RegisterTurn == 5)
    {
        return EDI;
        RegisterTurn = 0;
    }
}

Register *Token::getReg()
{
    if (Reg->Name == "null")
    {
        this->Reg = getNewRegister();
    }
    return Reg;
}

string Token::InitVariable()
{
    string result = "";
    if (NULL(this->Reg->Name))
    {

        if (this->is(Member))
        {
            Register *ParentReg = this->ParentFunc->Reg;
            if (NULL(ParentReg->Name))
            {
                //allocate new Register for class address place holding.
                this->ParentFunc->Reg = this->getReg();
                output += MOV + ParentReg->Name + FROM + FRAME(ParentType->getFullName()) + NL;
            }
            output += MOV + this->Reg->Name + FROM + DWORD + FRAME(ParentReg->Name + OFFSET + to_string(this->StackOffset)) + NL;
        }
        else if (this->is(Public))
        {
            output += MOV + this->Reg->Name + FROM + DWORD + FRAME(this->getFullName()) + NL;
        }
        else if (this->is(Equ))
        {
            output += MOV + this->Reg->Name + FROM + this->getFullName() + NL;
        }
        result = this->Reg->Name;
    }
    else
    {
        result = this->Reg->Name;
    }
    return result;
}

string Token::MOVE(Token *Source)
{
    output += MOV + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::SUM(Token *Source)
{
    output += ADD + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::SUBSTRACT(Token *Source)
{
    output += SUB + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::MULTIPLY(Token *Source)
{
    output += IMUL + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::DIVIDE(Token *Source)
{
    output += IDIV + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::COMPARE(Token *Source)
{
    output += CMP + this->InitVariable() + FROM + Source->InitVariable();
    return this->Reg->Name;
}

string Token::MOVEINSTACK()
{
    output += PUSH(this->getFullName());
}
