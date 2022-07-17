#include "../../H/Linker/Linker.h"
#include "../../H/Nodes/Node.h"
#include "../../H/BackEnd/Selector.h"

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

    for (auto& i : obj->Content){
        if (!i->Is_Data_Section){

            Code_Size += i->Calculated_Size;
            Code_Starting_Address = i->Calculated_Address;

        }
        else{

            Data_Size += i->Calculated_Size;
            Data_Starting_Address = i->Calculated_Address;

        }

        Image_Size += i->Calculated_Size;
    }

    //The final value of the image size is the multiple of alignments
    Image_Size = (Image_Size + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    
    obj->Header.Size_Of_Code = Code_Size;
    obj->Header.Size_Of_Initialized_Data = Data_Size;

    Add_Export_Table(obj, 2);
    Add_Import_Table(obj, 1);

    unsigned char Optional = 0;

    if (sys->Info.Debug){

        Optional = PE::_IMAGE_FILE_DEBUG_STRIPPED;

    }

    obj->Header.Machine = PE::_IMAGE_FILE_MACHINE_AMD64;
    obj->Header.Number_Of_Sections = obj->Sections.size();
    obj->Header.Pointer_To_Symbol_Table = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header) + obj->Sections.size() * sizeof(PE::Section);
    obj->Header.Size_Of_Optional_Header = (sizeof(PE::Header)) - (offsetof(PE::Header, PE::Header::Characteristics) + sizeof(PE::Header::Characteristics));
    obj->Header.Characteristics = PE::_IMAGE_FILE_EXECUTABLE_IMAGE | PE::_IMAGE_FILE_LARGE_ADDRESS_AWARE | Optional;
    obj->Header.Date_Time = time_t(time(NULL));
    obj->Header.Magic = PE::MAGIC_NUMBER;
    obj->Header.Linker_Version = 0;
    obj->Header.Size_Of_Uninitialized_Data = 0;
    obj->Header.Base_Of_Code = Code_Starting_Address;
    //obj->Header.Base_Of_Data = Data_Starting_Address;
    obj->Header.Image_Base = PE::_WINDOWS_PE_EXE_BASE_IMAGE;
    obj->Header.Section_Alignment = PE::_SECTION_ALIGNMENT;
    obj->Header.File_Alignment = PE::_FILE_ALIGNMENT;
    obj->Header.Operating_System_Version = PE::_IMAGE_OS_VERSION;
    obj->Header.Image_Version = 0;
    obj->Header.Subsystem_Version = PE::_IMAGE_SUBSYSTEM_VERSION;
    obj->Header.Win32_Version_Value = 0;
    obj->Header.Size_Of_Image = Image_Size;
    obj->Header.Size_Of_Headers = sizeof(PE::Header);
    obj->Header.Check_Sum = 0;
    obj->Header.Subsystem = PE::_IMAGE_SUBSYSTEM_WINDOWS_CUI;
    obj->Header.Dll_Characteristics = 0;
    obj->Header.Size_Of_Stack_Reserve = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Stack_Commit = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Heap_Reserve = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Heap_Commit = PE::_BUCKET_SIZE;

    //Now we need to add the export and import tables
    obj->Header.Number_Of_Rva_And_Sizes = 2;
    
    Update_Obj_Headers(obj);

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
        
		Current_Offset += obj->Sections[i].Virtual_Size + Tmp_Padding;
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

	//transform the 
	return Buffer;
}

void Linker::Add_Export_Table(PE::PE_OBJ* obj, int expected_section_count){
    int Origo = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header) + sizeof(PE::Section) * (obj->Sections.size() + expected_section_count) + sizeof(PE::Symbol) * obj->Symbols.size() + obj->String_Table_Size;

    int Start_Of_Code = (Origo + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    int Start_Of_data = (Start_Of_Code + obj->Header.Size_Of_Code + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    int Start_Of_Export_Table = (Start_Of_data + obj->Header.Size_Of_Initialized_Data + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);;

    Origo = Start_Of_Export_Table;

    //First we need to gather all the exporting functions
    vector<PE::Symbol> Exported_Functions;

    for (auto& s : obj->Symbols)
        if (s.Storage_Class == PE::_IMAGE_SYM_CLASS_EXTERNAL)
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

        Entry.Address = s.Value;

        Entry.Name_Address = Current_RVA;

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
    obj->Header.Size_Of_Export_Table = sizeof(PE::Export_Directory) + sizeof(PE::Export_Address_Table) * Exported_Functions.size() + sizeof(PE::Export_Table::Name_Address_Table) * Table.Name_Address_Table.size() + sizeof(PE::Export_Table::Ordinal_Table) * Table.Ordinal_Table.size() + Table.Size_Of_Name_Table;

    Table.Directory.Time_Date_Stamp = 0;//time_t(time(NULL));
    Table.Directory.Major_Version = 0;
    Table.Directory.Minor_Version = 0;
    Table.Directory.DLL_Name_RVA = 0;
    Table.Directory.Ordinal_Base = 0;
    Table.Directory.Address_Table_Entries = Exported_Functions.size();
    Table.Directory.Number_Of_Name_Entries = Exported_Functions.size();
    Table.Directory.Export_Address_Table_RVA = obj->Header.Image_Base + Origo + sizeof(PE::Export_Directory);
    Table.Directory.Ordinal_Table_RVA = obj->Header.Export_Table + sizeof(PE::Export_Directory) + sizeof(PE::Export_Address_Table) * Exported_Functions.size() + sizeof(PE::Export_Table::Name_Address_Table) * Table.Name_Address_Table.size();
    Table.Directory.Name_Pointer_RVA = obj->Header.Export_Table + sizeof(PE::Export_Directory) + sizeof(PE::Export_Address_Table) * Exported_Functions.size();

    obj->Exports = Table;

    //Also add the export table to the section table
    PE::Section Section;
    
    memcpy(&Section.Name, ".edata", 6);
    Section.Virtual_Address = Origo;
    Section.Virtual_Size = obj->Header.Size_Of_Export_Table;
    Section.Size_Of_Raw_Data = obj->Header.Size_Of_Export_Table;
    Section.Pointer_To_Raw_Data = Origo;
    Section.Characteristics = PE::_IMAGE_SCN_CNT_INITIALIZED_DATA | PE::_IMAGE_SCN_MEM_READ | PE::_IMAGE_SCN_MEM_WRITE;

    obj->Sections.push_back(Section);
}

void Linker::Add_Import_Table(PE::PE_OBJ* obj, int expected_section_count){
    //                                                                           + export section table
    int Origo = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header) + sizeof(PE::Section) * (obj->Sections.size() + expected_section_count) + sizeof(PE::Symbol) * obj->Symbols.size() + obj->String_Table_Size;

    int Start_Of_Code = (Origo + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    int Start_Of_data = (Start_Of_Code + obj->Header.Size_Of_Code + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    int Start_Of_Export_Table = (Start_Of_data + obj->Header.Size_Of_Initialized_Data + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);;
    int Start_Of_Import_Table = (Start_Of_Export_Table + obj->Header.Size_Of_Export_Table + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);;

    Origo = Start_Of_Import_Table;

    vector<PE::Symbol> Imported_Functions;

    for (auto& s : obj->Symbols)
        if (s.Storage_Class == PE::_IMAGE_SYM_CLASS_EXTERNAL && s.Section_Number == 0)
            Imported_Functions.push_back(s);

    PE::Import_Table Table;

    Table.Directory.Lookup_Table_RVA = Origo + sizeof(PE::Import_Directory) + sizeof(PE::Import_Table::Null_Directory_Table);
    Table.Directory.Time_Date_Stamp = time_t(time(NULL));
    Table.Directory.Forwarder_Chain = 0;
    Table.Directory.DLL_Name = 0;
    Table.Directory.Import_Address_Table_RVA = 0;

    unsigned int Current_RVA = Origo + sizeof(PE::Import_Directory) + sizeof(PE::Import_Table::Null_Directory_Table) + sizeof(PE::Import_Table::Null_Lookup_Table);
    for (auto& s : Imported_Functions){
        PE::Import_Lookup Lookup;

        Lookup.Name_Address = Current_RVA;

        Table.Lookup_Table.push_back(Lookup);

        PE::Hint hint;
        hint.Name = s.Get_Name(obj->String_Table_Buffer);

        if ((hint.Name.size() + 1) % 2 != 0)
            hint.Padding = true;
    }

    unsigned int Hint_Name_Size = 0;

    for (auto& s : Imported_Functions){
        Hint_Name_Size += s.Get_Name(obj->String_Table_Buffer).size() + 1;
    }

    obj->Header.Import_Table = Origo;
    //                            ->                              ->                               ->                         Hint table index * hint count + hint name size + null terminator * hint count
    obj->Header.Size_Of_Import_Table = sizeof(PE::Import_Directory) + sizeof(PE::Import_Lookup) * Imported_Functions.size() + sizeof(short) * Imported_Functions.size() + Hint_Name_Size;

    obj->Imports = Table;

    //Also add the import table to the section table
    PE::Section Section;
    
    memcpy(&Section.Name, ".idata", 6);
    Section.Virtual_Address = Origo;
    Section.Virtual_Size = obj->Header.Size_Of_Export_Table;
    Section.Size_Of_Raw_Data = obj->Header.Size_Of_Export_Table;
    Section.Pointer_To_Raw_Data = Origo;
    Section.Characteristics = PE::_IMAGE_SCN_CNT_INITIALIZED_DATA | PE::_IMAGE_SCN_MEM_READ | PE::_IMAGE_SCN_MEM_WRITE;

    obj->Sections.push_back(Section);
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
        Buffer.insert(Buffer.end(), s.begin(), s.end());
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
