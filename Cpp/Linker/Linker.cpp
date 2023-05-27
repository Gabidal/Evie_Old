#include "../../H/Linker/Linker.h"
#include "../../H/Nodes/Node.h"
#include "../../H/BackEnd/Selector.h"

#include "../../H/UI/Safe.h"

#include "../../H/UI/Usr.h"

extern Usr* sys;
extern Selector* selector;

#include <time.h>

void Linker::En_Large_PE_Header(PE::PE_OBJ* obj){

   //Get the stating address
    Node* Starting_Function = sys->Info.Starting_Address;

    unsigned long long Code_Size = 0;
    unsigned long long Data_Size = 0;

    unsigned int Code_Starting_Address = 0;
    unsigned int Data_Starting_Address = 0;

    unsigned long long Image_Size = 0;

    unsigned long long Text_Name = 0;
    unsigned long long Data_Name = 0;

    memcpy(&Text_Name, ".text", 5);
    memcpy(&Data_Name, ".data", 5);

    for (auto& i : obj->Sections){
        if (i.Name == Text_Name){
            Code_Size = i.Size_Of_Raw_Data;
            Code_Starting_Address = i.Pointer_To_Raw_Data;
        }
        else if (i.Name == Data_Name){
            Data_Size = i.Size_Of_Raw_Data;
            Data_Starting_Address = i.Pointer_To_Raw_Data;
        }

        Image_Size += i.Size_Of_Raw_Data;
    }

    //The final value of the image size is the multiple of alignments
    Image_Size = (Image_Size + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    
    obj->Header.Magic = PE::MAGIC_NUMBER;
    obj->Header.Linker_Version = 0;

    obj->Header.Size_Of_Code = (Code_Size + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    
    obj->Header.Size_Of_Initialized_Data = (Data_Size + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    obj->Header.Size_Of_Uninitialized_Data = 0;
    obj->Header.Base_Of_Code = Code_Starting_Address;

    obj->Header.Image_Base = PE::_WINDOWS_PE_EXE_BASE_IMAGE;
    obj->Header.Section_Alignment = PE::_SECTION_ALIGNMENT;
    obj->Header.File_Alignment = PE::_FILE_ALIGNMENT;
    obj->Header.Operating_System_Version = PE::_IMAGE_OS_VERSION;
    obj->Header.Image_Version = 0;
    obj->Header.Subsystem_Version = PE::_IMAGE_SUBSYSTEM_VERSION;
    obj->Header.Win32_Version_Value = 0;
    obj->Header.Size_Of_Image = Image_Size;
 
    //Update
 
    Linker::Add_Export_Table(obj, 0);       //Sections(text, data) + (export, import, base)
    Linker::Add_Import_Table(obj, 0);       //Sections(text, data, export) + (import, base)
    Linker::Add_Import_Address_Table(obj);  //Sections(text, data, export, import, base)

    Linker::Update_Obj_Headers(obj);

    //Clear redundant sections.

    unsigned long long Import_Name = 0;
    memcpy(&Import_Name, ".idata", 6);

    unsigned long long Export_Name = 0;
    memcpy(&Export_Name, ".edata", 6);
    
    unsigned long long Reloc_Name = 0;
    memcpy(&Reloc_Name, ".reloc", 6);

    for (int i = 0; i < obj->Sections.size(); i++){
        if (obj->Sections[i].Name == Import_Name || obj->Sections[i].Name == Export_Name || obj->Sections[i].Name == Reloc_Name){
            obj->Sections.erase(obj->Sections.begin() + i--);
        }
    }

    //(.text, .data) + .edata + i.data
    int Potential_Section_Count = obj->Sections.size() + 1 + 1;

    Linker::Add_Export_Table(obj, Potential_Section_Count);       //Sections(text, data) + (export, import, base)
    Linker::Add_Import_Table(obj, Potential_Section_Count);       //Sections(text, data, export) + (import, base)
    Linker::Add_Import_Address_Table(obj);  //Sections(text, data, export, import, base)
    
    obj->Header.Size_Of_Headers = sizeof(PE::Header) + sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Section) * obj->Sections.size();
    obj->Header.Size_Of_Headers += ((obj->Header.Size_Of_Headers + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1)) - obj->Header.Size_Of_Headers;
    obj->Header.Check_Sum = 0;
    obj->Header.Subsystem = PE::_IMAGE_SUBSYSTEM_WINDOWS_CUI;
    obj->Header.Dll_Characteristics = 0;
    obj->Header.Size_Of_Stack_Reserve = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Stack_Commit = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Heap_Reserve = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Heap_Commit = PE::_BUCKET_SIZE;
    obj->Header.Number_Of_Rva_And_Sizes = PE::_OPTIONAL_HEADER_DATA_DIRECTORIES_AMOUNT;

    for (auto& s : obj->Sections){

        obj->Header.Size_Of_Image += s.Size_Of_Raw_Data;

    }
    
    obj->Header.Size_Of_Image = (obj->Header.Size_Of_Image + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    unsigned char Optional = 0;

    if (!sys->Info.Debug){

        Optional = PE::_IMAGE_FILE_DEBUG_STRIPPED;

    }

    //Update the non optional headers.
    obj->Header.Machine = PE::_IMAGE_FILE_MACHINE_AMD64;
    obj->Header.Number_Of_Sections = obj->Sections.size();
    obj->Header.Date_Time = time_t(time(NULL));
    obj->Header.Pointer_To_Symbol_Table = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header) + obj->Sections.size() * sizeof(PE::Section);
    obj->Header.Number_Of_Symbols = obj->Symbols.size();
    obj->Header.Size_Of_Optional_Header = (sizeof(PE::Header))- (offsetof(PE::Header, PE::Header::Characteristics) + sizeof(PE::Header::Characteristics));
    obj->Header.Characteristics = PE::_IMAGE_FILE_EXECUTABLE_IMAGE | PE::_IMAGE_FILE_LARGE_ADDRESS_AWARE | PE::_IMAGE_FILE_DEBUG_STRIPPED | PE::_IMAGE_FILE_LINE_NUMS_STRIPPED | PE::_IMAGE_FILE_RELOCS_STRIPPED;

    //Now find this function name from the symbol table
    for (auto& i : obj->Symbols){
        if (i.Get_Name(obj->String_Table_Buffer) == Starting_Function->Mangled_Name){
            obj->Header.Address_Of_Entry_Point = i.Value + obj->Sections[i.Section_Number - 1].Virtual_Address;
            break;
        }
    }
}

void Linker::Update_Obj_Headers(PE::PE_OBJ* obj){
    //Gather all RVA's from symbols and sections of sorts, calculate the new adddresses and then compare the difference and that to the old addreses.

    vector<PE::Section*> Section_RVA;
    for (int i = 0; i < obj->Sections.size(); i++){
        Section_RVA.push_back(&obj->Sections[i]);
    }

    //Now start calculating the new offset of origo.

    unsigned int New_Origo = 0;

    New_Origo += sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header) + obj->Sections.size() * sizeof(PE::Section) + obj->Symbols.size() * sizeof(PE::Symbol) + obj->String_Table_Size;

    //Now start calculating the padding for the first section.

    unsigned int Current_Offset = New_Origo;

    for (int i = 0; i < Section_RVA.size(); i++){
	    unsigned Tmp_Padding = ((Current_Offset + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1)) - Current_Offset;

        Section_RVA[i]->Pointer_To_Raw_Data = Current_Offset + Tmp_Padding;
        Section_RVA[i]->Virtual_Address = Current_Offset + Tmp_Padding;
        
		Current_Offset += obj->Sections[i].Size_Of_Raw_Data + Tmp_Padding;

        Section_RVA[i]->Pointer_To_Relocations = 0;
        Section_RVA[i]->Number_Of_Relocations = 0;
    }

}

//SUPER DUPER PRECISE RELOCATRON 2500 !!!
void Linker::Inline_Relocations(PE::PE_OBJ* obj){
    if (obj->Raw_Sections.size() == 0){

        Report(Observation(ERROR, "Expected liquefied obj structure, got IR OBJ.", LINKER_INTERNAL));

    }

    unsigned long long Origo = obj->Header.Size_Of_Headers;

    for (auto rel : obj->Relocations){
        unsigned long long Current_Code_Address = rel.Virtual_Address;
        PE::Symbol Address_To_Write = obj->Symbols[rel.Symbol_Table_Index];
        long long Symbol_Address = Address_To_Write.Value;
        string Relocation_Name = Address_To_Write.Get_Name(obj->String_Table_Buffer);


        // Determine the size of the writable area.
        int Value_Size = 4;

        if (rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_ADDR64)
            Value_Size = 8;

        // Find the current section where the relocation wants to write to:
        PE::Raw_Section* Destination_Section = &obj->Raw_Sections[0];
        for (auto &i : obj->Raw_Sections){
            if (Current_Code_Address >= i.Section_Address && Current_Code_Address < i.Section_Address + i.Data.size()){
                Destination_Section = &i;
                break;
            }
        }

        if (rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_ADDR64 || rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_ADDR32){
            // Inline AND feed-forward to BASE RELOCATION TABLE.
            // Primarily used for .DATA section instances.
            // int OFFSETTER = (int)PE::IMAGE_REL_AMD64::REL_AMD64_REL32 + ((int)PE::IMAGE_REL_AMD64::REL_AMD64_REL32 * (rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_ADDR64));

            // Symbol_Address -= OFFSETTER;
        }
        else if (
            rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_REL32   || 
            rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_REL32_1 ||
            rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_REL32_2 || 
            rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_REL32_3 || 
            rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_REL32_4 || 
            rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_REL32_5
        ){
            // Inline relative addresses, primarily for JMP's and CALLS.
            // we need to offset the address of the Symbol_Address by the bits size of the OFFSETTER.
            int OFFSETTER = (int)rel.Type - (int)PE::IMAGE_REL_AMD64::REL_AMD64_REL32;

            Symbol_Address -= OFFSETTER;
        }
        else if (rel.Type == (int)PE::IMAGE_REL_AMD64::REL_AMD64_SECREL7){
            // Primarily used for debug information.
        }

        // This is where we are going to write the data to.
        unsigned int Relative_Code_Address = Current_Code_Address - Destination_Section->Section_Address;

        if (Current_Code_Address < Destination_Section->Section_Address){
            Report(Observation(ERROR, "Virtual address of: '" + Relocation_Name + "' at: '" + to_string(Current_Code_Address) + "' is lower than the section virtual address of: '" + to_string(Destination_Section->Section_Address) + "'.", LINKER_INTERNAL));
        }

        PE::Raw_Section* Origin_Section = &obj->Raw_Sections[Address_To_Write.Section_Number - 1];
        int Sectional_Padding = 0;

        // if the current section and the relocation origin section isn't the same then we need to take into the consideration the address differentiation.
        if (Origin_Section->Name != Destination_Section->Name){
            // Calculate the difference between the two sections.
            Sectional_Padding = Origin_Section->Section_Address - Current_Code_Address;

            // now add the sectional padding to the symbol address.
            Symbol_Address += Sectional_Padding;
        }

        // Now write the address
        unsigned char* Src = (unsigned char*)&Symbol_Address; 
        unsigned char* Dst = (unsigned char*)&Destination_Section->Data[Relative_Code_Address];

        int Carry_Flag = 0;

        for (int i = 0; i < Value_Size; i++){
            int Value = (int)Src[i] + (int)Carry_Flag + (int)Dst[i];

            Dst[i] += Src[i] + Carry_Flag;

            // check if the src + dst triggers the carry flag
            Carry_Flag = Value >> 8;
        }
    }

}

vector<unsigned char> Linker::Write_PE_Executable(PE::PE_OBJ* obj){
    vector<unsigned char> Buffer;
    PE::Bull_Shit_Headers dos;

    //add DOS bullshittery
    Buffer.insert(Buffer.end(), (unsigned char*)&dos, (unsigned char*)&dos + sizeof(dos));

	Buffer.insert(Buffer.end(), (unsigned char*)&obj->Header, (unsigned char*)&obj->Header + sizeof(PE::Header));

	Buffer.insert(Buffer.end(), (unsigned char*)obj->Sections.data(), (unsigned char*)obj->Sections.data() + sizeof(PE::Section) * obj->Sections.size());

	Buffer.insert(Buffer.end(), (unsigned char*)obj->Symbols.data(), (unsigned char*)obj->Symbols.data() + sizeof(PE::Symbol) * obj->Symbols.size());

	Buffer.insert(Buffer.end(), (unsigned char*)&obj->String_Table_Size, (unsigned char*)&obj->String_Table_Size + sizeof(obj->String_Table_Size));

	Buffer.insert(Buffer.end(), obj->String_Table_Buffer.begin(), obj->String_Table_Buffer.end());

    int Origo = Buffer.size();

    unsigned long long Current_Offset = Origo;

	for (auto i : obj->Content){
        //add padding
        int Padding = ((Current_Offset + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1)) - Current_Offset;

        Buffer.insert(Buffer.end(), Padding, (unsigned char)0);

		for (auto& j : i->Byte_Maps){

			vector<unsigned char> Data = selector->Assemble(j);

			Buffer.insert(Buffer.end(), Data.begin(), Data.end());

            Current_Offset += Data.size() + Padding;
		}
	}

    Write_Export_Table(obj, Buffer);
    Write_Import_Table(obj, Buffer);
    Write_Import_Address_Table(obj, Buffer);

	//transform the 
	return Buffer;
}

void Linker::Add_Export_Table(PE::PE_OBJ* obj, int expected_section_count){
    int Origo = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header) + sizeof(PE::Section) * expected_section_count + sizeof(PE::Symbol) * obj->Symbols.size() + obj->String_Table_Size;

    int Start_Of_Code = (Origo + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    int Start_Of_data = (Start_Of_Code + obj->Header.Size_Of_Code + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    int Start_Of_Export_Table = (Start_Of_data + obj->Header.Size_Of_Initialized_Data + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    Origo = Start_Of_Export_Table;

    //First we need to gather all the exporting functions
    vector<PE::Symbol> Exported_Functions;

    for (auto& s : obj->Symbols)
        if (s.Storage_Class == PE::_IMAGE_SYM_CLASS_EXTERNAL && s.Section_Number != 0)
            Exported_Functions.push_back(s);

    //Now we sort the names alphabetically
    sort(Exported_Functions.begin(), Exported_Functions.end(), [&](PE::Symbol& a, PE::Symbol& b){
        return a.Get_Name(obj->String_Table_Buffer) < b.Get_Name(obj->String_Table_Buffer);
    });

    PE::Export_Table Table;

    unsigned int Current_RVA = Origo + sizeof(PE::Export_Directory) + sizeof(PE::Export_Address_Table) * Exported_Functions.size() + sizeof(unsigned int) * Exported_Functions.size() + sizeof(unsigned short) * Exported_Functions.size();

    int Ordinal = 0;
    for (auto& s : Exported_Functions){
        PE::Export_Address_Table Entry;

        //Get the s's section number and with that get the sections starting address
        Entry.Address = obj->Sections[s.Section_Number - 1].Virtual_Address + s.Value;

        //Also add the symbol name to the name list, for later on to calculate
        //the RVA of the symbol name address.
        Table.Name_Table.push_back(s.Get_Name(obj->String_Table_Buffer));

        Table.Size_Of_Name_Table += s.Get_Name(obj->String_Table_Buffer).size() + 1;

        //also add name pointte table
        Table.Name_Address_Table.push_back(Current_RVA);

        Table.Ordinal_Table.push_back(Ordinal++);

        //Update RVA
        Current_RVA += s.Get_Name(obj->String_Table_Buffer).size() + 1;

        Table.Address_Table.push_back(Entry);
    }

    obj->Header.Export_Table = Origo;
    obj->Header.Size_Of_Export_Table = sizeof(PE::Export_Directory) + sizeof(PE::Export_Address_Table) * Exported_Functions.size() + sizeof(unsigned int) * Table.Name_Address_Table.size() + sizeof(unsigned short) * Table.Ordinal_Table.size() + Table.Size_Of_Name_Table;

    Table.Directory.Export_Flags = 0;
    Table.Directory.Time_Date_Stamp = time_t(time(NULL));
    Table.Directory.Major_Version = 0;
    Table.Directory.Minor_Version = 0;
    Table.Directory.DLL_Name_RVA = 0;
    Table.Directory.Ordinal_Base = 1;
    Table.Directory.Address_Table_Entries = Exported_Functions.size();
    Table.Directory.Number_Of_Name_Entries = Exported_Functions.size();
    Table.Directory.Export_Address_Table_RVA = obj->Header.Export_Table + sizeof(PE::Export_Directory);
    Table.Directory.Ordinal_Table_RVA = obj->Header.Export_Table + sizeof(PE::Export_Directory) + sizeof(PE::Export_Address_Table) * Exported_Functions.size() + sizeof(unsigned int) * Table.Name_Address_Table.size();
    Table.Directory.Name_Pointer_RVA = obj->Header.Export_Table + sizeof(PE::Export_Directory) + sizeof(PE::Export_Address_Table) * Exported_Functions.size();

    obj->Exports = Table;

    //Also add the export table to the section table
    PE::Section Section;
    
    memcpy(&Section.Name, ".edata", 6);
    Section.Virtual_Address = Origo;
    Section.Virtual_Size = obj->Header.Size_Of_Export_Table;
    Section.Size_Of_Raw_Data = ((obj->Header.Size_Of_Export_Table + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1));
    Section.Pointer_To_Raw_Data = Origo;
    Section.Characteristics = PE::_IMAGE_SCN_CNT_INITIALIZED_DATA | PE::_IMAGE_SCN_MEM_READ | PE::_IMAGE_SCN_MEM_WRITE | PE::_IMAGE_SCN_ALIGN_512BYTES;

    obj->Sections.push_back(Section);
}

void Linker::Add_Import_Table(PE::PE_OBJ* obj, int expected_section_count){
    //                                                                           + export section table
    int Origo = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header) + sizeof(PE::Section) * expected_section_count + sizeof(PE::Symbol) * obj->Symbols.size() + obj->String_Table_Size;

    int Start_Of_Code = (Origo + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    int Start_Of_Data = (Start_Of_Code + obj->Header.Size_Of_Code + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    int Start_Of_Export_Table = (Start_Of_Data + obj->Header.Size_Of_Initialized_Data + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    int Start_Of_Import_Table = (Start_Of_Export_Table + obj->Header.Size_Of_Export_Table + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    Origo = Start_Of_Import_Table;

    vector<PE::Symbol> Imported_Functions;

    for (auto& s : obj->Symbols)
        if (s.Storage_Class == PE::_IMAGE_SYM_CLASS_EXTERNAL && s.Section_Number == 0)
            Imported_Functions.push_back(s);

    PE::Import_Table Table;

    Table.Directory.Lookup_Table_RVA = Origo + sizeof(PE::Import_Directory) + sizeof(PE::Import_Table::Null_Directory_Table);
    //Table.Directory.Time_Date_Stamp = time_t(time(NULL));
    Table.Directory.Forwarder_Chain = 0;
    Table.Directory.DLL_Name = 0;

    unsigned int Current_RVA_For_Look_Up_Table = Table.Directory.Lookup_Table_RVA;
    unsigned int Current_RVA_For_Hints = Origo + sizeof(PE::Import_Directory) + sizeof(PE::Import_Table::Null_Directory_Table) + sizeof(PE::Import_Lookup) * Imported_Functions.size() + sizeof(PE::Import_Table::Null_Lookup_Table);
    for (auto& s : Imported_Functions){
        PE::Import_Lookup Lookup;

        Lookup.Name_Address = Current_RVA_For_Look_Up_Table;

        Table.Lookup_Table.push_back(Lookup);

        PE::Hint hint;
        hint.Name = s.Get_Name(obj->String_Table_Buffer);

        if ((hint.Name.size() + 1) % 2 != 0)
            hint.Padding = true;

        hint.Hint_Name_Size = hint.Name.size() + hint.Padding;

        Table.Hint_Table.push_back(hint);

        Current_RVA_For_Look_Up_Table += sizeof(PE::Import_Lookup);
    }

    unsigned int Hint_Name_Size = 0;

    for (auto& s : Table.Hint_Table){
        Hint_Name_Size += s.Hint_Name_Size;
    }

    obj->Header.Import_Table = Origo;
    //                            ->                              ->                               ->                         Hint table index * hint count + hint name size + null terminator * hint count
    obj->Header.Size_Of_Import_Table = sizeof(PE::Import_Table::Directory) + sizeof(PE::Import_Table::Null_Directory_Table) + sizeof(PE::Import_Lookup) * Imported_Functions.size() + sizeof(PE::Import_Table::Null_Lookup_Table) + (sizeof(short) * Imported_Functions.size() + Hint_Name_Size);

    //Add import address table size
    obj->Header.Size_Of_Import_Table += sizeof(PE::Import_Lookup) * Imported_Functions.size();

    Table.Directory.Import_Address_Table_RVA = obj->Header.Import_Table + obj->Header.Size_Of_Import_Table - obj->Header.Size_Of_Import_Address_Table;

    obj->Imports = Table;

    //Also add the import table to the section table
    PE::Section Section;
    
    memcpy(&Section.Name, ".idata", 6);
    Section.Virtual_Address = Origo;
    Section.Virtual_Size = obj->Header.Size_Of_Import_Table;
    Section.Size_Of_Raw_Data = ((obj->Header.Size_Of_Import_Table + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1));
    Section.Pointer_To_Raw_Data = Origo;
    Section.Characteristics = PE::_IMAGE_SCN_CNT_INITIALIZED_DATA | PE::_IMAGE_SCN_MEM_READ | PE::_IMAGE_SCN_MEM_WRITE | PE::_IMAGE_SCN_ALIGN_512BYTES;

    obj->Sections.push_back(Section);
}

void Linker::Add_Import_Address_Table(PE::PE_OBJ* obj){
    if (obj->Imports.Lookup_Table.size() == 0)
        return;

    int Origo = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header) + sizeof(PE::Section) * obj->Sections.size() + sizeof(PE::Symbol) * obj->Symbols.size() + obj->String_Table_Size;

    int Start_Of_Code = (Origo + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    
    obj->Header.Size_Of_Import_Address_Table = sizeof(PE::Import_Lookup) * obj->Imports.Lookup_Table.size();

    int Start_Of_data = (Start_Of_Code + obj->Header.Size_Of_Code + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    int Start_Of_Export_Table = (Start_Of_data + obj->Header.Size_Of_Initialized_Data + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    int Start_Of_Import_Table = (Start_Of_Export_Table + obj->Header.Size_Of_Export_Table + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    //Because Import address table is contained inside of the import tables tail, we will, need to substract the size of the import address table from import table.
    int Start_Of_Import_Address_Table = Start_Of_Import_Table + (obj->Header.Size_Of_Import_Table - obj->Header.Size_Of_Import_Address_Table);

    Origo = Start_Of_Import_Address_Table;

    obj->Import_Address_Table.resize(obj->Imports.Lookup_Table.size());

    memcpy(obj->Import_Address_Table.data(), obj->Imports.Lookup_Table.data(), sizeof(PE::Import_Lookup) * obj->Imports.Lookup_Table.size());

    obj->Header.Import_Address_Table = Origo;
}

void Linker::Write_Import_Address_Table(PE::PE_OBJ* obj, vector<unsigned char>& Buffer){
    if (obj->Import_Address_Table.size() == 0)
        return;

    Buffer.insert(Buffer.end(), (unsigned char*)&obj->Import_Address_Table[0], (unsigned char*)&obj->Import_Address_Table[0] + sizeof(PE::Import_Lookup) * obj->Import_Address_Table.size());
}

void Linker::Write_Export_Table(PE::PE_OBJ* obj, vector<unsigned char>& Buffer){

    //add padding
    int Padding = ((Buffer.size() + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1)) - Buffer.size();
    Buffer.insert(Buffer.end(), Padding, 0);

    Buffer.insert(Buffer.end(), (unsigned char*)&obj->Exports.Directory, (unsigned char*)&obj->Exports.Directory + sizeof(PE::Export_Directory));

    if (obj->Exports.Address_Table.size() > 0)
        Buffer.insert(Buffer.end(), (unsigned char*)&obj->Exports.Address_Table[0], (unsigned char*)&obj->Exports.Address_Table[0] + sizeof(PE::Export_Address_Table) * obj->Exports.Address_Table.size());

    if (obj->Exports.Name_Address_Table.size() > 0)
        Buffer.insert(Buffer.end(), (unsigned char*)&obj->Exports.Name_Address_Table[0], (unsigned char*)&obj->Exports.Name_Address_Table[0] + sizeof(unsigned int) * obj->Exports.Name_Address_Table.size());
    
    if (obj->Exports.Ordinal_Table.size() > 0)
        Buffer.insert(Buffer.end(), (unsigned char*)&obj->Exports.Ordinal_Table[0], (unsigned char*)&obj->Exports.Ordinal_Table[0] + sizeof(unsigned short) * obj->Exports.Ordinal_Table.size());

    for (auto& s : obj->Exports.Name_Table){
        Buffer.insert(Buffer.end(), (unsigned char*)s.data(), (unsigned char*)s.data() + s.size());
        Buffer.push_back(0);
    }
}

void Linker::Write_Import_Table(PE::PE_OBJ* obj, vector<unsigned char>& Buffer){
    //add padding
    int Padding = ((Buffer.size() + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1)) - Buffer.size();
    Buffer.insert(Buffer.end(), Padding, 0);

    Buffer.insert(Buffer.end(), (unsigned char*)&obj->Imports.Directory, (unsigned char*)&obj->Imports.Directory + sizeof(PE::Import_Table::Directory));
    
    Buffer.insert(Buffer.end(), (unsigned char*)&obj->Imports.Null_Directory_Table, (unsigned char*)&obj->Imports.Null_Directory_Table + sizeof(PE::Import_Table::Null_Directory_Table));

    if (obj->Imports.Lookup_Table.size() > 0)
        Buffer.insert(Buffer.end(), (unsigned char*)&obj->Imports.Lookup_Table[0], (unsigned char*)&obj->Imports.Lookup_Table[0] + sizeof(PE::Import_Lookup) * obj->Imports.Lookup_Table.size());
    
    Buffer.insert(Buffer.end(), sizeof(obj->Imports.Null_Lookup_Table), 0);
    
    for (auto& h : obj->Imports.Hint_Table){

        Buffer.insert(Buffer.end(), (unsigned char*)&h, (unsigned char*)&h + sizeof(short));

        Buffer.insert(Buffer.end(), (unsigned char*)&h.Name[0], (unsigned char*)&h.Name[0] + h.Name.size());

        if (h.Padding)
            Buffer.push_back(0);
    }
}

PE::Export_Table* Linker::Read_Export_Table(PE::Section& s, vector<unsigned char>& Buffer){

    PE::Export_Table* Result = new PE::Export_Table;

    unsigned int Current_Offset = s.Virtual_Address;

    Result->Directory = *(PE::Export_Directory*)&Buffer[Current_Offset];

    Current_Offset += sizeof(PE::Export_Directory);

    for (int i = 0; i < Result->Directory.Address_Table_Entries; i++){
        Result->Address_Table.push_back(*(PE::Export_Address_Table*)&Buffer[Current_Offset]);

        Current_Offset += sizeof(PE::Export_Address_Table);
    }

    for (int i = 0; i < Result->Directory.Address_Table_Entries; i++){
        Result->Name_Address_Table.push_back(*(unsigned int*)&Buffer[Current_Offset]);

        Current_Offset += sizeof(unsigned int);
    }

    for (int i = 0; i < Result->Directory.Address_Table_Entries; i++){
        Result->Ordinal_Table.push_back(*(unsigned short*)&Buffer[Current_Offset]);

        Current_Offset += sizeof(unsigned short);
    }

    for (int i = 0; i < Result->Directory.Address_Table_Entries; i++){
        vector<char> Name;

        while (Buffer[Current_Offset] != 0){
            Name.push_back(Buffer[Current_Offset]);
            Current_Offset++;
        }
        Current_Offset++;
        Result->Name_Table.push_back(string(Name.data(), Name.size()));
    }

    return Result;
}

