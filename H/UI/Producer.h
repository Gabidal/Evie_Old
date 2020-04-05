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
		aarch = sys->Info.Architecture;
		OS = sys->Info.OS;
		Debug = sys->Info.Debug;
		Libs = sys->Info.Libs;
	}

	~Producer(){}
	void Assemble_Command();

private:
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
	string Get_Added_Libs();
	string Get_Entry();
	string Link();
	string Size;
	string Output_File;
	string Type;
	string aarch;
	string OS;
	string Debug;
	vector<string> Libs;
};


#endif