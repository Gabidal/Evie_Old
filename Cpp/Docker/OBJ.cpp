#include "../../H/Docker/OBJ.h"

#include "../../H/BackEnd/Selector.h"
#include "../../H/Nodes/Node.h"
#include "../../H/Assembler/Assembler_Types.h"
#include "../../H/UI/Usr.h"
#include "../../H/UI/Safe.h"
#include "../../H/Assembler/Assembler.h"
#include "../../H/Docker/Docker.h"

extern Selector* selector;

extern Node* Global_Scope;

extern Usr* sys;

extern Assembler* assembler;

vector<OBJ::Section> OBJ::Gather_All_Sections(vector<char> buffer, int Section_Count)
{
	vector<Section> Result;
	for (int i = sizeof(Header); i < Section_Count; i += sizeof(Section)) {
		Result.push_back(*(Section*)&(buffer[i]));
	}
	return Result;
}

vector<string> OBJ::Get_Symbol_Table_Content(Header h, vector<char> buffer)
{
	vector<string> Result;

	vector<Symbol> Symbols;
	for (int i = *(int*)h.Pointer_To_Symbol_Table; i < buffer.size(); i++) {
		Symbols.push_back(*(Symbol*)&(buffer[i]));
	}

	for (auto& S : Symbols) {
		if (S.Name.Header == 0) {
			string Name = "";
			for (int i = *(int*)S.Name.Offset; i < buffer.size(); i++) {
				if (buffer[i] == '\0')
					break;
				Name += buffer[i];
			}
			Result.push_back(Name);
		}
		else
			Result.push_back(string(S.Full_Name, 8));
	}

	return Result;
}

void OBJ::OBJ_Analyser(vector<string>& Output) {
	//get the header and then start up the section suckup syste 2000 :D
	//read the file
	vector<uint8_t> tmp = DOCKER::Get_Char_Buffer_From_File(DOCKER::Working_Dir.back().second + DOCKER::FileName.back(), "");
	vector<char> Buffer = vector<char>(*(char*)tmp.data(), tmp.size());

	//read the header of this obj file
	Header header = *(Header*)&Buffer;

	DOCKER::Append(Output, Get_Symbol_Table_Content(header, Buffer));
}

vector<unsigned char> OBJ::Create_Obj(vector<Byte_Map_Section*> Input){
	OBJ::Header header;
	header.Machine = selector->OBJ_Machine_ID;
	header.Number_OF_Sections = Input.size();
	header.Date_Time = time_t(time(NULL));
	header.Pointer_To_Symbol_Table = offsetof(OBJ::Header, Characteristics) + sizeof(Header::Characteristics) + sizeof(OBJ::Section) * Input.size();

	//calculate the exports and import functions from global scope
	for (auto s : Global_Scope->Defined){
		if (s->Has(vector<string>{"export", "import"}) > 0){
			header.Number_Of_Symbols++;
		}
	}

	header.Size_Of_Optional_Header = 0;
	header.Characteristics = _IMAGE_FILE_LARGE_ADDRESS_AWARE;

	// header.Magic = _MAGIC_PE32_PlUS;
	// header.Linker_Version = 0x0000;
	// for (auto i : Input){
	// 	header.Size_Of_Code += i->Calculated_Size;
	// }
	// for (auto i : Input){
	// 	if (i->Is_Data_Section)
	// 		header.Size_Of_Initialized_Data += i->Calculated_Size;
	// }
	// header.Size_Of_Uninitialized_Data = 0;
	// if (sys->Info.Format == "lib"){
	// 	header.Address_Of_Entry_Point = 0;
	// }
	// else{
	// 	string Unmangled_Starting_Function_Name = sys->Info.Start_Function_Name;
	// 	Node* Function = Global_Scope->Find(Unmangled_Starting_Function_Name, Global_Scope, FUNCTION_NODE);
	// 	if (Function == nullptr){
	// 		Report(Observation(ERROR, "Function " + Unmangled_Starting_Function_Name + " not found in the global scope", LINKER_MISSING_STARTING_FUNCTION));
	// 		return vector<unsigned char>();
	// 	}
	// 	string Mangled_Starting_Function_Name = Function->Mangled_Name;
	// 	header.Address_Of_Entry_Point = assembler->Symbol_Table.at(Mangled_Starting_Function_Name);
	// }
	// header.Base_Of_Code = Input.size() * sizeof(Section) + header.Number_Of_Symbols * sizeof(Symbol) + sizeof(Header);
	// header.Base_Of_Data = header.Base_Of_Code + header.Size_Of_Code;
	// if (sys->Info.OS == "win"){ 
	// 	if (sys->Info.Format == "exe"){
	// 		header.Image_Base = _WINDOWS_PE_EXE_BASE_IMAGE;
	// 	}
	// 	else if (sys->Info.Format == "dll"){
	// 		header.Image_Base = _WINDOWS_PE_DLL_BASE_IMAGE;
	// 	}
	// }
	// header.Section_Alignment = _FILE_ALIGNMENT;
	// header.File_Alignment = _FILE_ALIGNMENT;
	// header.Operating_System_Version = 0x0006;
	// header.Image_Version = 0;
	// header.Subsystem_Version = 0;
	// header.Win32_Version_Value = 0;
	// header.Size_Of_Image = header.Size_Of_Code + header.Size_Of_Initialized_Data + header.Size_Of_Uninitialized_Data + sizeof(Section) * Input.size() + header.Number_Of_Symbols * sizeof(Symbol) + sizeof(Header);
	// header.Size_Of_Headers = sizeof(Header) + sizeof(Section) * Input.size() + header.Number_Of_Symbols * sizeof(Symbol);
	// header.Check_Sum = 0;
	// header.Subsystem = 0;
	// header.Dll_Characteristics = 0;
	// header.Size_Of_Stack_Reserve = 0x100000;
	// header.Size_Of_Stack_Commit = 0x1000;
	// //Allocate for one bucket + bucket buffer for the Evie allocator.
	// header.Size_Of_Heap_Reserve = _BUCKET_SIZE;
	// header.Size_Of_Heap_Commit = _ALLOCATOR_BUCKET_COUNT + _BUCKET_SIZE;
	// header.Loader_Flags = 0;
	// header.Number_Of_Rva_And_Sizes = 0;

	vector<OBJ::Symbol> Symbols = Generate_Symbol_Table();

	vector<string> Symbol_Names = Generate_Name_Section_For_Symbol_Table();

	unsigned long long Symbol_Name_Size = 0;
	for (auto i : Symbol_Names){
		//add the null terminator
		Symbol_Name_Size += i.size() + 1;

	}
	
	vector<OBJ::Section> Sections = Generate_Section_Table(Input, header.Pointer_To_Symbol_Table + sizeof(header.Pointer_To_Symbol_Table) + sizeof(OBJ::Symbol) * Symbols.size() + Symbol_Name_Size);

	//Now inline all the data into one humongus buffer
	vector<unsigned char> Buffer;

	//Remove the optional headers from the buffer
	unsigned char* Header_Start_Address = (unsigned char*)&header;
	unsigned char* Header_End_Address = (unsigned char*)&header.Characteristics + sizeof(header.Characteristics);

	Buffer.insert(Buffer.end(), (unsigned char*)&header, Header_End_Address);

	Buffer.insert(Buffer.end(), (unsigned char*)Sections.data(), (unsigned char*)Sections.data() + sizeof(OBJ::Section) * Input.size());

	Buffer.insert(Buffer.end(), (unsigned char*)Symbols.data(), (unsigned char*)Symbols.data() + sizeof(OBJ::Symbol) * Symbols.size());

	int s = sizeof(OBJ::Symbol);

	unsigned int String_Table_Size = 0;

	vector<unsigned char> String_Table_Buffer;

	for (auto i : Symbol_Names){

		String_Table_Buffer.insert(String_Table_Buffer.end(), i.begin(), i.end());

		String_Table_Buffer.push_back(0);

	}
	String_Table_Size = String_Table_Buffer.size() + sizeof(String_Table_Size);


	Buffer.insert(Buffer.end(), (unsigned char*)&String_Table_Size, (unsigned char*)&String_Table_Size + sizeof(String_Table_Size));

	Buffer.insert(Buffer.end(), String_Table_Buffer.begin(), String_Table_Buffer.end());

	for (auto i : Input){

		for (auto& j : i->Byte_Maps){

			vector<unsigned char> Data = selector->Assemble(j);

			Buffer.insert(Buffer.end(), Data.begin(), Data.end());

		}


	}

	//transform the 
	return Buffer;

}

vector<OBJ::Section> OBJ::Generate_Section_Table(vector<Byte_Map_Section*> Input, unsigned long long Origo){

	vector<OBJ::Section> Result;

	for (auto i : Input){
		Section tmp;
		 memcpy(&tmp.Name, i->Name.data(), i->Name.size());
		 tmp.Virtual_Size = i->Calculated_Size;
		 tmp.Virtual_Address = i->Calculated_Address;
		 tmp.Size_Of_Raw_Data = i->Calculated_Size;
		 tmp.Pointer_To_Raw_Data = i->Calculated_Address + Origo;
		 tmp.Pointer_To_Relocations = 0;
		 tmp.Pointer_To_Line_Numbers = 0;
		 tmp.Number_Of_Relocations = 0;
		 tmp.Number_Of_Line_Numbers = 0;

		if (i->Is_Data_Section){
			tmp.Characteristics = _IMAGE_SCN_CNT_INITIALIZED_DATA | _IMAGE_SCN_MEM_READ | _IMAGE_SCN_MEM_WRITE;
		}
		else{
			tmp.Characteristics = _IMAGE_SCN_CNT_CODE | _IMAGE_SCN_MEM_EXECUTE | _IMAGE_SCN_MEM_READ;
		}

		Result.push_back(tmp);
	}

	return Result;

}

vector<OBJ::Symbol> OBJ::Generate_Symbol_Table(){

	vector<OBJ::Symbol> Result;

	//Skip the String_Table_Size identifier

	long long Current_Symbol_Offset = sizeof(unsigned int);
	for (auto i : assembler->Symbol_Table){

		OBJ::Symbol Current;

		//Generate the offset for the name redies in, transform it to text
		Current.Full_Name = Current_Symbol_Offset << 32;

		Current.Value = i.second;
		Current.Section_Number = 0;
		Current.Type = 0;
		Current.Storage_Class = _IMAGE_SYM_CLASS_LABEL;
		Current.Number_Of_Aux_Symbols = 0;

		Result.push_back(Current);

		Current_Symbol_Offset += i.first.size() + 1;

	}

	return Result;


}

vector<string> OBJ::Generate_Name_Section_For_Symbol_Table(){
	
	vector<string> Result;

	for (auto symbol : assembler->Symbol_Table){
		Result.push_back(symbol.first);
	}

	return Result;

}