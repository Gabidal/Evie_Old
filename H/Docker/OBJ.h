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
		//unsigned int Base_Of_Data = 0;
		unsigned long long Image_Base = 0;
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
		unsigned long long Size_Of_Stack_Reserve = 0;
		unsigned long long Size_Of_Stack_Commit = 0;
		unsigned long long Size_Of_Heap_Reserve = 0;
		unsigned long long Size_Of_Heap_Commit = 0;
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

	class Bull_Shit_Headers {
	public:
		unsigned short Signature = 0x5A4D;
		unsigned char Empty2[64 - 2 - 4] = { 0 };
		unsigned int PE_Offset = 64;
		unsigned int Signature_The_Second = 0x4550;
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
			unsigned long long Full_Name = 0;
		};
		int Value = 0;
		short Section_Number = 0;	// where 1 is 0'th index.
		short Type = 0;
		char Storage_Class = 0;
		char Number_Of_Aux_Symbols = 0;

		string Get_Name(vector<unsigned char>& String_Table);
	};

	class Raw_Section{
	public:
		string Name = "";

		unsigned long long Section_Address = 0;
		
		vector<unsigned char> Data;
	};

	enum class IMAGE_REL_AMD64{
		REL_AMD64_ABSOLUTE,
		REL_AMD64_ADDR64,
		REL_AMD64_ADDR32,
		REL_AMD64_ADDR32NB,
		REL_AMD64_REL32,
		REL_AMD64_REL32_1,
		REL_AMD64_REL32_2,
		REL_AMD64_REL32_3,
		REL_AMD64_REL32_4,
		REL_AMD64_REL32_5,
		REL_AMD64_SECTION,
		REL_AMD64_SECREL,
		REL_AMD64_SECREL7,
		REL_AMD64_TOKEN,
		REL_AMD64_SREL32,
		REL_AMD64_PAIR,
		REL_AMD64_SSPAN32
	};

	class Relocation{
	public:
		unsigned int Virtual_Address = 0;
		unsigned int Symbol_Table_Index = 0;
		unsigned short Type = 0;
	};

	template<typename T>
	class Group_Info{
	public:
		string File_Origin = "";
		unsigned long long Additional_Offset = 0;
		vector<T> Data;
	};

	class Export_Directory{
	public:
		unsigned int Export_Flags = 0;
		unsigned int Time_Date_Stamp = 0;
		unsigned short Major_Version = 0;
		unsigned short Minor_Version = 0;
		unsigned int DLL_Name_RVA = 0;
		unsigned int Ordinal_Base = 0;
		unsigned int Address_Table_Entries = 0;
		unsigned int Number_Of_Name_Entries = 0;
		unsigned int Export_Address_Table_RVA = 0;
		unsigned int Name_Pointer_RVA = 0;
		unsigned int Ordinal_Table_RVA = 0;
	};

	class Export_Address_Table{
	public:
		unsigned int Address = 0;
	};

	class Export_Table{
	public:
		Export_Directory Directory;
		vector<Export_Address_Table> Address_Table;
		vector<unsigned int> Name_Address_Table;
		vector<unsigned short> Ordinal_Table;
		vector<string> Name_Table;
		unsigned int Size_Of_Name_Table = 0;
	};

	// Only used as size calculations, so padding is not of concern.
	class Hint{
	public:
		unsigned short Hint_Name_Table_Index = 0;
		string Name = "";
		bool Padding = false;
		unsigned int Hint_Name_Size = 0;
	};

	class Import_Lookup{
	public:
		unsigned long long Name_Address = 0;
	};

	class Import_Directory{
	public:
		unsigned int Lookup_Table_RVA = 0;
		unsigned int Time_Date_Stamp = 0;
		unsigned int Forwarder_Chain = 0;
		unsigned int DLL_Name = 0;
		unsigned int Import_Address_Table_RVA = 0;
	};

	class Import_Table{
	public:
		Import_Directory Directory;
		Import_Directory Null_Directory_Table;
		vector<Import_Lookup> Lookup_Table;
		unsigned long long Null_Lookup_Table = 0;
		vector<Hint> Hint_Table;
	};

	class Relocation_Field{
	public:
		unsigned short Data;

		unsigned char Get_Type(){
			return (unsigned char)(Data >> (unsigned short)12);
		}

		unsigned short Get_Virtual_Address(){
			return Data & (unsigned short)0x0FFF;
		}

		void Set_Type(unsigned char c){
			Data = (Data & (unsigned short)0x0FFF) | (c << (unsigned char)12);
		}

		void Set_Virtual_Address(unsigned short c){
			unsigned char Type = Get_Type();

			Data = c;

			Set_Type(Type);
		}
	};

	class Base_Relocation_Block{
	public:
		unsigned int Page_RVA = 0;
		unsigned short Block_Size = 0;
		vector<Relocation_Field> Relocations;
	};

	class Relocation_Table{
	public:
		vector<Base_Relocation_Block> Blocks;
	};

	class PE_OBJ{
	public:
		string File_Name = "";

		Header Header;
		vector<Section> Sections;
		vector<Symbol> Symbols;
		vector<string> String_Table;
		vector<unsigned char> String_Table_Buffer;
		unsigned int String_Table_Size = 0;
		vector<Relocation> Relocations;

		vector<Raw_Section> Raw_Sections;
		vector<Byte_Map_Section*> Content;
		
		//DLL/EXE Stuff
		Export_Table Exports;
		Import_Table Imports;
		Relocation_Table Base_Relocations;
		vector<Import_Lookup> Import_Address_Table;
		//END of DLL/EXE stuff

		PE_OBJ(){}

		PE_OBJ(vector<unsigned char> File, string File_Name);

		PE_OBJ(vector<Byte_Map_Section*> Sections);
	};

	class OBJ_Pile{
	public:
		Header header;

		vector<Group_Info<Section>> Sections;
		vector<Group_Info<Symbol>> Symbols;
		vector<Group_Info<string>> String_Table;
		vector<Group_Info<unsigned char>> String_Table_Buffer;
		vector<pair<string, unsigned long long>> String_Table_Size;
		vector<Group_Info<Relocation>> Relocations;
		vector<Group_Info<Raw_Section>> Raw_Sections;

		OBJ_Pile(vector<PE::PE_OBJ*> OBJs);

		PE::PE_OBJ* Compile();
	};

	vector<Relocation> Generate_Relocation_Table(vector<Byte_Map_Section*> Sections, vector<PE::Symbol> Symbols, vector<unsigned char>& String_Table, vector<PE::Section> Section_Table);

	vector<Section> Gather_All_Sections(vector<char> buffer, int Section_Count);

	vector<string> Get_Symbol_Table_Content(Header h, vector<char> buffer);

	void OBJ_Analyser(vector<string>& Output);

	void Add_Padding_To_Offsets(PE::PE_OBJ& obj);

	vector<unsigned char> Write_Obj(PE_OBJ& Input);

	PE::PE_OBJ* Cluster_Local_PE_Objects(vector<PE::PE_OBJ*> Input);
	PE::PE_OBJ* Cluster_External_PE_Objects(vector<string> Input);

	unsigned long long Get_Relative_Address(unsigned long long address, PE::OBJ_Pile& pile, string File_Origin);
	
	vector<Section> Generate_Section_Table(vector<Byte_Map_Section*> Input, unsigned long long Origo, PE::PE_OBJ* obj);

	vector<Symbol> Generate_Symbol_Table();

	vector<string> Generate_Name_Section_For_Symbol_Table();

	static constexpr unsigned short _IMAGE_FILE_LARGE_ADDRESS_AWARE = 0x0020;
	static constexpr unsigned short _IMAGE_FILE_EXECUTABLE_IMAGE = 0x0002;
	static constexpr unsigned short _IMAGE_FILE_DEBUG_STRIPPED = 0x0200;
	static constexpr unsigned short _IMAGE_FILE_LINE_NUMS_STRIPPED = 0x0004;
	static constexpr unsigned short _IMAGE_FILE_RELOCS_STRIPPED = 0x0001;
	static constexpr unsigned short _IMAGE_FILE_DLL = 0x2000;
	static constexpr unsigned short _MAGIC_PE32_PlUS = 0x20b;
	static constexpr unsigned long _WINDOWS_PE_DLL_BASE_IMAGE = 0x10000000;
	static constexpr unsigned long _WINDOWS_PE_EXE_BASE_IMAGE = 0x00400000;

	static constexpr unsigned long _FILE_ALIGNMENT = 0x200;
	static constexpr unsigned long _SECTION_ALIGNMENT = 0x200;

	static constexpr unsigned long _ALLOCATOR_BUCKET_COUNT = 100000;
	static constexpr unsigned long _BUCKET_SIZE = 700000;

	static constexpr unsigned long _IMAGE_SCN_CNT_INITIALIZED_DATA = 0x00000040;
	static constexpr unsigned long _IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080;

	static constexpr unsigned long _IMAGE_SCN_MEM_READ = 0x40000000;
	static constexpr unsigned long _IMAGE_SCN_MEM_WRITE = 0x80000000;
	static constexpr unsigned long _IMAGE_SCN_MEM_EXECUTE = 0x20000000;
	static constexpr unsigned long _IMAGE_SCN_ALIGN_512BYTES = 0x00A00000;

	static constexpr unsigned long _IMAGE_SCN_CNT_CODE = 0x00000020;

	static constexpr unsigned long _IMAGE_SYM_CLASS_EXTERNAL = 0x00000002;
	static constexpr unsigned long _IMAGE_SYM_CLASS_LABEL = 0x00000006;

	static constexpr unsigned long _IMAGE_FILE_MACHINE_AMD64 = 0x8664;

	static constexpr unsigned long MAGIC_NUMBER = 0x20b;

	static constexpr unsigned long _IMAGE_SUBSYSTEM_WINDOWS_CUI = 0x3;

	static constexpr unsigned long _IMAGE_OS_VERSION = (0 << (sizeof(short) * 8)) + 4;

	static constexpr unsigned long _IMAGE_SUBSYSTEM_VERSION = (2 << (sizeof(short) * 8)) + 5;

	static constexpr unsigned long _IMAGE_REL_BASED_LOW = 2;

	static constexpr unsigned long _OPTIONAL_HEADER_DATA_DIRECTORIES_AMOUNT = 16;
}

#pragma pack(pop) // Restore alignment
#endif