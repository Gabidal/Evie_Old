#include "..\..\H\UI\Usr.h"

Symbol_Table::Symbol_Table() {
	Member_Pointters = Get_Member_Pointters();
	Member_Data = Get_Member_Data();
}

Symbol_Table* Symbol_Table::Get_Member_Pointter(string key) {
	auto i = Member_Pointters.find(key);
	if (i == Member_Pointters.end())
		return nullptr;
	return i->second;
}

string* Symbol_Table::Get_Member_Data(string key) {
	auto i = Member_Data.find(key);
	if (i == Member_Data.end())
		return nullptr;
	return i->second;
}

map<string, Symbol_Table*> Usr::Get_Member_Pointters()
{
	/*
	output Info;
	*/
	return {
		std::make_pair(string("Info"), &Info)
	};
}

map<string, string*> Usr::Get_Member_Data()
{
	return map<string, string*>();
}

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
		Info.Bits_Mode = Input[i + 1];
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

map<string, Symbol_Table*> output::Get_Member_Pointters() {
	return std::map<string, Symbol_Table*>();
}

map<string, string*> output::Get_Member_Data(){
	/*string Source_File;
	string Destination_File;
	string OS;
	string Architecture;
	string Obj_Type;
	int Bits_Mode = 4;*/
	return {
		std::make_pair(string("Source_File"), &Source_File),
		std::make_pair(string("Destination_File"), &Destination_File),
		std::make_pair(string("OS"), &OS),
		std::make_pair(string("Architecture"), &Architecture),
		std::make_pair(string("Obj_Type"), &Obj_Type),
		std::make_pair(string("Bits_Mode"), &Bits_Mode)
	};
}
