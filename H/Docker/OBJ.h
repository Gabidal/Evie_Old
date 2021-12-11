#ifndef _OBJ_H_
#define _OBJ_H_
#include <vector>
#include <string>

#include "Docker.h"

using namespace std;

namespace OBJ {
	class Header {
	public:
		char Number_OF_Sections[2];
		char Date_Time[4];
		char Pointter_To_Symbol_Table[4];
		char Number_Of_Symbols[4];
		char Size_Of_Optional_Header[2];
		char Characteristics[2];
		/*char Magic[2];
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
		char Number_Of_Rva_And_Sizes[4];*/
	};

	class Section {
	public:
		char Name[8];
		char Virtual_Size[4];
		char Virtual_Address[4];
		char Size_Of_Raw_Data[4];
		char Pointer_To_Raw_Data[4];
		char Pointer_To_Relocations[4];
		char Pointer_To_Line_Numbers[4];
		char Number_Of_Relocations[2];
		char Number_Of_Line_Numbers[2];
		char Characteristics[4];
	};

	class Symbol {
	public:
		union {
			struct {
				char Name_Header[4];
				char Name_Offset[4];
			}Name;
			char Full_Name[8];
		};
		char Value[4];
		char Section_Number[2];
		char Type[2];
		char Storage_Class;
		char Number_Of_Aux_Symbols;
	};

	vector<Section> Gather_All_Sections(vector<char> buffer, int Section_Count);

	vector<string> Get_Symbol_Table_Content(Header h, vector<char> buffer);

	void OBJ_Analyser(vector<string>& Output);
}

#endif