
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

bool Token::Optimize_Register_Usage()
{
	//optimized register to give to a normal math variable is EAX or EDX
	//optimized rigister to give to offsetter is ECX
	//optimized register to give to array is EDi or ESi
	//optimized register to give to pointers is EBX
	//this part checks is this named variable already has a register to it's name
	if ((ECX->Base != nullptr) && (ECX->Base->Name == this->Name))
	{
		//this has been a offsetter before
		ECX->Link(this);
		this->Reg = ECX;
		return true;
	}
	else if ((EAX->Base != nullptr) && (EAX->Base->Name == this->Name))
	{
		//this is just a normal  math variable
		EAX->Link(this);
		this->Reg = EAX;
		return true;
	}
	else if ((EDX->Base != nullptr) && (EDX->Base->Name == this->Name))
	{
		//this is just a normal  math variable
		EDX->Link(this);
		this->Reg = EDX;
		return true;
	}
	else if ((EDI->Base != nullptr) && (EDI->Base->Name == this->Name))
	{
		if ((this->Offsetter != nullptr) && (EDI->Base->Offsetter->Name == this->Offsetter->Name))
		{
			//same parent variable array, and same offsetters.
			ECX->Link(this->Offsetter);
			this->Offsetter->Reg = ECX;
			EDI->Link(this);
			this->Reg = EDI;
			return true;
		}
		//even if this variable has EDI and,
		//now it doesnt have the same offsetter it wont point to same place enymore
	}
	else if ((ESI->Base != nullptr) && (ESI->Base->Name == this->Name))
	{
		if ((this->Offsetter != nullptr) && (ESI->Base->Offsetter->Name == this->Offsetter->Name))
		{
			//same parent variable array, and same offsetters.
			ECX->Link(this->Offsetter);
			this->Offsetter->Reg = ECX;
			ESI->Link(this);
			this->Reg = ESI;
			return true;
		}
		//even if this variable has ESI and,
		//now it doesnt have the same offsetter it wont point to same place enymore
	}
	else
	{
		return false;
	}
}

Register *Token::getNewRegister()
{
	if (Optimize_Register_Usage())
	{
		//for safety
	}
	else if (is(Variable) || is(Number) || is(Ptr))
	{
		if (RegisterTurn == 0)
		{
			EAX->Link(this);
			Reg = EAX;
			RegisterTurn++;
		}
		else if (RegisterTurn == 1)
		{
			EDX->Link(this);
			Reg = EDX;
			RegisterTurn--;
		}
	}
	else if (is(Array) || is(Ptr))
	{
		if (RegisterTurn == 0)
		{
			EDI->Link(this);
			Reg = EDI;
			RegisterTurn++;
		}
		else if (RegisterTurn > 0)
		{
			ESI->Link(this);
			Reg = ESI;
			RegisterTurn--;
		}
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
        getNewRegister();
		output += COMMENT + "Giving " + this->Name + ", " + this->Reg->Name + NL;
    }
    return Reg;
}

string Token::InitVariable()
{
    string result = "";
    if (this->Reg == nullptr || this->Reg->Name == "null")
    {
		getReg();
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
		NUL->Link(this);
		this->Reg = NUL;
		return this->Reg->Name;
    }
	else if (Source->is(String))
	{
		output += COMMENT + "Giving " + this->Name + " the address of " + Source->StringName + NL;
		output += LEA + this->getReg()->Name + FROM + FRAME(Source->StringName) + NL;
		this->Passing_String = true;
	}
    else if (this->is(Member) && (this->Fetcher != nullptr))
    {
        // straight movation
		output += COMMENT + "Feching " + this->Name + " from " + this->Fetcher->Name + NL;
        output += MOV + FRAME(this->Fetcher->InitVariable() + OFFSET + to_string(this->StackOffset - 4)) + FROM + DWORD + Source->InitVariable() + NL;
        this->Reg = Source->Reg;
        Source->Reg->Link(this);
		return this->Reg->Name;
    }
    else if (Source->is(Array))
    {
		//mov eax, [ebp + 8]
		//lea esi, [eax + 0 * 4]
		output += COMMENT + "From " + Source->Name + " added address by value of " + Source->Offsetter->Name + NL;
		if (Source->is(Address_Operator))
		{
			output += MOV + ESI->Name + FROM + Source->GetAddress() + NL;
		}
		else
		{
			output += LEA + ESI->Name + FROM + Source->GetAddress() + NL;
		}
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
			this->Reg = Source->Reg;
		}
		return this->Reg->Name;
    }
    else if (Source->is(Ptr) || Source->is(Variable))
    {
        // straight movation
		output += COMMENT + "Saving " + Source->Name + " into " + this->Name + NL;
        output += MOV + GetAddress() + FROM + DWORD + Source->InitVariable() + NL;
        this->Reg = Source->Reg;
        Source->Reg->Link(this);
		return this->Reg->Name;
    }
    else if (Source->is(Returning))
    {
        if ((Source->Parameters.size() > 0) && Source->cleaned == false)
        {
			output += COMMENT + "Clearing the parameters" + NL;
            output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
			Source->cleaned = true;
        }
		output += COMMENT + "Giving " + this->Name + " the return value" + NL;
        output += MOV + this->GetAddress() + FROM + Source->Reg->Name + NL + NL;
    }
    
    return "";
}

string Token::SUM(Token *Source, Token *Dest)
{
    PTRING(Source);
    if (Source->is(Returning))
    {
		if ((Source->Parameters.size() > 0) && Source->cleaned == false)
		{
			output += COMMENT + "Clearing the parameters" + NL;
			output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
			Source->cleaned = true;
		}
		EAX->Link(Source);
		Source->Reg = EAX;
		if (RegisterTurn == 0)
		{
			RegisterTurn++;
		}
    }
	if (this->is(Returning))
	{
		if ((this->Parameters.size() > 0) && (this->cleaned == false))
		{
			output += COMMENT + "Clearing the parameters" + NL;
			output += ADD + ESP->Name + FROM + to_string(this->Parameters.size() * 4) + NL;
			this->cleaned = true;
		}
		//if the both of em are returning functions
		if (Source->is(Returning))
		{
		}
		else
		{
			EAX->Link(this);
			this->Reg = EAX;
			if (RegisterTurn == 0)
			{
				RegisterTurn++;
			}
		}
	}
    if (Source->is(Number))
    {
		output += COMMENT + "Direct addition" + NL;
		if (Dest->Name == this->Name)
		{
			output += ADD + this->GetAddress() + FROM + DWORD + Source->Name + NL;
			this->Reg = NUL;
		}
		else
		{
			output += ADD + this->InitVariable() + FROM + DWORD + Source->Name + NL;
		}
    }
	else if (this->is(Number))
	{
		output += COMMENT + "Direct addition" + NL;
		if (Dest->Name == Source->Name)
		{
			output += ADD + Dest->GetAddress() + FROM + DWORD + this->Name + NL;
			this->Reg = NUL;
		}
		else
		{
			output += ADD + Source->InitVariable() + FROM + DWORD + this->Name + NL;
			this->Reg = Source->Reg;
		}
	}
	else if (Source->is(Array))
	{
		//mov eax, [ebp + 8]
		//lea esi, [eax + 0 * 4]
		output += COMMENT + "From " + Source->Name + " added address by value of " + Source->Offsetter->Name + NL;
		if (Source->is(Address_Operator))
		{
			output += MOV + ESI->Name + FROM + Source->GetAddress() + NL;
		}
		else
		{
			output += LEA + ESI->Name + FROM + Source->GetAddress() + NL;
		}
		ESI->Link(Source);
		Source->Reg = ESI;
		if (this->is(Array))
		{
			output += COMMENT + "From " + this->Name + " added address by value of " + this->Offsetter->Name + NL;
			output += LEA + EDI->Name + FROM + this->GetAddress() + NL;
			EDI->Link(this);
			this->Reg = EDI;
			//if (this->repz != nullptr)
			//{
				if (this->tmp == nullptr)
				{
					this->tmp = new Token(this->output, this->Input);
					this->tmp->Flags |= Variable;
				}
				output += MOV + this->tmp->getReg()->Name + FROM + FRAME(EDI->Name) + NL;
				output += ADD + this->tmp->Reg->Name + FROM + FRAME(ESI->Name) + NL;
			//}
		}
		else
		{
			//add eax, [(ebp - 4) + (ebp - 8) * 4]
			output += ADD + this->getReg()->Name + FROM + FRAME(ESI->Name) + NL;
		}
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
	else if (this->is(Ptr) || this->is(Variable))
	{
		output += COMMENT + "Adding " + this->Name + " into " + this->Name + NL;
		if (this->Reg == nullptr || this->Reg->Name == "null")
		{
			output += COMMENT + "Just directly get address" + NL;
			output += ADD + Source->InitVariable() + FROM + this->GetAddress() + NL;
			this->Reg = Source->Reg;
		}
		else
		{
			output += COMMENT + "There is already register for it, use it" + NL;
			output += ADD + Source->InitVariable() + FROM + this->Reg->Name + NL;
		}
	}
	else if (Source->is(Returning) && this->is(Returning))
	{
		output += ADD + this->Reg->Name + FROM + Source->Reg->Name + NL;
	}
    return this->Reg->Name;
}

string Token::SUBSTRACT(Token *Source, Token *Dest)
{
    PTRING(Source);
	if (Source->is(Returning))
	{
		if ((Source->Parameters.size() > 0) && Source->cleaned == false)
		{
			output += COMMENT + "Clearing the parameters" + NL;
			output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
			Source->cleaned = true;
		}
		EAX->Link(Source);
		Source->Reg = EAX;
		if (RegisterTurn == 0)
		{
			RegisterTurn++;
		}
	}
	if (this->is(Returning))
	{
		if ((this->Parameters.size() > 0) && this->cleaned == false)
		{
			output += COMMENT + "Clearing the parameters" + NL;
			output += ADD + ESP->Name + FROM + to_string(this->Parameters.size() * 4) + NL;
			this->cleaned = true;
		}
		//if the both of em are returning functions
		if (Source->is(Returning))
		{
		}
		else
		{
			EAX->Link(this);
			this->Reg = EAX;
			if (RegisterTurn == 0)
			{
				RegisterTurn++;
			}
		}
	}
    if (Source->is(Number))
    {
		output += COMMENT + "Direct substraction" + NL;
		if (Dest->Name == this->Name)
		{
			output += SUB + this->GetAddress() + FROM + DWORD + Source->Name + NL;
			this->Reg = NUL;
		}
		else
		{
			output += SUB + this->InitVariable() + FROM + DWORD + Source->Name + NL;
		}
    }
	else if (Source->is(Array))
	{
		//mov eax, [ebp + 8]
		//lea esi, [eax + 0 * 4]
		output += COMMENT + "From " + Source->Name + " added address by value of " + Source->Offsetter->Name + NL;
		if (Source->is(Address_Operator))
		{
			output += MOV + ESI->Name + FROM + Source->GetAddress() + NL;
		}
		else
		{
			output += LEA + ESI->Name + FROM + Source->GetAddress() + NL;
		}
		ESI->Link(Source);
		Source->Reg = ESI;
		if (this->is(Array))
		{
			output += COMMENT + "From " + this->Name + " added address by value of " + this->Offsetter->Name + NL;
			output += LEA + EDI->Name + FROM + this->GetAddress() + NL;
			EDI->Link(this);
			this->Reg = EDI;/*if (this->repz != nullptr)
			{
			}*/
			//else
			//{
			if (this->tmp == nullptr)
			{
				this->tmp = new Token(this->output, this->Input);
				this->tmp->Flags |= Variable;
			}
			output += MOV + this->tmp->getReg()->Name + FROM + FRAME(EDI->Name) + NL;
			output += SUB + this->tmp->Reg->Name + FROM + FRAME(ESI->Name) + NL;
			//}
		}
		else
		{
			//add eax, [(ebp - 4) + (ebp - 8) * 4]
			output += SUB + this->getReg()->Name + FROM + FRAME(ESI->Name) + NL;
		}
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
	else if (this->is(Ptr) || this->is(Variable))
	{
		output += COMMENT + "Adding " + this->Name + " into " + this->Name + NL;
		if (this->Reg == nullptr || this->Reg->Name == "null")
		{
			output += COMMENT + "Just directly get address" + NL;
			output += SUB + Source->InitVariable() + FROM + this->GetAddress() + NL;
			this->Reg = Source->Reg;
		}
		else
		{
			output += COMMENT + "There is already register for it, use it" + NL;
			output += SUB + Source->InitVariable() + FROM + this->Reg->Name + NL;
		}
	}
	else if (Source->is(Returning) && this->is(Returning))
	{
		output += SUB + this->Reg->Name + FROM + Source->Reg->Name + NL;
	}
    return this->Reg->Name;
}

string Token::MULTIPLY(Token *Source)
{
    PTRING(Source);
	if (Source->is(Returning))
	{
		if ((Source->Parameters.size() > 0) && Source->cleaned == false)
		{
			output += COMMENT + "Clearing the parameters" + NL;
			output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
			Source->cleaned = true;
		}
		EAX->Link(Source);
	}
	if (this->is(Returning))
	{
		if ((this->Parameters.size() > 0) && this->cleaned == false)
		{
			output += COMMENT + "Clearing the parameters" + NL;
			output += ADD + ESP->Name + FROM + to_string(this->Parameters.size() * 4) + NL;
			this->cleaned = true;
		}
		//if the both of em are returning functions
		if (Source->is(Returning))
		{
		}
		else
		{
			EAX->Link(this);
			this->Reg = EAX;
			if (RegisterTurn == 0)
			{
				RegisterTurn++;
			}
		}
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
		//mov eax, [ebp + 8]
		//lea esi, [eax + 0 * 4]
		output += COMMENT + "From " + Source->Name + " added address by value of " + Source->Offsetter->Name + NL;
		if (Source->is(Address_Operator))
		{
			output += MOV + ESI->Name + FROM + Source->GetAddress() + NL;
		}
		else
		{
			output += LEA + ESI->Name + FROM + Source->GetAddress() + NL;
		}
		ESI->Link(Source);
		if (this->is(Array))
		{
			output += COMMENT + "From " + this->Name + " added address by value of " + this->Offsetter->Name + NL;
			output += LEA + EDI->Name + FROM + this->GetAddress() + NL;
			EDI->Link(this);/*if (this->repz != nullptr)
			{
			}*/
			//else
			//{
			if (this->tmp == nullptr)
			{
				this->tmp = new Token(this->output, this->Input);
				this->tmp->Flags |= Variable;
			}
			output += MOV + this->tmp->getReg()->Name + FROM + FRAME(EDI->Name) + NL;
			output += IMUL + this->tmp->Reg->Name + FROM + FRAME(ESI->Name) + NL;
			//}
		}
		else
		{
			//add eax, [(ebp - 4) + (ebp - 8) * 4]
			output += IMUL + this->getReg()->Name + FROM + FRAME(ESI->Name) + NL;
		}
	}
    else if (Source->is(Ptr) || Source->is(Variable))
    {
		output += COMMENT + "Multiplying " + Source->Name + " into " + this->Name + NL;
		if (Source->Name == this->Name)
		{
			output += IMUL + this->getReg()->Name + FROM + Source->InitVariable() + NL;
		}
        else if (Source->Reg == nullptr || Source->Reg->Name == "null")
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
	else if (this->is(Ptr) || this->is(Variable))
	{
		output += COMMENT + "Adding " + this->Name + " into " + this->Name + NL;
		if (this->Reg == nullptr || this->Reg->Name == "null")
		{
			output += COMMENT + "Just directly get address" + NL;
			output += IMUL + Source->InitVariable() + FROM + this->GetAddress() + NL;
			this->Reg = Source->Reg;
		}
		else
		{
			output += COMMENT + "There is already register for it, use it" + NL;
			output += IMUL + Source->InitVariable() + FROM + this->Reg->Name + NL;
		}
	}
	else if (Source->is(Returning) && this->is(Returning))
	{
		output += IMUL + this->Reg->Name + FROM + Source->Reg->Name + NL;
	}
    return this->Reg->Name;
}

string Token::DIVIDE(Token *Source)
{
    PTRING(Source);
	if (Source->is(Returning))
	{
		if ((Source->Parameters.size() > 0) && Source->cleaned == false)
		{
			output += COMMENT + "Clearing the parameters" + NL;
			output += ADD + ESP->Name + FROM + to_string(Source->Parameters.size() * 4) + NL;
			Source->cleaned = true;
		}
		output += CDQ + NL;
		output += IDIV + this->GetAddress() + NL;
		EAX->Link(this);
	}
	if (this->is(Returning))
	{
		if ((this->Parameters.size() > 0) && this->cleaned == false)
		{
			output += COMMENT + "Clearing the parameters" + NL;
			output += ADD + ESP->Name + FROM + to_string(this->Parameters.size() * 4) + NL;
			this->cleaned = true;
		}
		output += CDQ + NL;
		//if the both of em are returning functions
		if (Source->is(Returning))
		{
			output += IDIV + this->Reg->Name + NL;
		}
		else
		{
			EAX->Link(this);
			this->Reg = EAX;
			if (RegisterTurn == 0)
			{
				RegisterTurn++;
			}
		}
	}
    if (Source->is(Number))
    {
        //cdq
		output += COMMENT + "Direct division" + NL;
        output += XCHG(this->InitVariable(), EAX->Name);
		output += CDQ + NL;
        output += IDIV + Source->Name + NL;
        EAX->Link(this);
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
		}
        //cdq
		output += COMMENT + "From " + Source->Name + " added address by value of " + Source->Offsetter->Name + NL;
        output += XCHG(this->Reg->Name, EAX->Name);
		output += COMMENT + "Dividing the value from " + Source->Name + " offsetted by " + this->Name + NL;
		output += CDQ + NL;
        output += IDIV + DWORD + FRAME(ESI->Name) + NL;
        EAX->Link(this);
    }
    else if (Source->is(Ptr) || Source->is(Variable))
    {
		output += COMMENT + "Dividing " + Source->Name + " into " + this->Name + NL;
		if (this->Reg->Name != "eax")
		{
			output += XCHG(this->InitVariable(), EAX->Name);
		}
        if (Source->Reg == nullptr || Source->Reg->Name == "null")
        {
			output += COMMENT + "Just directly get address" + NL;
			output += CDQ + NL;
            output += IDIV + string(DWORD) + Source->GetAddress() + NL;
        }
        else
        {
			output += COMMENT + "There is already register for it, use it" + NL;
			output += CDQ + NL;
            output += IDIV + Source->GetAddress() + NL;
        }
        EAX->Link(this);
    }
	else if (Source->is(Returning) && this->is(Returning))
	{
		output += IDIV + this->Reg->Name + FROM + Source->Reg->Name + NL;
	}
    return this->Reg->Name;
}

string Token::COMPARE(Token *Source)
{
	output += COMMENT + "Comparing " + this->Name + " and " + Source->Name + NL;
	if (Source->is(Number))
	{
		output += COMMENT + "Just directly get name of the number" + NL;
		if (Source->Reg == nullptr)
		{
			output += MOV + Source->getReg()->Name + FROM + Source->Name + NL;
		}
		output += CMP + this->GetAddress() + FROM + Source->Reg->Name + NL;
	}
    else if (Source->Reg == nullptr || Source->Reg->Name == "null")
    {
		output += COMMENT + "Just directly get address of " + Source->Name + NL;
		if ((this->Reg == nullptr) || (this->Reg->Name == "null"))
		{
			output += MOV + getReg()->Name + FROM + this->GetAddress() + NL;
		}
        output += CMP + this->Reg->Name + FROM + Source->GetAddress() + NL;
    }
    else
    {
		output += COMMENT + "There is already register for " + Source->Name + " use it" + NL;
		if ((this->Reg == nullptr) || (this->Reg->Name == "null"))
		{
			output += CMP + this->GetAddress() + FROM + Source->Reg->Name + NL + NL;
		}
		else
		{
			output += CMP + this->Reg->Name + FROM + Source->Reg->Name + NL + NL;
		}
    }
	return "";
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
				if (this->Passing_String)
				{
					if ((this->Reg == nullptr) || (this->Reg->Name == "null"))
					{
						output += MOV + Reg->Name + FROM + this->GetAddress() + NL;
					}
				}
				else
				{
					output += LEA + Reg->Name + FROM + this->GetAddress() + NL;
				}
				skip_ptr_check = false;
				return Reg->Name;
			}
			else
			{
				//mov eax, [ebp + 8]
				//lea esi, [eax + 0 * 4]
				if (this->Reg == nullptr)
				{
					getReg();
					output += MOV + Reg->Name + FROM + FRAME(this->getFullName()) + NL;
				}
			}
		}
        if (this->is(Array) && this->Offsetter->is(Number))
        {
			//[(ebp - 8) + 1 * 4]
			output += COMMENT + "Adding the offset of " + this->Name + " by " + this->Offsetter->Name + NL;
			if ((this->Reg == nullptr) || (this->Reg->Name == "null"))
			{
				this->InitVariable();
			}
			if (this->is(Ptr) && (Outside_Of_Parameters == false))
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
			if ((this->Reg == nullptr) || (this->Reg->Name == "null"))
			{
				this->InitVariable();
			}
			if (this->is(Ptr) && (Outside_Of_Parameters == false))
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
	if ((Base != nullptr) && (Base->Name != Current->Name))
	{
		Base->Reg = NUL;
	}
	Base = Current;/*
	if (Requester->ParentCondition != nullptr)
	{
		Apply(Requester, Requester->ParentCondition->Childs);
		Apply(Requester, Requester->ParentCondition->Parameters);
		if ((Requester->ParentCondition->ParentCondition == nullptr) && (Requester->ParentCondition->ParentFunc != nullptr))
		{
			Apply(Requester, Requester->ParentCondition->ParentFunc->Parameters);
			Apply(Requester, Requester->ParentCondition->ParentFunc->Childs);
		}
	}
	else if (Requester->ParentFunc != nullptr)
	{
		Apply(Requester, Requester->ParentFunc->Parameters);
		Apply(Requester, Requester->ParentFunc->Childs);
	}
	else if (Requester->ParentType != nullptr)
	{
		Apply(Requester, Requester->ParentType->Childs);
	}
	else
	{
		Apply(Requester, *Requester->Input);
	}*/
}

void Register::Apply(Token* Requester, vector<Token*> &T)
{
	for (auto* t : T)
	{
		if (t->Childs.size() > 0)
		{
			Apply(Requester, t->Childs);
		}
		if (t->Parameters.size() > 0)
		{
			Apply(Requester, t->Parameters);
		}
		if (t->Offsetter != nullptr)
		{
			if ((t->Offsetter->Name == Requester->Name))
			{
				t->Offsetter->Reg = this;
			}
		}
		if (t->Name == Requester->Name)
		{
			t->Reg = this;
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
