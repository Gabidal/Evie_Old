#ifndef _OBJ_H_
#define _OBJ_H_
#include <vector>
#include <string>

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
		unsigned int Operating_System_Version;
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

		unsigned int Export_Table = 0;
		unsigned int Size_Of_Export_Table = 0;
		unsigned int Import_Table = 0;
		unsigned int Size_Of_Import_Table = 0;

		unsigned int Resource_Table = 0;
		unsigned int Size_Of_Resource_Table = 0;
		unsigned int Exception_Table = 0;
		unsigned int Size_Of_Exception_Table = 0;
		unsigned int Certificate_Table = 0;
		unsigned int Size_Of_Certificate_Table = 0;
		unsigned int Base_Relocation_Table = 0;
		unsigned int Size_Of_Base_Relocation_Table = 0;
		unsigned int Debug = 0;
		unsigned int Size_Of_Debug = 0;
		unsigned int Architecture_Data = 0;
		unsigned int Size_Of_Architecture_Data = 0;
		unsigned long long Global_Pointer = 0;
		unsigned int TLS_Table = 0;
		unsigned int Size_Of_TLS_Table = 0;
		unsigned int Load_Config_Table = 0;
		unsigned int Size_Of_Load_Config_Table = 0;
		unsigned int Bound_Import = 0;
		unsigned int Size_Of_Bound_Import= 0;
		unsigned int Import_Address_Table = 0;
		unsigned int Size_Of_Import_Address_Table = 0;
		unsigned int Delay_Import_Descriptor = 0;
		unsigned int Size_Of_Delay_Import_Descriptor = 0;
		unsigned int CLR_Runtime_Header = 0;
		unsigned int Size_Of_CLR_Runtime_Header = 0;
		unsigned long long RESERVED = 0;
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
				char Header;
				char Offset[7];
			}Name;
			long long Full_Name;
		};
		int Value;
		short Section_Number;
		short Type;
		char Storage_Class;
		char Number_Of_Aux_Symbols;
	};


	vector<Section> Gather_All_Sections(vector<char> buffer, int Section_Count);

	vector<string> Get_Symbol_Table_Content(Header h, vector<char> buffer);

	void OBJ_Analyser(vector<string>& Output);

	vector<unsigned char> Create_Obj(vector<Byte_Map_Section*> Input);

	vector<Section> Generate_Section_Table(vector<Byte_Map_Section*> Input);

	vector<Symbol> Generate_Symbol_Table();

	vector<string> Generate_Name_Section_For_Symbol_Table();

	static constexpr unsigned char _IMAGE_FILE_LARGE_ADDRESS_AWARE = 0x0020;
	static constexpr unsigned short _MAGIC_PE32_PlUS = 0x20b;
	static constexpr long _WINDOWS_PE_DLL_BASE_IMAGE = 0x10000000;
	static constexpr long _WINDOWS_PE_EXE_BASE_IMAGE = 0x00400000;

	static constexpr long _FILE_ALIGNMENT = 0x200;

	static constexpr long _ALLOCATOR_BUCKET_COUNT = 100000;
	static constexpr long _BUCKET_SIZE = 700000;

	static constexpr long _IMAGE_SCN_CNT_INITIALIZED_DATA = 0x00000040;
	static constexpr long _IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080;

	static constexpr long _IMAGE_SCN_MEM_READ = 0x40000000;
	static constexpr long _IMAGE_SCN_MEM_WRITE = 0x80000000;
	static constexpr long _IMAGE_SCN_MEM_EXECUTE = 0x20000000;

	static constexpr long _IMAGE_SCN_CNT_CODE = 0x00000020;
}

#endif