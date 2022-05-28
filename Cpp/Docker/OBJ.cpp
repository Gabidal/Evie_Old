#include "../../H/Docker/OBJ.h"

#include "../../H/BackEnd/Selector.h"
#include "../../H/Nodes/Node.h"
#include "../../H/Assembler/Assembler_Types.h"
#include "../../H/UI/Usr.h"
#include "../../H/UI/Safe.h"
#include "../../H/Assembler/Assembler.h"

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
		if (S.Name.Name_Header == 0) {
			string Name = "";
			for (int i = *(int*)S.Name.Name_Offset; i < buffer.size(); i++) {
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

string OBJ::Create_Obj(vector<Byte_Map_Section*> Input){
	Header header;
	header.Machine = selector->OBJ_Machine_ID;
	header.Number_OF_Sections = Input.size();
	header.Date_Time = time_t(time(NULL));
	header.Pointer_To_Symbol_Table = sizeof(Header) + sizeof(Section) * Input.size();

	//calculate the exports and import functions from global scope
	for (auto s : Global_Scope->Childs){
		if (s->Has(vector<string>{"export", "import"}) > 0){
			header.Number_Of_Symbols++;
		}
	}

	header.Size_Of_Optional_Header = 0;
	header.Characteristics = IMAGE_FILE_LARGE_ADDRESS_AWARE;

	header.Magic = MAGIC_PE32_PlUS;
	header.Linker_Version = 0x0000;

	for (auto i : Input){
		header.Size_Of_Code += i->Calculated_Size;
	}

	for (auto i : Input){
		if (i->Is_Data_Section)
			header.Size_Of_Initialized_Data += i->Calculated_Size;
	}

	header.Size_Of_Uninitialized_Data = 0;

	if (sys->Info.Format == "lib"){
		header.Address_Of_Entry_Point = 0;
	}
	else{
		string Unmangled_Starting_Function_Name = sys->Info.Start_Function_Name;
		Node* Function = Global_Scope->Find(Unmangled_Starting_Function_Name, Global_Scope, FUNCTION_NODE);

		if (Function == nullptr){
			Report(Observation(ERROR, "Function " + Unmangled_Starting_Function_Name + " not found in the global scope", LINKER_MISSING_STARTING_FUNCTION));
			return "";
		}

		string Mangled_Starting_Function_Name = Function->Mangled_Name;

		header.Address_Of_Entry_Point = assembler->Symbol_Table.at(Mangled_Starting_Function_Name);
	}

	return "";

}