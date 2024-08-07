#ifndef _USR_H_
#define _USR_H_
#include <vector>
#include <string>
#include <map>
#include <optional>
#include <algorithm>
#include <iostream>

#include "Document_Request_Type.h"
using namespace std;

class System{
public:
	string Source_File;
	string Destination_File;
	string OS;						// Destination environment OS
	string HOST_OS;					// Compiling environment OS
	string Architecture = "x86";
	vector<string> Pre_Compiled_Sources;			// All in source imported Pre-Compiled-Sources are Liquefied
	vector<string> Pre_Compiled_Linkable_Sources;	// All Mentions of Import functions whiteout their respective importing PCS files get thrown here, for normal linking.
	vector<string> Inlined_External_Symbols;		// This is for all the symbols which are brought from the PCS files from syntax: "use" keyword
	string Repo_Dir = "";
	vector<string> Source_Files;
	string Format = "exe";
	string Bytes_Mode = "0";
	string Disable = "";
	bool Debug = false;
	string VT_API = "";
	int Reference_Count_Size = -1;
	bool Is_Service = false;
	bool Use_Scraper = true;		// Automatically fetches dll/lib and links them if they have the necessary function implementations.

	string Start_Function_Name = "main";

	string Evie_Location = "";
	string Assembler_Location = "";
	string Linker_Location = "";

	class Node* Starting_Address = nullptr;

	// Flags
	bool Allow_Inconsistencies = true;

	System() {
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
	System Info;
	Document_Request_Type Service_Info = Document_Request_Type::NONE;
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
	void Find_Service(int& i);
	void Find_Start_Function_Name(int& i);
	void Find_Allow_Inconsistencies(int& i);
	void Find_Use_Scraper(int& i);

	void Single_Argument_Use();
};


#endif
