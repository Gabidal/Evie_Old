#include "..\..\H\UI\Usr.h"

//main -in ~/test.g -out ~/test.asm -os win32 -arch x86 -mode 32
void Usr::Create_Argument_Stats()
{
	for (int i = 1; i < Argument_Amount; i++) {
		Find_Destination_File(i);
		Find_Source_File(i);
		Find_OS(i);
		Find_Architecture(i);
		Find_Bits_Mode(i);
	}
}

void Usr::Find_Source_File(int i)
{
	if (strcmp(Input[i], "-in") == 0)
	{
		Info.Source_File = Input[i + 1];
	}
}

void Usr::Find_Destination_File(int i)
{
	if (strcmp(Input[i], "-out") == 0)
	{
		Info.Destination_File = Input[i + 1];
	}
}

void Usr::Find_OS(int i)
{
	if (strcmp(Input[i], "-os") == 0)
	{
		Info.OS = Input[i + 1];
	}
}

void Usr::Find_Architecture(int i)
{
	if (strcmp(Input[i], "-arch") == 0)
	{
		Info.Architecture = Input[i + 1];
	}
}

void Usr::Find_Bits_Mode(int i)
{
	if (strcmp(Input[i], "-mode") == 0)
	{
		string tmp = string(Input[i + 1]);
		Info.Bits_Mode = atoi(tmp.c_str());
	}
}

void Usr::Find_Obj_Type(int i)
{
	if (strcmp(Input[i], "-lib") == 0)
	{
		string tmp = string(Input[i + 1]);
		Info.Obj_Type = atoi(tmp.c_str());
	}
}
