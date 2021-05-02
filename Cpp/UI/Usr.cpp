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
		Find_HOST_OS(i);
		Find_Architecture(i);
		Find_Bits_Mode(i);
		Find_Debug_Type(i);
		Find_Format(i);
		Find_Lib(i);
		Find_VT_API(i);
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

void Usr::Find_HOST_OS(int& i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-host") == 0)
	{
		Info.HOST_OS = Input[i + 1];
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
		Info.Bits_Mode = to_string(atoi(Input[i + 1]) / 8);
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

void Usr::Find_Repo_Dir(int& i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-repo_dir") == 0)
	{
		string tmp = string(Input[i + 1]);
		Info.Repo_Dir = tmp;
		i++;
	}
}

void Usr::Find_Debug_Type(int& i)
{
	if ((i <= Argument_Amount) && strcmp(Input[i], "-d") == 0)
	{
		Info.Debug = true;
	}
}

void Usr::Find_VT_API(int& i)
{
	string a = string(Input[i]);
	if ((i <= Argument_Amount) && strcmp(Input[i], "-vt") == 0)
	{
		string tmp = string(Input[i + 1]);
		Info.VT_API = tmp;
		i++;
	}
}

void output::Fill_Empty_Arguments()
{
	//Evie.exe -in IO/test.e

	//first check if bit mode is set or not
	if (Bits_Mode == "0")
		Bits_Mode = to_string(sizeof(void*));

	//we can always use the source files name to output files name and add the .asm at the end
	if (Destination_File == "")
		Destination_File = (string)Source_File + ".asm";

	if (Repo_Dir == "") {
		char* Env = getenv("Repo_Dir");
		if (Env != nullptr)
			Repo_Dir = Env;
		else
			Repo_Dir = "Remote";
	}

	replace(Repo_Dir.begin(), Repo_Dir.end(), '\\', '/');
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
