
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

string Token::InitToken(Token *v, Token *type, string &code)
{
    string result = "";
    if (NULL(v->Reg->Name))
    {

        if (v->is(Member))
        {
            Register *ParentReg = v->ParentFunc->Reg;
            if (NULL(ParentReg->Name))
            {
                //allocate new Register for class address place holding.
                v->ParentFunc->Reg = v->getReg();
                code += MOV + ParentReg->Name + FROM + FRAME(type->getFullName()) + NL;
            }
            code += MOV + v->Reg->Name + FROM + DWORD + FRAME(ParentReg->Name + OFFSET + to_string(v->StackOffset)) + NL;
        }
        else if (v->is(Public))
        {
            code += MOV + v->Reg->Name + FROM + DWORD + FRAME(v->getFullName()) + NL;
        }
        else if (v->is(Equ))
        {
            code += MOV + v->Reg->Name + FROM + v->getFullName() + NL;
        }
        result = v->Reg->Name;
    }
    else
    {
        result = v->Reg->Name;
    }
    return result;
}

string Token::InitToken(Token *v, string &code)
{
    InitToken(v, new Token(), code);
}