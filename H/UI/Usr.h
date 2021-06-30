#ifndef _USR_H_
#define _USR_H_
#include <vector>
#include <string>
#include <map>
#include <optional>
#include <algorithm>
#include <iostream>
using namespace std;

class output{
public:
	string Source_File;
	string Destination_File;
	string OS;
	string HOST_OS;
	string Architecture = "x86";
	vector<string> Libs;
	string Repo_Dir = "";
	vector<string> Source_Files;
	string Format = "exe";
	string Bits_Mode = "0";
	string Disable = "";
	bool Debug = false;
	string VT_API = "";
	int Reference_Count_Size = 0;

	string Evie_Location = "";
	string Assembler_Location = "";
	string Linker_Location = "";

	output() {
		#if _WIN32
			OS = "win";
		#else
			OS = "unix";
		#endif
		#if _WIN32
			HOST_OS = "win";
		#else
			HOST_OS = "unix";
		#endif
	}
	void Fill_Empty_Arguments();
};

class Usr
{
public:
	output Info;
	Usr(const char** in, int count)
	{
		Input = in;
		Argument_Amount = count;

		/*for (int i = 0; i < Argument_Amount; i++) {
			transform((char*)Input[i], (char*)Input[i] + strlen((char*)Input[i]), (char*)Input[i], tolower);
			replace((char*)Input[i], (char*)Input[i] + strlen((char*)Input[i]), '-', '_');
		}*/

		Create_Argument_Stats();
		Info.Fill_Empty_Arguments();
	}

	~Usr(){}

private:
	const char** Input;
	int Argument_Amount;
	void Create_Argument_Stats();
	void Find_Source_File(int &i);
	void Find_Destination_File(int &i);
	void Find_OS(int& i);
	void Find_HOST_OS(int& i);
	void Find_Architecture(int &i);
	void Find_Bits_Mode(int &i);
	void Find_Format(int &i);
	void Find_Lib(int& i);
	void Find_Repo_Dir(int& i);
	void Find_Debug_Type(int& i);
	void Find_VT_API(int& i);
	void Find_Reference_Count(int& i);
	void Find_Evie_Executable_Position();
};


#endif
