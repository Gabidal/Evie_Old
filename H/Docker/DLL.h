#ifndef _DLL_H_
#define _DLL_H_

#include <vector>
#include <string>
#include "Docker.h"
#include "OBJ.h"

using namespace std;

namespace DLL {
	vector<PE::Section> Gather_All_Tables(vector<unsigned char> buffer, PE::Header_64 h);

	vector<string> Gather_All_Export_Names(PE::Header_64 h, vector<unsigned char> buffer, PE::Section t);

	void DLL_Analyser(vector<string>& Output);

	void Enlarge_PE_Header(PE::PE_OBJ* obj);

	void Add_Base_Relocation_table(PE::PE_OBJ* obj, int Expected_Section_Count);

	void Write_Base_Relocation_Table(PE::PE_OBJ* obj, vector<unsigned char>& buffer);

	vector<unsigned char> Write_DLL(PE::PE_OBJ* obj);

	unsigned int Get_Bull_Shit_Header_Size(vector<unsigned char> &buffer);

	PE::Section Get_Export_Table(vector<unsigned char> &buffer);

	PE::Header_64 Read_Headers(vector<unsigned char> &buffer);
}

#endif