#include "../../H/Back/Back.h"
#include "../../H/Selector/Selector.h"
extern Selector* S;
#define _SYSTEM_BIT_TYPE 4


string Back::Get_Initial_Operator()
{
	return S->Get_ID(Input->ID);
}

string Back::Initialize(Token* t)
{
	if (S->Get_Belonging_Reg(t->Name) != nullptr)
		//this can happen also if the pointter has been already provided by a register.
		return S->Get_Belonging_Reg(t->Name)->Name;
	if (Storing_Into_Mem)
	{
		//get the memory location of *t
		return Get_Mem_Address(t);
	}
	if (t->is(_Number_))
	{
		return (S->Get_ID(to_string(t->Size)) + t->Name);
	}
	//load the token from memory into a reg.
	if (t->is(_Array_))
	{
		cout << "Error:: Too complex pointter has intruded the BackEnd" << endl;
		return " Error::" + t->Name + " Offsetted by " + t->Offsetter->Name + NL;
	}
	if (t->is(_Function_))
	{
		cout << "Error:: Function callation is not supported in BackEnd" << endl;
		return " Error::" + t->Name + NL;
	}
	Register* New_Reg = S->Get_Reg(t->Size);
	New_Reg->Base = t;
	//mov reg, [t]
	Output += S->Get_ID("=") + New_Reg->Name + FROM + Get_Mem_Address(t) + NL;
	return New_Reg->Name;
}

string Back::Get_Size_Specification()
{
	return string();
}

void Back::Factory()
{
	
}

string Back::Get_Static_Agent(Token* t)
{
	if (t->is(_Number_))
	{
		return t->Name;
	}
	else if (t->is(_Array_))
	{
		return "return has not been implemented!";
	}
	else
	{
		Get_Mem_Address(t);
	}
	return string();
}

string Back::Get_Agent(bool Storing, Token* Dest, Token* Source)
{
	//first find if this token has a register to it.
	if (S->Get_Belonging_Reg(Dest->Name) != nullptr)
	{
		return S->Get_Belonging_Reg(Dest->Name)->Name;
	}
	//if it is number.
	if (Dest->is(_Number_))
	{
		return Dest->Name;
	}
	//if the Source doesnt have a reg and this is a storing opcode
	//then move the source into a reg and then move the reg into the address.
	if ((Source != nullptr) && (S->Get_Belonging_Reg(Source->Name) == nullptr) && (Storing))
	{
		S->Get_Reg(Source->Size)->Base = Source;
		string returning_Reg = S->Get_Belonging_Reg(Source->Name)->Name;
		Output += S->Get_ID("=") + returning_Reg + FROM  + S->Get_ID(to_string(Source->Size)) + Get_Static_Agent(Source) + NL;
		//return returning_Reg;
	}
	//then get it from mem.
	if (Storing)
	{
		return Get_Mem_Address(Dest);
	}
	else
	{
		return S->Get_Reg(Dest->Size)->Name;
	}
}

Token* Back::Give_Context(int i, vector<Token*> in)
{
	if ((i+1) > (in.size() - 1))
	{
		return nullptr;
	}
	else
	{
		return in.at(i + 1);
	}
}

void Back::Make(IR* ir, bool Storing)
{
	//this needs a secondary output because if need for more complex instructions they have 
	//then the reserved as Output and then it will putted into the secindary output the hendle register it gives us.
	string Secondary_Output = "";
	Secondary_Output += S->Get_ID(ir->PreFix) + S->Get_ID(ir->ID);
	for (int i = 0; i < ir->Parameters.size(); i++)
	{
		if (i > 0)
		{
			Secondary_Output += FROM + string(" ");
			Secondary_Output += S->Get_ID(to_string(ir->Parameters.at(i)->Size));
		}
		Secondary_Output += Get_Agent(Storing, ir->Parameters.at(i), Give_Context(i, ir->Parameters));
	}
	Output += Secondary_Output;
}

string Back::Get_Name(Token* t)
{
	if (t->ID > 0)
	{
		return t->Name + to_string(t->ID);
	}
	else
	{
		return t->Name;
	}
}

string Back::Get_Mem_Address(Token* t)
{
	if (t->is(_External_))
	{
		return "[" + Get_Name(t) + "]";
	}
	else
	{
		return "[" + S->Get_Right_Reg(Task_For_Type_Address_Basing, _SYSTEM_BIT_TYPE) + t->Get_Additive_Operator() + to_string(t->StackOffset) + "]";
	}
}

string Back::Get_Size_Translator(int Size)
{
	return S->Get_ID(to_string(Size));
}
