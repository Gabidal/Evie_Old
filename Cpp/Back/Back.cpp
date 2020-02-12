#include "../../H/Back/Back.h"
extern vector<string> Pre_Defined_Tokens;

int Back::Get_Location_Of_Type_Constructor(string type)
{
	int i = 0;
	for (Token* T : Input_Of_Tokens)
	{
		if (T->is(_Constructor_) && T->Name == type)
		{
			return i;
		}
		i++;
	}
}

int Back::Get_Size_Definition(Token* t)
{
	for (Token* i : t->Right_Side_Token->Childs)
	{
		//go a double loop and make a vector for type settings like: Size, etc...
		//loop and find if that type constructor has correlating settings and set em.
		if (i->Name == "Size")
		{
			return atoi(i->Right_Side_Token->Name.c_str());
		}
	}
	return 0;
}

void Back::Factory()
{
	//type var()
	//(
	//  Size 4		#the size of var type is 4Bits.
	//)
	for (string s: Defined_Types)
	{
		Token* New_Defined_Class = new Token();
		//first lets find the defined types
		int i = Get_Location_Of_Type_Constructor(s);
		New_Defined_Class->Size = Get_Size_Definition(Input_Of_Tokens.at(i));
		New_Defined_Class->Name = s;
		New_Defined_Class->Type = s;
	}
}
