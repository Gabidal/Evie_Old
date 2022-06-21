#ifndef _OBJ_H_
#define _OBJ_H_
#include <vector>
#include <string>

#pragma pack(push, 1)	// Align to 1 byte

using namespace std;

class Byte_Map_Section;

namespace PE {
	class Header {
	public:
		unsigned short Machine = 0;
		unsigned short Number_Of_Sections = 0;
		unsigned int Date_Time = 0;
		unsigned int Pointer_To_Symbol_Table = 0;
		unsigned int Number_Of_Symbols = 0;
		unsigned short Size_Of_Optional_Header = 0;
		unsigned short Characteristics = 0;
		unsigned short Magic = 0;
		unsigned short Linker_Version = 0;
		unsigned int Size_Of_Code = 0;
		unsigned int Size_Of_Initialized_Data = 0;
		unsigned int Size_Of_Uninitialized_Data = 0;
		unsigned int Address_Of_Entry_Point = 0;
		unsigned int Base_Of_Code = 0;
		unsigned int Base_Of_Data = 0;
		unsigned int Image_Base = 0;
		unsigned int Section_Alignment = 0;
		unsigned int File_Alignment = 0;
		unsigned int Operating_System_Version = 0;
		unsigned int Image_Version = 0;
		unsigned int Subsystem_Version = 0;
		unsigned int Win32_Version_Value = 0;
		unsigned int Size_Of_Image = 0;
		unsigned int Size_Of_Headers = 0;
		unsigned int Check_Sum = 0;
		unsigned short Subsystem = 0;
		unsigned short Dll_Characteristics = 0;
		unsigned int Size_Of_Stack_Reserve = 0;
		unsigned int Size_Of_Stack_Commit = 0;
		unsigned int Size_Of_Heap_Reserve = 0;
		unsigned int Size_Of_Heap_Commit = 0;
		unsigned int Loader_Flags = 0;
		unsigned int Number_Of_Rva_And_Sizes = 0;

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
		unsigned int Size_Of_Bound_Impor = 0;
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
		unsigned long long Name = 0;
		unsigned int Virtual_Size = 0;
		unsigned int Virtual_Address = 0;
		unsigned int Size_Of_Raw_Data = 0;
		unsigned int Pointer_To_Raw_Data = 0;
		unsigned int Pointer_To_Relocations = 0;
		unsigned int Pointer_To_Line_Numbers = 0;
		unsigned short Number_Of_Relocations = 0;
		unsigned short Number_Of_Line_Numbers = 0;
		unsigned int Characteristics = 0;
	};

	class Symbol {
	public:
		union {
			struct {
				char Header;
				char Offset[7];
			}Name;
			long long Full_Name = 0;
		};
		int Value = 0;
		short Section_Number = 0;
		short Type = 0;
		char Storage_Class = 0;
		char Number_Of_Aux_Symbols = 0;

		string Get_Name(vector<unsigned char>& String_Table);
	};

	class Raw_Section{
	public:
		string Name = "";
		
		vector<unsigned char> Data;

	};

	class PE_OBJ{
	public:
		Header Header;
		vector<Section> Sections;
		vector<Symbol> Symbols;
		vector<string> String_Table;

		vector<Raw_Section> Raw_Sections;

		PE_OBJ(vector<unsigned char> File);

	};

	class Relocation{
	public:
		unsigned int Virtual_Address = 0;
		unsigned int Symbol_Table_Index = 0;
		unsigned short Type = 0;
	};

	vector<Relocation> Generate_Relocation_Table(vector<Byte_Map_Section*> Sections, vector<PE::Symbol> Symbols, vector<unsigned char>& String_Table);

	vector<Section> Gather_All_Sections(vector<char> buffer, int Section_Count);

	vector<string> Get_Symbol_Table_Content(Header h, vector<char> buffer);

	void OBJ_Analyser(vector<string>& Output);

	vector<unsigned char> Create_Obj(vector<Byte_Map_Section*> Input);

	vector<Section> Generate_Section_Table(vector<Byte_Map_Section*> Input, unsigned long long Origo);

	vector<Symbol> Generate_Symbol_Table();

	vector<string> Generate_Name_Section_For_Symbol_Table();

	static constexpr unsigned char _IMAGE_FILE_LARGE_ADDRESS_AWARE = 0x0020;
	static constexpr unsigned short _MAGIC_PE32_PlUS = 0x20b;
	static constexpr unsigned long _WINDOWS_PE_DLL_BASE_IMAGE = 0x10000000;
	static constexpr unsigned long _WINDOWS_PE_EXE_BASE_IMAGE = 0x00400000;

	static constexpr unsigned long _FILE_ALIGNMENT = 0x200;

	static constexpr unsigned long _ALLOCATOR_BUCKET_COUNT = 100000;
	static constexpr unsigned long _BUCKET_SIZE = 700000;

	static constexpr unsigned long _IMAGE_SCN_CNT_INITIALIZED_DATA = 0x00000040;
	static constexpr unsigned long _IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080;

	static constexpr unsigned long _IMAGE_SCN_MEM_READ = 0x40000000;
	static constexpr unsigned long _IMAGE_SCN_MEM_WRITE = 0x80000000;
	static constexpr unsigned long _IMAGE_SCN_MEM_EXECUTE = 0x20000000;

	static constexpr unsigned long _IMAGE_SCN_CNT_CODE = 0x00000020;

	static constexpr unsigned long _IMAGE_SYM_CLASS_LABEL = 0x00000006;
}

#pragma pack(pop) // Restore alignment
#endif