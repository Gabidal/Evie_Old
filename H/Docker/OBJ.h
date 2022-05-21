#ifndef _OBJ_H_
#define _OBJ_H_
#include <vector>
#include <string>

#include "Docker.h"

using namespace std;

class Byte_Map_Section;

namespace OBJ {
	class Header {
	public:
		unsigned short Machine;
		unsigned short Number_OF_Sections;
		unsigned int Date_Time;
		unsigned int Pointer_To_Symbol_Table;
		unsigned int Number_Of_Symbols;
		unsigned short Size_Of_Optional_Header;
		unsigned short Characteristics;
		unsigned short Magic;
		unsigned short Linker_Version;
		unsigned int Size_Of_Code;
		unsigned int Size_Of_Initialized_Data;
		unsigned int Size_Of_Uninitialized_Data;
		unsigned int Address_Of_Entry_Point;
		unsigned int Base_Of_Code;
		unsigned int Base_Of_Data;
		unsigned int Image_Base;
		unsigned int Section_Alignment;
		unsigned int File_Alignment;
		unsigned int Major_Operating_System_Version;
		unsigned int Image_Version;
		unsigned int Subsystem_Version;
		unsigned int Win32_Version_Value;
		unsigned int Size_Of_Image;
		unsigned int Size_Of_Headers;
		unsigned int Check_Sum;
		unsigned short Subsystem;
		unsigned short Dll_Characteristics;
		unsigned int Size_Of_Stack_Reserve;
		unsigned int Size_Of_Stack_Commit;
		unsigned int Size_Of_Heap_Reserve;
		unsigned int Size_Of_Heap_Commit;
		unsigned int Loader_Flags;
		unsigned int Number_Of_Rva_And_Sizes;
	};

	class Section {
	public:
		long long Name;
		int Virtual_Size;
		int Virtual_Address;
		int Size_Of_Raw_Data;
		int Pointer_To_Raw_Data;
		int Pointer_To_Relocations;
		int Pointer_To_Line_Numbers;
		short Number_Of_Relocations;
		short Number_Of_Line_Numbers;
		int Characteristics;
	};

	class Symbol {
	public:
		union {
			struct {
				short Name_Header;
				short Name_Offset;
			}Name;
			long long Full_Name;
		};
		short Value;
		short Section_Number;
		short Type;
		char Storage_Class;
		char Number_Of_Aux_Symbols;
	};

	vector<Section> Gather_All_Sections(vector<char> buffer, int Section_Count);

	vector<string> Get_Symbol_Table_Content(Header h, vector<char> buffer);

	void OBJ_Analyser(vector<string>& Output);

	string Create_Obj(vector<Byte_Map_Section*> Input);

	static constexpr unsigned char IMAGE_FILE_LARGE_ADDRESS_AWARE = 0x0020;
	static constexpr unsigned short MAGIC_PE32_PlUS = 0x20b;
}

#endif