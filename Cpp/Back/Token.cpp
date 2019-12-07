
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
			output += COMMENT + "Adding type owner name to the function name" + NL;
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
		//output += COMMENT + "Private ";
        if (is(Parameter))
        {
			//output +="variable " + NL;
            name = EBP->Name + OFFSET + to_string(this->ParameterOffset + 4);
        }
        else
        {
			//output += "variable " + NL;
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
		EAX->Apply(this, Input);
        return EAX;
    }
    else if (RegisterTurn == 1)
    {
        RegisterTurn = 2;
        EBX->Link(this);
		EBX->Apply(this, Input);
        return EBX;
    }
    else if (RegisterTurn == 2)
    {
        RegisterTurn = 3;
        ECX->Link(this);
		ECX->Apply(this, Input);
        return ECX;
    }
    else if (RegisterTurn == 3)
    {
        RegisterTurn = 4;
        EDX->Link(this);
		EDX->Apply(this, Input);
        return EDX;
    }
    else if (RegisterTurn == 4)
    {
        RegisterTurn = 5;
        ESI->Link(this);
		ESI->Apply(this, Input);
        return ESI;
    }
    else if (RegisterTurn >= 5)
    {
        RegisterTurn = 0;
        EDI->Link(this);
		EDI->Apply(this, Input);
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
		output += COMMENT + "Giving " + this->Name + ", " + this->Reg->Name + NL;
    }
    return Reg;
}

string Token::InitVariable()
{
    string result = "";
    if (this->Reg == nullptr || this->Reg->Name == "null")
    {
		this->Reg = getReg();
		output += COMMENT + "Initializing new register for ";
		if (this->is(Number))
		{
			output += "number " + this->Name + NL;
			output += MOV + this->Reg->Name + FROM + this->Name + NL;
		}
        else if (this->is(Member) && (this->Fetcher != nullptr))
        {
			output +="member variable " + this->Name + NL;
			if (Fetcher->Reg == nullptr)
			{
				//allocate new Register for class address place holding.
				Fetcher->InitVariable();
			}
			output += MOV + this->getReg()->Name + FROM + FRAME(Fetcher->Reg->Name + OFFSET + to_string(this->StackOffset - 4)) + NL;
        }
		else if (this->is(Public))
		{
			output += "public variable " + this->Name + NL;
			if (ARRAY)
			{
				output += LEA + this->Reg->Name + FROM + FRAME(this->getFullName()) + NL;
			}
			else
			{
				output += MOV + this->Reg->Name + FROM + FRAME(this->getFullName()) + NL;
			}
		}
        else if (this->is(Private))
        {
			output +="private  variable " + this->Name + NL;
			if (ARRAY)
			{
				output += LEA + this->Reg->Name + FROM + FRAME(this->getFullName()) + NL;
			}
			else
			{
				output += MOV + this->Reg->Name + FROM + FRAME(this->getFullName()) + NL;
			}
        }
        else if (this->is(Equ))
        {
            output += MOV + this->Reg->Name + FROM + this->getFullName() + NL;
        }
        result = this->Reg->Name;
    }
    else
    {
		output += COMMENT + this->Name + " has already a register to it" + NL;
        result = this->Reg->Name;
    }
    return result;
}

string Token::MOVE(Token *Source)
{
    PTRING(Source);
    if (Source->is(Number))
    {
		output += COMMENT + "Giving " + this->Name + ", " + Source->Name + NL;
        output += MOV + this->GetAddress() + FROM + string(DWORD) + Source->Name + NL;
    }
    else if (this->is(Member) && (this->Fetcher != nullptr))
    {
        // straight movation
		output += COMMENT + "Feching " + this->Name + " from " + this->Fetcher->Name + NL;
        output += MOV + FRAME(this->Fetcher->InitVariable() + OFFSET + to_string(this->StackOffset - 4)) + FROM + DWORD + Source->InitVariable() + NL;
        this->Reg = Source->Reg;
        Source->Reg->Link(this);
    }
    else if (Source->is(Array))
    {
		//mov eax, [ebp + 8]
		//lea esi, [eax + 0 * 4]
		output += COMMENT + "From " + Source->Name + " added address by value of " + Source->Offsetter->Name + NL;
		output += LEA + ESI->Name + FROM + Source->GetAddress() + NL;
		ESI->Link(Source);
		if (this->is(Array))
		{
			output += COMMENT + "From " + this->Name + " added address by value of " + this->Offsetter->Name + NL;
			output += LEA + EDI->Name + FROM + this->GetAddress() + NL;
			EDI->Link(this);
			output += COMMENT + "Saving the value from " + Source->Name + " offsetted by " + Source->Offsetter->Name + NL;
			if (this->repz != nullptr)
			{
				if (repz->is(Number))
				{
					output += MOV + ECX->Name + FROM + repz->Name + NL;
				}
				else
				{
					output += MOV + ECX->Name + FROM + FRAME(repz->getFullName()) + NL;
				}
				output += REPZ + MOVSD + NL;
			}
			else
			{
				output += MOVSD + NL;
			}
		}
		else
		{
			//mov [(ebp - 4) + (ebp - 8) * 4], dword eax
			output += COMMENT + "Saving the value from " + Source->Name + " offsetted by " + Source->Offsetter->Name + NL;
			output += MOV + this->GetAddress() + FROM + DWORD + ESI->Name + NL + NL;
		}
    }
    else if (Source->is(Ptr) || Source->is(Variable))
    {
        // straight movation
		output += COMMENT + "Saving " + Source->Name + " into " + this->Name + NL;
        output += MOV + GetAddress() + FROM + DWORD + Source->InitVariable() + NL;
        this->Reg = Source->Reg;
        Source->Reg->Link(this);
    }
    else if (Source->is(Returning))
    {
        if (Source->Parameters.size() > 0)
        {
			output += COMMENT + "Clearing the parameters" + NL;
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
        }
		output += COMMENT + "Giving " + this->Name + " the return value" + NL;
        output += POP + string(DWORD) + this->GetAddress() + NL + NL;
    }
    
    return "";
}

string Token::SUM(Token *Source)
{
    PTRING(Source);
    if (Source->is(Returning))
    {
        if (Source->Parameters.size() > 0)
        {
			output += COMMENT + "Clearing the parameters" + NL;
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
        }
		output += COMMENT + "Giving " + this->Name + " the return value" + NL;
        output += POP + this->InitVariable() + NL + NL;
    }
    if (Source->is(Number))
    {
		output += COMMENT + "Direct addition" + NL;
        output += ADD + this->InitVariable() + FROM + Source->Name + NL;
    }
	else if (Source->is(Array))
	{
		output += COMMENT + "From " + Source->Name + " added address by value of " + Source->Offsetter->Name + NL;
		output += MOV + Source->getReg()->Name + FROM + FRAME(Source->getFullName()) + NL;
		if ((Source->Offsetter->is(Number) != true) && (Source->is(Public) != true))
		{
			output += COMMENT + "Fixing Base Pointer" + NL;
			output += POP + EBP->Name + NL + NL;
		}
		output += COMMENT + "Adding the value from " + Source->Name + " offsetted by " + Source->Offsetter->Name + NL;
		output += ADD + this->GetAddress() + FROM + Source->Reg->Name + NL + NL;
	}
    else if (Source->is(Ptr) || Source->is(Variable))
    {
		output += COMMENT + "Adding " + Source->Name + " into " + this->Name + NL;
        if (Source->Reg == nullptr || Source->Reg->Name == "null")
        {
			output += COMMENT + "Just directly get address" + NL;
            output += ADD + this->InitVariable() + FROM + Source->GetAddress() + NL;
        }
        else
        {
			output += COMMENT + "There is already register for it, use it" + NL;
            output += ADD + this->InitVariable() + FROM + Source->Reg->Name + NL;
        }
    }
    return this->Reg->Name;
}

string Token::SUBSTRACT(Token *Source)
{
    PTRING(Source);
    if (Source->is(Returning))
    {
        if (Source->Parameters.size() > 0)
        {
			output += COMMENT + "Clearing the parameters" + NL;
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
        }
		output += COMMENT + "Giving " + this->Name + " the return value" + NL;
        output += POP + this->InitVariable() + NL + NL;
    }
    if (Source->is(Number))
    {
		output += COMMENT + "Direct substraction" + NL;
        output += SUB + this->InitVariable() + FROM + Source->Name + NL;
    }
	else if (Source->is(Array))
	{
		output += COMMENT + "From " + Source->Name + " added address by value of " + Source->Offsetter->Name + NL;
		output += MOV + Source->getReg()->Name + FROM + FRAME(Source->getFullName()) + NL;
		if ((Source->Offsetter->is(Number) != true) && (Source->is(Public) != true))
		{
			output += COMMENT + "Fixing Base Pointer" + NL;
			output += POP + EBP->Name + NL + NL;
		}
		output += COMMENT + "Substracting the value from " + Source->Name + " offsetted by " + Source->Offsetter->Name + NL;
		output += SUB + this->GetAddress() + FROM + Source->Reg->Name + NL + NL;
	}
    else if (Source->is(Ptr) || Source->is(Variable))
    {
		output += COMMENT + "Substracting " + Source->Name + " into " + this->Name + NL;
        if (Source->Reg == nullptr || Source->Reg->Name == "null")
        {
			output += COMMENT + "Just directly get address" + NL;
            output += SUB + this->InitVariable() + FROM + Source->GetAddress() + NL;
        }
        else
        {
			output += COMMENT + "There is already register for it, use it" + NL;
            output += SUB + this->InitVariable() + FROM + Source->Reg->Name + NL;
        }
    }
    return this->Reg->Name;
}

string Token::MULTIPLY(Token *Source)
{
    PTRING(Source);
    if (Source->is(Returning))
    {
        if (Source->Parameters.size() > 0)
        {
			output += COMMENT + "Clearing the parameters" + NL;
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
        }
		output += COMMENT + "Giving " + this->Name + " the return value" + NL;
        output += POP + this->InitVariable() + NL + NL;
    }
    if (Source->is(Number))
    {
		output += COMMENT + "Direct multiplying" + NL;
        output += IMUL + this->InitVariable() + FROM + Source->Name + NL;
    }
    else if (Source->is(Member))
    {
		output += COMMENT + "Feching " + this->Name + " from " + this->Fetcher->Name + NL;
        output += IMUL + this->InitVariable() + FROM + Source->InitVariable() + NL;
    }
    else if (Source->is(Array))
    {
		output += COMMENT + "From " + Source->Name + " added address by value of " + Source->Offsetter->Name + NL;
        output += MOV + Source->getReg()->Name + FROM + FRAME(Source->getFullName()) + NL;
		if ((Source->Offsetter->is(Number) != true) && (Source->is(Public) != true))
        {
			output += COMMENT + "Fixing Base Pointer" + NL;
            output += POP + EBP->Name + NL + NL;
        }
		output += COMMENT + "Multiplying the value from " + Source->Name + " offsetted by " + this->Name + NL;
        output += IMUL + this->GetAddress() + FROM + Source->Reg->Name + NL + NL;
    }
    else if (Source->is(Ptr) || Source->is(Variable))
    {
		output += COMMENT + "Multiplying " + Source->Name + " into " + this->Name + NL;
        if (Source->Reg == nullptr || Source->Reg->Name == "null")
        {
			output += COMMENT + "Just directly get address" + NL;
            output += IMUL + this->InitVariable() + FROM + Source->GetAddress() + NL;
        }
        else
        {
			output += COMMENT + "There is already register for it, use it" + NL;
            output += IMUL + this->InitVariable() + FROM + Source->Reg->Name + NL;
        }
    }
    return this->Reg->Name;
}

string Token::DIVIDE(Token *Source)
{
    PTRING(Source);
    if (Source->is(Returning))
    {
        if (Source->Parameters.size() > 0)
        {
			output += COMMENT + "Clearing the parameters" + NL;
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
        }
		output += COMMENT + "Giving " + this->Name + " the return value" + NL;
        output += POP + EAX->Name + NL;
        output += CDQ + string(NL);
        output += DIV + this->InitVariable() + NL;
        EAX->Link(this);
    }
    if (Source->is(Number))
    {
        //cdq
		output += COMMENT + "Direct division" + NL;
        output += XCHG(this->InitVariable(), EAX->Name);
        output += CDQ + string(NL);
        output += DIV + Source->InitVariable() + NL;
        EAX->Link(this);
    }
    else if (Source->is(Array))
    {
        //cdq
		output += COMMENT + "From " + Source->Name + " added address by value of " + Source->Offsetter->Name + NL;
        output += XCHG(this->InitVariable(), EAX->Name);
        output += CDQ + string(NL);
		output += COMMENT + "Dividing the value from " + Source->Name + " offsetted by " + this->Name + NL;
        output += DIV + FRAME(Source->getFullName()) + NL;
        EAX->Link(this);
    }
    else if (Source->is(Ptr) || Source->is(Variable))
    {
		output += COMMENT + "Dividing " + Source->Name + " into " + this->Name + NL;
        output += XCHG(this->InitVariable(), EAX->Name);
        output += CDQ + string(NL);
        if (Source->Reg == nullptr || Source->Reg->Name == "null")
        {
			output += COMMENT + "Just directly get address" + NL;
            output += DIV + string(DWORD) + Source->GetAddress() + NL;
        }
        else
        {
			output += COMMENT + "There is already register for it, use it" + NL;
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
		output += COMMENT + "Just directly get address" + NL;
        output += CMP + this->InitVariable() + FROM + Source->GetAddress() + NL;
    }
    else
    {
		output += COMMENT + "There is already register for it, use it" + NL;
        output += CMP + this->InitVariable() + FROM + Source->Reg->Name + NL + NL;
    }
    return this->Reg->Name;
}

string Token::MOVEINSTACK()
{
    output += PUSH + this->getFullName();
    return this->getReg()->Name;
}

bool skip_ptr_check = false;
string Token::GetAddress()
{
    if (this->is(Array) || this->is(Ptr))
    {
		if (this->is(Ptr) && (skip_ptr_check == false))
		{
			if (this->Outside_Of_Parameters)
			{
				skip_ptr_check = true;
				//lea edx, [ebp - 4]
				//push edx
				getReg();
				output += LEA + Reg->Name + FROM + this->GetAddress() + NL;
				skip_ptr_check = false;
				return Reg->Name;
			}
			else
			{
				//mov eax, [ebp + 8]
				//lea esi, [eax + 0 * 4]
				getReg();
				output += MOV + Reg->Name + FROM + FRAME(this->getFullName()) + NL;
			}
		}
        if (this->is(Array) && this->Offsetter->is(Number))
        {
			//[(ebp - 8) + 1 * 4]
			output += COMMENT + "Adding the offset of " + this->Name + " by " + this->Offsetter->Name + NL;
			if (this->is(Ptr))
			{
				return FRAME(this->Reg->Name + OFFSET + this->Offsetter->Name + SCALE + "4");
			}
			else
			{
				return FRAME(CONTENT(this->getFullName()) + OFFSET + this->Offsetter->Name + SCALE + "4");
			}
        }
        else if (this->is(Array) && this->Offsetter->is(Variable))
        {
			//[(ebp - 8) + (ebp - 4) * 4]
			if (this->is(Ptr))
			{
				return FRAME(this->Reg->Name + OFFSET + CONTENT(this->Offsetter->InitVariable()) + SCALE + "4");
			}
			else
			{
				return FRAME(CONTENT(this->getFullName()) + OFFSET + CONTENT(this->Offsetter->InitVariable()) + SCALE + "4");
			}
        }
        //lea eax, [eax]
        else if (this->is(Ptr) && this->is(Loader))
        {
			this->getReg();
			output += COMMENT + "Load the value inside the pointer" + NL;
            output += LEA + this->Reg->Name + FROM + FRAME(this->Reg->Name) + NL;
            return FRAME(this->Reg->Name);
        }
        //mov ebx, eax
        else if (this->is(Ptr) && this->is(Storer))
        {
			this->getReg();
			output += COMMENT + "Give the pointer address" + NL;
			return FRAME(this->Reg->Name);
        }
		//lea eax, [ebp - 8]
		else
		{

			return FRAME(getFullName());
		}
	}
	if (this->is(Private))
	{

		return FRAME(getFullName());
	}
	else
	{
		return FRAME(getFullName());
	}
}

void Token::addChild(Token* local, bool func)
{
	Childs.push_back(local);
	if (func)
		local->ParentFunc = this;
	else if (func == false)
		local->ParentType = this;
	local->StackOffset = this->StackOffset;
	this->StackOffset += local->Size;
	this->Size += local->Size;
	local->Flags |= Private;
}

void Token::addParameter(Token* Param)
{
	Param->ParameterOffset = this->ParameterOffset;
	Parameters.push_back(Param);
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

void Token::CallFunc(Token* Fetcher)
{
	//check if its fetched;
	if (this->is(This))
	{
		//fetcher is needed;

	}

}

Token& Token::operator=(const Token& name)
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

void Register::Link(Token* Requester)
{
	Current = Requester;
	if (Base != nullptr)
	{
		Base->Reg = NUL;
	}
	Base = Current;
}

void Register::Apply(Token* Requester, vector<Token*> *T)
{
	for (int i = 0; i < T->size(); i++)
	{
		if (T->at(i)->Offsetter != nullptr)
		{
			if (T->at(i)->Offsetter->Name == Requester->Name)
			{
				if (T->at(i)->Offsetter->Flags == Requester->Flags)
				{
					T->at(i)->Offsetter->Reg = this;
				}
			}
		}
		if (T->at(i)->Childs.size() > 0)
		{
			Apply(Requester, &T->at(i)->Childs);
		}
		else if (T->at(i)->Name == Requester->Name)
		{
			if (T->at(i)->Flags == Requester->Flags)
			{
				T->at(i)->Reg = this;
			}
		}
	}
}

void Token::PTRING(Token *&T)
{
    if (T->is(Ptr) && this->is(Ptr))
    {
        //* to * operation
		output += COMMENT + "Pointer to pointer directionation" + NL;
        T->Flags |= Storer;
    }
    else if (T->is(Ptr) && (this->is(Ptr) != true))
    {
        //var to * operation
		output += COMMENT + "Pointer address value to variable" + NL;
        T->Flags |= Loader;
    }
}
