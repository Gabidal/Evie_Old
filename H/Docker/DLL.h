#ifndef _DLL_H_
#define _DLL_H_

#include <vector>
#include <string>
#include "Docker.h"

using namespace std;

namespace DLL {
	class Table {
	public:
		char Table_Name[4];
		char Table_Size[4];
	};

	class Export_Directory_Table {
	public:
		char Export_Flags[4];
		char Time_Date_Stamp[4];
		char Version[4];
		char Name_RVA[4];
		char Ordinal_Base[4];
		char Address_Table_Entries[4];
		char Number_Of_Name_Pointers[4];
		char Export_Address_Table_RVA[4];
		char Name_Pointer_RVA[4];
		char Ordinal_Table_RVA[4];
	};

	class Header {
	public:
		char Number_OF_Sections[2];
		char Date_Time[4];
		char Pointter_To_Symbol_Table[4];
		char Number_Of_Symbols[4];
		char Size_Of_Optional_Header[2];
		char Characteristics[2];
		char Magic[2];
		char Linker_Version[2];
		char Size_Of_Code[4];
		char Size_Of_Initialized_Data[4];
		char Size_Of_Uninitialized_Data[4];
		char Address_Of_Entry_Point[4];
		char Base_Of_Code[4];
		char Base_Of_Data[4];
		char Image_Base[4];
		char Section_Alignment[4];
		char File_Alignment[4];
		char Major_Operating_System_Version[4];
		char Image_Version[4];
		char Subsystem_Version[4];
		char Win32_Version_Value[4];
		char Size_Of_Image[4];
		char Size_Of_Headers[4];
		char Check_Sum[4];
		char Subsystem[2];
		char Dll_Characteristics[2];
		char Size_Of_Stack_Reserve[4];
		char Size_Of_Stack_Commit[4];
		char Size_Of_Heap_Reserve[4];
		char Size_Of_Heap_Commit[4];
		char Loader_Flags[4];
		char Number_Of_Rva_And_Sizes[3];
	};

	vector<Table> Gather_All_Tables(vector<char> buffer, Header h);

	vector<string> Gather_All_Export_Names(Header h, vector<char> buffer, Table t);

	void DLL_Analyser(vector<string>& Output);
}

#endif