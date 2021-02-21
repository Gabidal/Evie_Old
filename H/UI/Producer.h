#ifndef _PRODUCER_H_
#define _PRODUCER_H_
#include "Usr.h"
#include <sstream>
#include <iostream>
#include <vector>

extern Usr* sys;

class Producer
{
public:
	Producer()
	{
		Size = to_string(atoi(sys->Info.Bits_Mode.c_str()) * 8);
		Output_File = sys->Info.Destination_File;
		Type = sys->Info.Format;
		arch = sys->Info.Architecture;
		OS = sys->Info.OS;
		HOST_OS = sys->Info.HOST_OS;
		Debug = sys->Info.Debug;
		Libs = sys->Info.Libs;
		Source_Files = sys->Info.Source_Files;
	}

	~Producer(){}
	void Assemble_Command();

private:
	void Assembly_Other_Source_Files();
	string Get_Linker_Type();
	string Get_Assembler();
	string Get_Debug();
	string Get_Type();
	string Get_File_Name();
	string Get_Assembly_Dest_Marker();
	string Get_Linker_Debug_Type();
	string Get_Linker_aarch();
	string Get_Assembler_Output();
	string Get_Linker_Input();
	string Get_Linker_Output();
	string Get_Added_Libs();
	string Get_Entry();
	string Get_System_Paths();
	string Link();
	string Get_Template();
	bool Find(vector<string> in, string f);
	string Get_All(vector<string> in);
	string Update_Dir(string File_Name);
	string Change_Dir();
	string Size;
	string Output_File;
	string Type;
	string arch;
	string OS;
	string HOST_OS;
	string Debug;
	vector<string> Libs;
	vector<string> Source_Files;;
};


#endif