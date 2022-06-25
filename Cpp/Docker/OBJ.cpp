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

vector<PE::Section> PE::Gather_All_Sections(vector<char> buffer, int Section_Count)
{
	vector<Section> Result;
	for (int i = sizeof(Header); i < Section_Count; i += sizeof(Section)) {
		Result.push_back(*(Section*)&(buffer[i]));
	}
	return Result;
}

vector<string> PE::Get_Symbol_Table_Content(Header h, vector<char> buffer)
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

void PE::OBJ_Analyser(vector<string>& Output) {
	//get the header and then start up the section suckup syste 2000 :D
	//read the file
	vector<uint8_t> tmp = DOCKER::Get_Char_Buffer_From_File(DOCKER::Working_Dir.back().second + DOCKER::FileName.back(), "");
	vector<char> Buffer = vector<char>(*(char*)tmp.data(), tmp.size());

	//read the header of this obj file
	Header header = *(Header*)&Buffer;

	DOCKER::Append(Output, Get_Symbol_Table_Content(header, Buffer));
}

PE::PE_OBJ::PE_OBJ(vector<Byte_Map_Section*> Sections){
	this->Header.Machine = selector->OBJ_Machine_ID;
	this->Header.Number_Of_Sections = Sections.size();
	this->Header.Date_Time = time_t(time(NULL));
	this->Header.Pointer_To_Symbol_Table = offsetof(PE::Header, PE::Header::Characteristics) + sizeof(Header::Characteristics) + sizeof(PE::Section) * Sections.size();

	//calculate the exports and import functions from global scope
	for (auto s : Global_Scope->Defined){
		if (s->Has(vector<string>{"export", "import"}) > 0){
			this->Header.Number_Of_Symbols++;
		}
	}

	this->Header.Size_Of_Optional_Header = 0;
	this->Header.Characteristics = _IMAGE_FILE_LARGE_ADDRESS_AWARE;

	this->Symbols = Generate_Symbol_Table();

	vector<string> Symbol_Names = Generate_Name_Section_For_Symbol_Table();

	unsigned long long Symbol_Name_Size = 0;
	for (auto i : Symbol_Names){
		//add the null terminator
		Symbol_Name_Size += i.size() + 1;

	}
	
	this->Sections = Generate_Section_Table(Sections, this->Header.Pointer_To_Symbol_Table + sizeof(this->Header.Pointer_To_Symbol_Table) + sizeof(PE::Symbol) * Symbols.size() + Symbol_Name_Size);

	//Remove the optional headers from the buffer
	unsigned char* Header_Start_Address = (unsigned char*)&this->Header;
	unsigned char* Header_End_Address = (unsigned char*)&this->Header.Characteristics + sizeof(this->Header.Characteristics);

	int s = sizeof(PE::Symbol);

	unsigned int String_Table_Size = 0;

	vector<unsigned char> String_Table_Buffer;

	for (auto i : Symbol_Names){

		String_Table_Buffer.insert(String_Table_Buffer.end(), i.begin(), i.end());

		String_Table_Buffer.push_back(0);

	}
	String_Table_Size = String_Table_Buffer.size() + sizeof(String_Table_Size);
	this->String_Table_Buffer = String_Table_Buffer; 

	this->Relocations = Generate_Relocation_Table(Sections, Symbols, String_Table_Buffer);
}

vector<unsigned char> PE::Write_Obj(PE::PE_OBJ& obj){
	vector<unsigned char> Buffer;

	//Remove the optional headers from the buffer
	unsigned char* Header_Start_Address = (unsigned char*)&obj.Header;
	unsigned char* Header_End_Address = (unsigned char*)&obj.Header.Characteristics + sizeof(obj.Header.Characteristics);

	Buffer.insert(Buffer.end(), (unsigned char*)&obj.Header, Header_End_Address);

	Buffer.insert(Buffer.end(), (unsigned char*)obj.Sections.data(), (unsigned char*)obj.Sections.data() + sizeof(PE::Section) * obj.Sections.size());

	Buffer.insert(Buffer.end(), (unsigned char*)obj.Symbols.data(), (unsigned char*)obj.Symbols.data() + sizeof(PE::Symbol) * obj.Symbols.size());

	Buffer.insert(Buffer.end(), (unsigned char*)&obj.String_Table_Size, (unsigned char*)&obj.String_Table_Size + sizeof(obj.String_Table_Size));

	Buffer.insert(Buffer.end(), obj.String_Table_Buffer.begin(), obj.String_Table_Buffer.end());

	for (auto i : obj.Content){

		for (auto& j : i->Byte_Maps){

			vector<unsigned char> Data = selector->Assemble(j);

			Buffer.insert(Buffer.end(), Data.begin(), Data.end());

		}

	}

	//transform the 
	return Buffer;

}

PE::PE_OBJ* PE::Cluster_PE_Objects(vector<PE::PE_OBJ*> Input){
	//Combine the content sections
	if (Input.size() > 1){
		unsigned long long Current_Offset = 0;
		for (auto& Current_Section : Input[0]->Content){

			//Give the starting address of this section
			Current_Offset += Current_Section->Calculated_Address;
			Current_Section->Calculated_Address = Current_Offset;


			for (int i = 1; i < Input.size(); i++){
				for (auto& j : Input[i]->Content){
					if (j->Name == Current_Section->Name){
						Current_Section->Byte_Maps.insert(Current_Section->Byte_Maps.end(), j->Byte_Maps.begin(), j->Byte_Maps.end());
						Current_Section->Calculated_Size += j->Calculated_Size;
					}
				}
			}
		}
	}

	PE_OBJ* Result = new PE_OBJ(Input[0]->Content);

	return Result;
}

//This function takes a files contant and disects it into a PE OBJ object
PE::PE_OBJ::PE_OBJ(vector<unsigned char> File){

	bool File_Does_Not_Use_Optional_Header = false;

	//First we need to check if the file is a valid PE file
	if (File.size() < sizeof(PE::Header)){
		//The OBJ headers could not have the optional header
		if (File.size() < offsetof(PE::Header, PE::Header::Characteristics)){
			//The file is too small to be a valid PE file
			Report(Observation(ERROR, "File is too small to be a valid PE file", LINKER_INVALID_FILE));
			return;
		}
		else{
			//The file is a valid PE file without an optional header
			File_Does_Not_Use_Optional_Header = true;
		}
	}

	int Header_Size = sizeof(PE::Header);

	//Now we can safely assume that the file is a valid PE file
	if (File_Does_Not_Use_Optional_Header){
		//Move the file start content to header with the size of the non optional header
		Header_Size = offsetof(PE::Header, PE::Header::Characteristics);
	}
	
	move(File.begin(), File.begin() + Header_Size, (unsigned char*)&this->Header);

	//now that we have the header information we can extract the section table
	for (int i = 0; i < this->Header.Number_Of_Sections; i++){
		PE::Section Section;

		move(File.begin() + Header_Size + sizeof(PE::Section) * i, File.begin() + Header_Size + sizeof(PE::Section) * (i + 1), (unsigned char*)&Section);

		Sections.push_back(Section);
	}

	//Now we can extract the symbol table
	for (int i = 0; i < this->Header.Number_Of_Symbols; i++){
		PE::Symbol Symbol;

		move(File.begin() + Header_Size + sizeof(PE::Section) * this->Header.Number_Of_Sections + sizeof(PE::Symbol) * i, File.begin() + Header_Size + sizeof(PE::Section) * this->Header.Number_Of_Sections + sizeof(PE::Symbol) * (i + 1), (unsigned char*)&Symbol);

		Symbols.push_back(Symbol);
	}

	//Now we can extract the string table
	unsigned int String_Table_Size = 0;

	//For reading purposes
	int Current_Offset = Header_Size + sizeof(PE::Section) * this->Header.Number_Of_Sections + sizeof(PE::Symbol) * this->Header.Number_Of_Symbols;
	move(File.begin() + Current_Offset, File.begin() + Current_Offset + sizeof(String_Table_Size), (unsigned char*)&String_Table_Size);
	Current_Offset += sizeof(String_Table_Size);


	String_Table.resize(String_Table_Size);
	move(File.begin() + Current_Offset, File.begin() + Current_Offset + String_Table_Size, String_Table.begin());


	//Now we can extract the Sections
	Current_Offset += String_Table_Size;

	for (auto i : Sections){
		vector<unsigned char> Section_Data;
		Section_Data.resize(i.Size_Of_Raw_Data);

		move(File.begin() + i.Pointer_To_Raw_Data, File.begin() + i.Pointer_To_Raw_Data + i.Size_Of_Raw_Data, Section_Data.begin());

		Raw_Section section;
		section.Name = i.Name;
		section.Data = Section_Data;
	}

}

vector<PE::Section> PE::Generate_Section_Table(vector<Byte_Map_Section*> Input, unsigned long long Origo){

	vector<PE::Section> Result;

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

vector<PE::Symbol> PE::Generate_Symbol_Table(){

	vector<PE::Symbol> Result;

	//Skip the String_Table_Size identifier

	long long Current_Symbol_Offset = sizeof(unsigned int);
	for (auto i : assembler->Symbol_Table){

		PE::Symbol Current;

		//Generate the offset for the name redies in, transform it to text
		Current.Full_Name = Current_Symbol_Offset << 32;

		Current.Value = i.second.first;
		Current.Section_Number = i.second.second;
		Current.Type = 0;
		Current.Storage_Class = _IMAGE_SYM_CLASS_LABEL;
		Current.Number_Of_Aux_Symbols = 0;

		Result.push_back(Current);

		Current_Symbol_Offset += i.first.size() + 1;

	}

	return Result;


}

vector<string> PE::Generate_Name_Section_For_Symbol_Table(){
	
	vector<string> Result;

	for (auto symbol : assembler->Symbol_Table){
		Result.push_back(symbol.first);
	}

	return Result;

}

string PE::Symbol::Get_Name(vector<unsigned char>& String_Table){
	string Result = "";

	for (int i = Full_Name; i < String_Table.size(); i++){

		if (String_Table[i] == 0){
			break;
		}
		else{
			Result += String_Table[i];
		}

	}

	return Result;
}

vector<PE::Relocation> PE::Generate_Relocation_Table(vector<Byte_Map_Section*> Sections, vector<PE::Symbol> Symbols, vector<unsigned char>& String_Table){
	vector<PE::Relocation> Result;

	map<string, int> Extern_Symbols;

	//First extract all the extern symbols from the symbols list
	int Index = 0;
	for (auto i : Symbols){
		if (i.Section_Number == 0){
			Extern_Symbols.insert({i.Get_Name(String_Table), Index});
		}
		Index++;
	}

	for (auto& section : Sections){

		for (auto& byte_map : section->Byte_Maps){

			if (byte_map->Has_External_Label){

				PE::Relocation relocation;
				relocation.Virtual_Address = byte_map->Address;
				relocation.Symbol_Table_Index = Extern_Symbols[byte_map->Label];
				relocation.Type = _SYSTEM_BIT_SIZE_;

				Result.push_back(relocation);

			}

		}

	}

	return Result;
}