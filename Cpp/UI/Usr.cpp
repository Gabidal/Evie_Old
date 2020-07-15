#include "../../H/UI/Usr.h"
#include <cstring>
#include <iostream>
#include <optional>
#include <algorithm>

//main -in ~/test.g -out ~/test.asm -os win32 -arch x86 -mode 32
void Usr::Create_Argument_Stats()
{
	for (int i = 1; i < Argument_Amount; i++) {
		Find_Destination_File(i);
		Find_Source_File(i);
		Find_OS(i);
		Find_Architecture(i);
		Find_Bits_Mode(i);
		Find_Debug_Type(i);
		Find_Format(i);
		Find_Lib(i);
	}
}

void Usr::Find_Source_File(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-in") == 0)
	{
		Info.Source_File = Input[i + 1];
		i++;
	}
}

void Usr::Find_Destination_File(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-out") == 0)
	{
		Info.Destination_File = Input[i + 1];
		i++;
	}
}

void Usr::Find_OS(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-os") == 0)
	{
		Info.OS = Input[i + 1];
		i++;
	}
}

void Usr::Find_Architecture(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-arch") == 0)
	{
		Info.Architecture = Input[i + 1];
		i++;
	}
}

void Usr::Find_Bits_Mode(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-mode") == 0)
	{
		Info.Bits_Mode = Input[i + 1];
		i++;
	}
}

void Usr::Find_Format(int &i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-f") == 0)
	{
		string tmp = string(Input[i + 1]);
		Info.Format = tmp.c_str();
		i++;
	}
}

void Usr::Find_Lib(int& i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-lib") == 0)
	{
		string tmp = string(Input[i + 1]);
		Info.Libs.push_back(tmp.c_str());
		i++;
	}
}

void Usr::Find_Debug_Type(int& i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-debug") == 0)
	{
		string tmp = string(Input[i + 1]);
		Info.Debug = tmp;
		i++;
	}
}

bool is_number(const string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

optional<int> If_Int(string s) {
	if (is_number(s))
	{
		return optional<int> {
			atoi(s.c_str())
		};
	}
	return nullopt;
}

void output::Update_Mapped_Values()
{
	/*
	string Source_File;
	string Destination_File;
	string OS = "win32";
	string Architecture = "x86";
	vector<string> Libs;
	vector<string> Source_Files;
	string Format = "exe";
	string Bits_Mode = "4";
	string Disable = "";
	string Debug = "";
	*/
	Mapped_Values.insert({ "SOURCE_FILE", Source_File });
	Mapped_Values.insert({ "DESTINATION_FILE", Destination_File });
	Mapped_Values.insert({ "OS", OS });
	Mapped_Values.insert({ "ARCHTITECTURE", Architecture });
	//Mapped_Values.insert({ "SOURCE_FILE", Libs });
	//Mapped_Values.insert({ "SOURCE_FILE", Source_Files });
	Mapped_Values.insert({ "FORMAT", Format });
	Mapped_Values.insert({ "BITS_MODE", Bits_Mode });
	Mapped_Values.insert({ "DISABLE", Disable });
	Mapped_Values.insert({ "DEBUG", Debug });
}
