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
	int Small_Header_Size = offsetof(PE::Header, PE::Header::Characteristics) + sizeof(PE::Header::Characteristics);

	Header header;

	memcpy(&header, &Buffer[0], Small_Header_Size);

	DOCKER::Append(Output, Get_Symbol_Table_Content(header, Buffer));
}

PE::PE_OBJ::PE_OBJ(vector<Byte_Map_Section*> Sections){
	this->Header.Machine = selector->OBJ_Machine_ID;
	this->Header.Number_Of_Sections = Sections.size();
	this->Header.Date_Time = time_t(time(NULL));
	this->Header.Pointer_To_Symbol_Table = offsetof(PE::Header, PE::Header::Characteristics) + sizeof(Header::Characteristics) + sizeof(PE::Section) * Sections.size();

	this->Header.Size_Of_Optional_Header = 0;
	this->Header.Characteristics = PE::_IMAGE_FILE_LARGE_ADDRESS_AWARE | PE::_IMAGE_FILE_DEBUG_STRIPPED | PE::_IMAGE_FILE_LINE_NUMS_STRIPPED | PE::_IMAGE_FILE_RELOCS_STRIPPED;

	this->Symbols = Generate_Symbol_Table();
	this->Header.Number_Of_Symbols = Symbols.size();

	this->Content = Sections;

	vector<string> Symbol_Names = Generate_Name_Section_For_Symbol_Table();
	
	//Remove the optional headers from the buffer
	unsigned char* Header_Start_Address = (unsigned char*)&this->Header;
	unsigned char* Header_End_Address = (unsigned char*)&this->Header.Characteristics + sizeof(this->Header.Characteristics);

	int s = sizeof(PE::Symbol);

	vector<unsigned char> String_Table_Buffer;

	for (auto i : Symbol_Names){

		String_Table_Buffer.insert(String_Table_Buffer.end(), i.begin(), i.end());

		String_Table_Buffer.push_back(0);

	}
	this->String_Table_Size = String_Table_Buffer.size() + sizeof(String_Table_Size);
	this->String_Table_Buffer = String_Table_Buffer; 

	this->Relocations = Generate_Relocation_Table(Sections, Symbols, String_Table_Buffer);

	this->Sections = Generate_Section_Table(Sections, this->Header.Pointer_To_Symbol_Table + sizeof(this->Header.Pointer_To_Symbol_Table) + sizeof(PE::Symbol) * Symbols.size() + this->String_Table_Size + this->Relocations.size() * sizeof(PE::Relocation), this);

	unsigned long long Header_Size = Header_End_Address - Header_Start_Address + this->Sections.size() * sizeof(PE::Section) + this->Symbols.size() * sizeof(PE::Symbol) + this->String_Table_Size + this->Relocations.size() * sizeof(PE::Relocation);

	//now we need to go the generated symbo table and update all the relative values to absolute values
	// for (auto& i : this->Symbols){

	// 	i.Value += Header_Size;

	// }
}

void PE::Add_Padding_To_Offsets(PE::PE_OBJ& obj){
	int Origo = obj.Header.Pointer_To_Symbol_Table + sizeof(obj.Header.Pointer_To_Symbol_Table) + sizeof(PE::Symbol) * obj.Symbols.size() + obj.String_Table_Size + obj.Relocations.size() * sizeof(PE::Relocation);

	unsigned long long Current_Offset = Origo;

	Current_Offset = (Current_Offset + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

	//	 section id, address difference
	vector<pair<int, int>> Changes;

	int index = 0;
	for (auto& s : obj.Sections){
		pair<int, int> Change;

		Change.second = Current_Offset - s.Pointer_To_Raw_Data;
		Change.first = index;

		Changes.push_back(Change);

		s.Pointer_To_Raw_Data = Current_Offset;
		Current_Offset += s.Size_Of_Raw_Data;
		Current_Offset = ((Current_Offset + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1));
	}


	//Now add the changes to symbols
	int Symbol_Index = 0;
	for (auto& s : obj.Symbols){
		for (auto& c : Changes){
			if (s.Section_Number == c.first){
				s.Value += c.second;
			}
		}

		//Shift the relocations pointing to the section by the section shift.
		for (auto& r : obj.Relocations){
			if (r.Symbol_Table_Index == Symbol_Index){
				r.Virtual_Address += Changes[s.Section_Number].second;
			}
		}

		Symbol_Index++;
	}

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

	Buffer.insert(Buffer.end(), (unsigned char*)obj.Relocations.data(), (unsigned char*)obj.Relocations.data() + sizeof(PE::Relocation) * obj.Relocations.size());


	unsigned long long Symbol_Name_Size = 0;
	for (auto i : obj.Symbols){
		//add the null terminator
		Symbol_Name_Size += i.Get_Name(obj.String_Table_Buffer).size() + 1;

	}

	int Origo = Buffer.size();

	unsigned long long Current_Offset = Origo;

	for (auto i : obj.Content){

		//add padding
		int Padding = ((Current_Offset + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1)) - Current_Offset;

		Buffer.insert(Buffer.end(), Padding, 0);

		for (auto& j : i->Byte_Maps){

			vector<unsigned char> Data = selector->Assemble(j);

			Buffer.insert(Buffer.end(), Data.begin(), Data.end());

			Current_Offset += Data.size();
		}

		Current_Offset += Padding;

	}

	//transform the 
	return Buffer;

}

PE::PE_OBJ* PE::Cluster_Local_PE_Objects(vector<PE::PE_OBJ*> Input){
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

PE::PE_OBJ* PE::Cluster_External_PE_Objects(vector<string> Input){

	//First transform the input of file names into PE::PE_OBJ*
	vector<PE::PE_OBJ*> OBJs;

	for (auto i : Input){
		pair<char*, long long> Raw_Buffer = DOCKER::Read_Bin_File(i);

		vector<unsigned char> Buffer = vector<unsigned char>(Raw_Buffer.first, Raw_Buffer.first + Raw_Buffer.second);

		//check that this is a PE file
		DOCKER::Function_Pointter f = DOCKER::Get_Translator(Buffer);

		if (f != PE::OBJ_Analyser)
			continue;

		OBJs.push_back(new PE::PE_OBJ(Buffer, i));
	}

	PE::OBJ_Pile* Pile = new PE::OBJ_Pile(OBJs);
	
	PE::PE_OBJ* Result = Pile->Compile();

	return Result;
}

PE::PE_OBJ* PE::OBJ_Pile::Compile(){

	PE::PE_OBJ* Result = new PE::PE_OBJ();

	Result->Header = header;

	//Calculate the new values based on the new grouping of the section pile.
	for (auto& s_group : Sections){

		for (auto& r_group : Raw_Sections){
			if (r_group.File_Origin != s_group.File_Origin)
				continue;

			for (auto& s : s_group.Data){
				unsigned long long Current_Offset = 0;

				for (auto& r : r_group.Data){
					unsigned long long Name;
		 			memcpy(&Name, r.Name.data(), r.Name.size());

					if (s.Name == Name){
						
						s.Pointer_To_Raw_Data += r_group.Additional_Offset + Current_Offset;

					}

					r.Section_Address += r_group.Additional_Offset + Current_Offset;
					Current_Offset += r.Data.size();
				}
			}

			//now combine the sections
			Result->Sections.insert(Result->Sections.end(), s_group.Data.begin(), s_group.Data.end());
		}
	}

	//Calculate the new values for the symbol table
	unsigned long long String_Table_Offset = 0;
	for (auto& s_group : Symbols){
		for (auto& symbol : s_group.Data){
			
			vector<unsigned char> Current_String_Table_Buffer;

			for (auto& s_table_buffer : String_Table_Buffer){
				if (s_table_buffer.File_Origin != s_group.File_Origin)
					continue;

				Current_String_Table_Buffer = s_table_buffer.Data;
			}

			Group_Info<string> Current_Symbol_Table;

			for (auto& s_table : String_Table){
				if (s_group.File_Origin != s_table.File_Origin)
					continue;

				Current_Symbol_Table = s_table;
			}

			//Calculate the new offset of the symbol name.
			for (auto& s : Current_Symbol_Table.Data){
				string Symbol_Name = symbol.Get_Name(Current_String_Table_Buffer);

				if (Symbol_Name == s){

					symbol.Full_Name = String_Table_Offset << 32;
				}

				String_Table_Offset += s.size() + 1;
			}

			//Now calculate the new offset of the symbol address.
			unsigned long long Relative_Address = PE::Get_Relative_Address(symbol.Value, *this, s_group.File_Origin);
			unsigned long long Absolute_Address = 0;

			for (auto& r_group : Raw_Sections){
				if (r_group.File_Origin != s_group.File_Origin)
					continue;

				Absolute_Address = r_group.Additional_Offset;
			}

			symbol.Value = Absolute_Address + Relative_Address;
		}
	
		//Now combine the symbol tables
		Result->Symbols.insert(Result->Symbols.end(), s_group.Data.begin(), s_group.Data.end());
	}
	
	//Join String table since there is nothing to calculate.
	for (auto& s_table : String_Table){
		Result->String_Table.insert(Result->String_Table.end(), s_table.Data.begin(), s_table.Data.end());
	}

	//Join the string table buffer since there is nothing to calculate.
	for (auto& s_table_buffer : String_Table_Buffer){
		Result->String_Table_Buffer.insert(Result->String_Table_Buffer.end(), s_table_buffer.Data.begin(), s_table_buffer.Data.end());
	}

	//Calculate the new string table buffer size
	for (auto& s_table_buffer : String_Table_Buffer){
		Result->String_Table_Size += s_table_buffer.Data.size();
	}

	//Calculate the new values for the relocations table.
	//first update the Symbol table indexs.
	int Current_Symbols_Count = 0; 
	for (int r_group_index = 0; r_group_index < Relocations.size(); r_group_index++){

		for (auto& r : Relocations[r_group_index].Data){
			r.Symbol_Table_Index += Current_Symbols_Count;
		}

		//because there is as many relocation tables as there are sections, we can just use the relocation pile index to get the same file's symbol table size.
		Current_Symbols_Count += Symbols[r_group_index].Data.size();
	}

	//now we can calculate the virtual addresses of the relocations.
	for (auto& r_group : Relocations){
		for (auto& r : r_group.Data){
			unsigned long long Relative_Address = PE::Get_Relative_Address(r.Virtual_Address, *this, r_group.File_Origin);
			unsigned long long Absolute_Address = 0;

			for (auto& r_group : Raw_Sections){
				if (r_group.File_Origin != r_group.File_Origin)
					continue;

				Absolute_Address = r_group.Additional_Offset;
			}

			r.Virtual_Address = Absolute_Address + Relative_Address;
		}

		//now combine the relocations
		Result->Relocations.insert(Result->Relocations.end(), r_group.Data.begin(), r_group.Data.end());
	}

	//now combine the raw sections
	for (auto& r_group : Raw_Sections){
		Result->Raw_Sections.insert(Result->Raw_Sections.end(), r_group.Data.begin(), r_group.Data.end());
	}

	return Result;
}

unsigned long long PE::Get_Relative_Address(unsigned long long address, PE::OBJ_Pile& pile, string File_Origin){
	//we can achieve this by removing the current offset value and comparing the difference.
	//Also remove the small header.
	unsigned long long Offset_Difference = address - (offsetof(Header, Header::Characteristics) + sizeof(Header::Characteristics));

	//remove all other values from the offset from the obj
	unsigned long long Sections_Size = 0;

	for (auto& i : pile.Sections){
		if (i.File_Origin == File_Origin){
			Sections_Size = i.Data.size() * sizeof(Section);
		}
	}

	unsigned long long Symbols_Size = 0;

	for (auto& i : pile.Symbols){
		if (i.File_Origin == File_Origin){
			Symbols_Size = i.Data.size() * sizeof(Symbol);
		}
	}

	unsigned long long String_Table_Size = 0;

	for (auto& i : pile.String_Table_Size){
		if (i.first == File_Origin){
			String_Table_Size = i.second;
		}
	}

	unsigned long long Relocations_Size = 0;

	for (auto& i : pile.Relocations){
		if (i.File_Origin == File_Origin){
			Relocations_Size = i.Data.size() * sizeof(Relocation);
		}
	}

	//get the section id that the address is part of.
	int Section_ID = 0;
	vector<PE::Section> right_sections;

	for (auto& i : pile.Sections){
		if (i.File_Origin == File_Origin){
			right_sections = i.Data;
			for (int j = 0; j < i.Data.size(); j++){
				if (i.Data[j].Pointer_To_Raw_Data <= address){
					Section_ID = j;
					break;
				}
			}
		}
	}

	//now that we know in what section this address resides in, we can compute the paddings that occur before the sections.
	unsigned long long Overall_Padding = 0;

	unsigned int Current_Offset = (offsetof(Header, Header::Characteristics) + sizeof(Header::Characteristics)) + Sections_Size + Symbols_Size + String_Table_Size + Relocations_Size;

	for (int i = 0; i < Section_ID; i++){

		unsigned Tmp_Padding = ((Current_Offset + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1)) - Current_Offset;

		Current_Offset += right_sections[i].Virtual_Size + Tmp_Padding;
		
		Overall_Padding += Tmp_Padding;
	}

	//Now remove all the gathered offsets from the offset difference.
	Offset_Difference -= Sections_Size + Symbols_Size + String_Table_Size + Relocations_Size + Overall_Padding;

	return Offset_Difference;
}

PE::OBJ_Pile::OBJ_Pile(vector<PE::PE_OBJ*> OBJs){
	this->header = OBJs[0]->Header;

	unsigned long long Current_Additional_Offset = 0;

	//Add the sections to the this
	for (auto i : OBJs){
		this->Sections.insert(this->Sections.end(), Group_Info<Section>{i->File_Name, Current_Additional_Offset, i->Sections});
		Current_Additional_Offset += i->Sections.size() * sizeof(PE::Section);
	}

	//Add the symbols to the this
	for (auto i : OBJs){
		this->Symbols.insert(this->Symbols.end(), Group_Info<Symbol>{i->File_Name, Current_Additional_Offset, i->Symbols});
		Current_Additional_Offset += i->Symbols.size() * sizeof(PE::Symbol);
	}

	//Add the string table to the this
	for (auto i : OBJs){
		this->String_Table.insert(this->String_Table.end(), Group_Info<string>{i->File_Name, Current_Additional_Offset, i->String_Table});
	}

	//Add the string table buffer to the this
	for (auto i : OBJs){
		this->String_Table_Buffer.insert(this->String_Table_Buffer.end(), Group_Info<unsigned char>{i->File_Name, Current_Additional_Offset, i->String_Table_Buffer});
		Current_Additional_Offset += i->String_Table_Size;
	}

	//Add the string table sizes
	for (auto i : OBJs){
		this->String_Table_Size.push_back({i->File_Name, i->String_Table_Size});
	}

	//Add the relocations to the this
	for (auto i : OBJs){
		this->Relocations.insert(this->Relocations.end(), Group_Info<Relocation>{i->File_Name, Current_Additional_Offset, i->Relocations});
		Current_Additional_Offset += i->Relocations.size() * sizeof(PE::Relocation);
	}

	//Add the raw sections to the this
	for (auto i : OBJs){
		this->Raw_Sections.insert(this->Raw_Sections.end(), Group_Info<Raw_Section>{i->File_Name, Current_Additional_Offset, i->Raw_Sections});
		
		for (auto& j : i->Raw_Sections){
			Current_Additional_Offset += j.Data.size();
		}
	}
}

//This function takes a files contant and disects it into a PE OBJ object
PE::PE_OBJ::PE_OBJ(vector<unsigned char> File, string File_Name){

	this->File_Name = File_Name;

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
		section.Section_Address = Current_Offset;

		Current_Offset += i.Size_Of_Raw_Data;

		this->Raw_Sections.push_back(section);
	}

	Add_Padding_To_Offsets(*this);
}

vector<PE::Section> PE::Generate_Section_Table(vector<Byte_Map_Section*> Input, unsigned long long Origo, PE::PE_OBJ* obj){

	vector<PE::Section> Result;

	//Remove the optional headers from the buffer
	unsigned char* Header_Start_Address = (unsigned char*)&obj->Header;
	unsigned char* Header_End_Address = (unsigned char*)&obj->Header.Characteristics + sizeof(obj->Header.Characteristics);

	unsigned int Current_Offset = Origo;

	for (auto i : Input){

		unsigned long long Padding = ((Current_Offset + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1)) - Current_Offset;

		Section tmp;
		 memcpy(&tmp.Name, i->Name.data(), i->Name.size());
		 tmp.Virtual_Size = i->Calculated_Size;
		 tmp.Virtual_Address = Padding + Current_Offset;
		 tmp.Size_Of_Raw_Data = ((i->Calculated_Size + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1));
		 tmp.Pointer_To_Raw_Data = Padding + Current_Offset;
		 tmp.Pointer_To_Relocations =  Header_End_Address - Header_Start_Address + sizeof(PE::Section) * Input.size() + sizeof(PE::Symbol) * obj->Header.Number_Of_Symbols + obj->String_Table_Size;
		 tmp.Pointer_To_Line_Numbers = 0;
		 tmp.Number_Of_Relocations = obj->Relocations.size();
		 tmp.Number_Of_Line_Numbers = 0;

		if (i->Is_Data_Section){
			tmp.Characteristics = _IMAGE_SCN_CNT_INITIALIZED_DATA | _IMAGE_SCN_MEM_READ | _IMAGE_SCN_MEM_WRITE;
		}
		else{
			tmp.Characteristics = _IMAGE_SCN_CNT_CODE | _IMAGE_SCN_MEM_EXECUTE | _IMAGE_SCN_MEM_READ;
		}

		tmp.Characteristics |= _IMAGE_SCN_ALIGN_512BYTES;

		Result.push_back(tmp);

		Current_Offset += Padding + tmp.Virtual_Size;
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

		Current.Value = i.second.Address;
		Current.Section_Number = i.second.Section_ID;
		Current.Type = 0;

		if (i.second.Origin && i.second.Origin->is("export")){
			Current.Storage_Class = _IMAGE_SYM_CLASS_EXTERNAL;
		}
		else if (i.second.Origin && i.second.Origin->is("import")){
			Current.Storage_Class = _IMAGE_SYM_CLASS_EXTERNAL;
			Current.Section_Number = 0;
		}
		else{
			Current.Storage_Class = _IMAGE_SYM_CLASS_LABEL;
		}
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

	int String_Table_Size_Identifier_Size = 4;
	unsigned int Clean_Name_Offset = (Full_Name >> 32) - 4;

	for (unsigned int i = Clean_Name_Offset; i < String_Table.size(); i++){

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