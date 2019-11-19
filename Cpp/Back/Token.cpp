
#include <string>
#include "../../H/Back/Token.h"
#include "../../H/Back/Assembly_Definitions.h"
#include "../../H/Back/Registers.h"
using namespace std;

int RegisterTurn = 0;

bool Token::is(int flag)
{
    return (Flags & flag) == flag;
}

bool Token::Any(int flags)
{
    return (Flags & flags) != 0;
}

string Token::getFullName()
{
    string name = "";
    if (is(Call) || is(If) || is(Else) || is(While))
    {
        if (is(Member))
        {
            return TYPE(this->Fetcher->Origin->Name, this->Name);
        }
        else
        {
            return this->Name;
        }
    }
    
    if (is(Public))
    {
        name = Name;
    }
    else
    {
        if (is(Parameter))
        {
            name = EBP->Name + OFFSET + to_string(StackOffset + 4);
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
        RegisterTurn = 1;
        EAX->Link(this);
        return EAX;
    }
    else if (RegisterTurn == 1)
    {
        RegisterTurn = 2;
        EBX->Link(this);
        return EBX;
    }
    else if (RegisterTurn == 2)
    {
        RegisterTurn = 3;
        ECX->Link(this);
        return ECX;
    }
    else if (RegisterTurn == 3)
    {
        RegisterTurn = 4;
        EDX->Link(this);
        return EDX;
    }
    else if (RegisterTurn == 4)
    {
        RegisterTurn = 5;
        ESI->Link(this);
        return ESI;
    }
    else if (RegisterTurn >= 5)
    {
        RegisterTurn = 0;
        EDI->Link(this);
        return EDI;
    }
    else
    {
        return NULL;
    }
}

Register *Token::getReg()
{
    if (Reg == nullptr|| Reg->Name == "null")
    {
        this->Reg = getNewRegister();
    }
    return Reg;
}

string Token::InitVariable()
{
    string result = "";
    if (this->Reg == nullptr || this->Reg->Name == "null")
    {
        this->Reg = getReg();
        if (this->is(Member))
        {
            Register *ParentReg = this->ParentFunc->Reg;
            if (ParentReg == nullptr)
            {
                //allocate new Register for class address place holding.
                ParentReg = this->getReg();
                ParentFunc->Reg = ParentReg;
                output += MOV + ParentReg->Name + FROM + FRAME(ParentFunc->getFullName()) + NL;
            }
            output += MOV + this->Reg->Name + FROM + FRAME(ParentReg->Name + OFFSET + to_string(this->StackOffset)) + NL;
        }
        else if (this->is(Ptr))
        {
            output += MOV + this->Reg->Name + FROM + this->GetAddress() + NL;
        }
        else if (this->is(Private))
        {
            output += MOV + this->Reg->Name + FROM + FRAME(this->getFullName()) + NL;
        }
        else if (this->is(Public))
        {
            output += MOV + this->Reg->Name + FROM + DWORD + FRAME(this->getFullName()) + NL;
        }
        else if (this->is(Equ))
        {
            output += MOV + this->Reg->Name + FROM + this->getFullName() + NL;
        }
        else if (this->is(Number))
        {
            output += MOV + this->Reg->Name + FROM + this->Name + NL;
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
    if (Source->is(Number))
    {
        output += MOV + string(DWORD) + this->GetAddress() + FROM + Source->Name + NL;
    }
    else if (Source->is(Ptr) || Source->is(Variable))
    {
        // straight movation
        output += MOV + this->GetAddress() + FROM + Source->InitVariable() + NL;
        this->Reg = Source->Reg;
        Source->Reg->Link(this);
    }
    else if (Source->is(Returning))
    {
        if (Source->Parameters.size() > 0)
        {
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
        }
        output += POP + string(DWORD) + this->GetAddress() + NL + NL;
    }
    
    return "";
}

string Token::SUM(Token *Source)
{
    if (Source->is(Returning))
    {
        if (Source->Parameters.size() > 0)
        {
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
        }
        output += POP + this->InitVariable() + NL + NL;
    }
    if (Source->is(Number))
    {
        output += ADD + this->InitVariable() + FROM + Source->Name + NL;
    }
    else if (Source->is(Ptr) || Source->is(Variable))
    {
        if (Source->Reg == nullptr || Source->Reg->Name == "null")
        {
            output += ADD + this->InitVariable() + FROM + Source->GetAddress() + NL;
        }
        else
        {
            output += ADD + this->InitVariable() + FROM + Source->Reg->Name + NL;
        }
    }
    return this->Reg->Name;
}

string Token::SUBSTRACT(Token *Source)
{
    if (Source->is(Returning))
    {
        if (Source->Parameters.size() > 0)
        {
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
        }
        output += POP + this->InitVariable() + NL + NL;
    }
    if (Source->is(Number))
    {
        output += SUB + this->InitVariable() + FROM + Source->Name + NL;
    }
    else if (Source->is(Ptr) || Source->is(Variable))
    {
        if (Source->Reg == nullptr || Source->Reg->Name == "null")
        {
            output += SUB + this->InitVariable() + FROM + Source->GetAddress() + NL;
        }
        else
        {
            output += SUB + this->InitVariable() + FROM + Source->Reg->Name + NL;
        }
    }
    return this->Reg->Name;
}

string Token::MULTIPLY(Token *Source)
{
    if (Source->is(Returning))
    {
        if (Source->Parameters.size() > 0)
        {
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
        }
        output += POP + this->InitVariable() + NL + NL;
    }
    if (Source->is(Number))
    {
        output += IMUL + this->InitVariable() + FROM + Source->Name + NL;
    }
    else if (Source->is(Ptr) || Source->is(Variable))
    {
        if (Source->Reg == nullptr || Source->Reg->Name == "null")
        {
            output += IMUL + this->InitVariable() + FROM + Source->GetAddress() + NL;
        }
        else
        {
            output += IMUL + this->InitVariable() + FROM + Source->Reg->Name + NL;
        }
    }
    return this->Reg->Name;
}

string Token::DIVIDE(Token *Source)
{
    if (Source->is(Returning))
    {
        if (Source->Parameters.size() > 0)
        {
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
        }
        output += POP + EAX->Name + NL;
        output += CDQ + string(NL);
        output += DIV + this->InitVariable() + NL;
        EAX->Link(this);
    }
    if (Source->is(Number))
    {
        //cdq
        output += XCHG(this->InitVariable(), EAX->Name);
        output += CDQ + string(NL);
        output += DIV + Source->InitVariable() + NL;
        EAX->Link(this);
    }
    else if (Source->is(Ptr) || Source->is(Variable))
    {
        output += XCHG(this->InitVariable(), EAX->Name);
        output += CDQ + string(NL);
        if (Source->Reg == nullptr || Source->Reg->Name == "null")
        {
            output += DIV + string(DWORD) + Source->GetAddress() + NL;
        }
        else
        {
            output += DIV + Source->Reg->Name + NL;
        }
        EAX->Link(this);
    }
    return this->Reg->Name;
}

string Token::COMPARE(Token *Source)
{
    if (Source->Reg == nullptr || Source->Reg->Name == "null")
    {
        output += CMP + this->InitVariable() + FROM + Source->GetAddress() + NL;
    }
    else
    {
        output += CMP + this->InitVariable() + FROM + Source->Reg->Name + NL + NL;
    }
    return this->Reg->Name;
}

string Token::MOVEINSTACK()
{
    output += PUSH + this->getFullName();
    return this->getReg()->Name;
}

string Token::GetAddress()
{
    if (this->is(Array))
    {
        this->Offsetter->InitVariable();
        return FRAME(SUM(Offsetter));
    }
    if (this->is(Private))
    {
        return FRAME(getFullName());
    }
    else
    {
        return getFullName();
    }
}

void Token::addChild(Token *local) 
{
    Childs.push_back(local);
    local->ParentFunc = this;
    local->StackOffset = this->StackOffset;
    this->StackOffset += local->Size;
    this->Size += local->Size;
	local->Flags |= Private;
}

void Token::addParameter(Token *Param)
{
    Parameters.push_back(Param);
    Param->ParameterOffset = this->ParameterOffset;
    this->ParameterOffset += Param->Size;
}

void Token::InitFunction()
{
    if (is(Member))
    {
        output += LABEL(TYPE(ParentType->Name, FUNC(this->Name)));
    }
    else
    {
        output += LABEL(FUNC(this->Name));
    }
}

void Token::CallFunc(Token *Fetcher)
{
    //check if its fetched;
    if (this->is(This))
    {
        //fetcher is needed;
        
    }
    
}

Token &Token::operator=(const Token& name)
{
    Flags = name.Flags;
    Size = name.Size;
    Value = name.Value;
    StackOffset = name.StackOffset;
    ParameterCount = name.ParameterCount;
    AddedOffset = name.AddedOffset;
    ParameterOffset = name.ParameterOffset;
    ID = name.ID;
    Offsetter = name.Offsetter;
    ParentType = name.ParentType;
    ParentFunc = name.ParentFunc;
    Parameters = name.Parameters;
    SuccessorToken = name.SuccessorToken;
    Childs = name.Childs;
    Name = name.Name;
    Reg = name.Reg;
    output = name.output;
    Origin = name.Origin;
    return *this;
}

void Register::Link(Token *Requester)
{
    Current = Requester;
    if (Base != nullptr)
    {
        Base->Reg = NUL;
    }
    Base = Current;
}
