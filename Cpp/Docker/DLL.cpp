#include "../../H/Docker/DLL.h"
#include "../../H/Linker/Linker.h"
#include "../../H/UI/Usr.h"
#include "../../H/Nodes/Node.h"
#include "../../H/BackEnd/Selector.h"

#include "../../H/UI/Safe.h"

extern Usr* sys;
extern Selector* selector;

vector<PE::Section> DLL::Gather_All_Tables(vector<unsigned char> Buffer, PE::Header_64 h)
{
	vector<PE::Section> Result;

    unsigned int Non_Optional_Header_Size = 0x18;

	unsigned int Start_Of_Section_Table = Get_Bull_Shit_Header_Size(Buffer) + h.Size_Of_Optional_Header + Non_Optional_Header_Size;

	//Gather all sections
	for (int i = 0; i < h.Number_Of_Sections; i++)
	{
		PE::Section s = *(PE::Section*)&Buffer[Start_Of_Section_Table + (i * sizeof(PE::Section))];

		Result.push_back(s);
	}

	return Result;
}

vector<string> DLL::Gather_All_Export_Names(PE::Header_64 h, vector<unsigned char> buffer, PE::Section s)
{
 	PE::Export_Table* e = Linker::Read_Export_Table(s, buffer);

	return e->Name_Table;
}

void DLL::DLL_Analyser(vector<string>& Output)
{
	//get the header and then start up the section suckup system 2000 :D
	//read the file
	vector<uint8_t> tmp = DOCKER::Get_Char_Buffer_From_File(DOCKER::Working_Dir.back().second + DOCKER::FileName.back(), "");
	
    // Cast the tmp vector into a unsigned char vector
    vector<unsigned char> buffer(tmp.begin(), tmp.end());
    
    PE::Section Export_Table;
    
    try{
	    Export_Table = Get_Export_Table(buffer);
    }
    catch (Not_Found){
        Report(Observation(ERROR, "Could not find export table on dll: " + DOCKER::FileName.back(), LINKER_INTERNAL, NO));
    }

    DOCKER::Append(Output, Gather_All_Export_Names(Read_Headers(buffer), buffer, Export_Table));
}

void DLL::Enlarge_PE_Header(PE::PE_OBJ* obj){

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
    
    obj->Header.Size_Of_Code = Code_Size;
    obj->Header.Size_Of_Initialized_Data = Data_Size;

    obj->Header.Size_Of_Uninitialized_Data = 0;
    obj->Header.Base_Of_Code = Code_Starting_Address;

    obj->Header.Image_Base = PE::_WINDOWS_PE_DLL_BASE_IMAGE;
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
    DLL::Add_Base_Relocation_table(obj, 0);    //Sections(text, data, export, import, base)
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

    if (obj->Relocations.size() > 0){
        Potential_Section_Count++;
    }

    obj->Base_Relocations.Blocks.clear();

    Linker::Add_Export_Table(obj, Potential_Section_Count);       //Sections(text, data) + (export, import, base)
    Linker::Add_Import_Table(obj, Potential_Section_Count);       //Sections(text, data, export) + (import, base)
    DLL::Add_Base_Relocation_table(obj, Potential_Section_Count);    //Sections(text, data, export, import, base)
    Linker::Add_Import_Address_Table(obj);  //Sections(text, data, export, import, base)


    obj->Header.Size_Of_Code = (Code_Size + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    
    obj->Header.Size_Of_Initialized_Data = (Data_Size + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    
    obj->Header.Size_Of_Headers = sizeof(PE::Header_64) + sizeof(PE::Bull_Shit_Headers) + sizeof(PE::PE_SIGNATURE_HEADER) + sizeof(PE::Section) * obj->Sections.size();
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
    obj->Header.Pointer_To_Symbol_Table = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::PE_SIGNATURE_HEADER) + sizeof(PE::Header_64) + obj->Sections.size() * sizeof(PE::Section);
    obj->Header.Number_Of_Symbols = obj->Symbols.size();
    obj->Header.Size_Of_Optional_Header = (sizeof(PE::Header_64))- (offsetof(PE::Header_64, PE::Header_64::Characteristics) + sizeof(PE::Header_64::Characteristics));
    obj->Header.Characteristics = PE::_IMAGE_FILE_EXECUTABLE_IMAGE | PE::_IMAGE_FILE_LARGE_ADDRESS_AWARE | PE::_IMAGE_FILE_DEBUG_STRIPPED | PE::_IMAGE_FILE_LINE_NUMS_STRIPPED | PE::_IMAGE_FILE_RELOCS_STRIPPED | PE::_IMAGE_FILE_DLL;

    //Now find this function name from the symbol table
    for (auto& i : obj->Symbols){
        if (i.Get_Name(obj->String_Table_Buffer) == Starting_Function->Mangled_Name){
            obj->Header.Address_Of_Entry_Point = i.Value + obj->Sections[i.Section_Number - 1].Virtual_Address;
            break;
        }
    }
}

//Chop the entire DLL into 4K chunks and then assess the .Text and .Data sections, where there is a  
//Go through the relocations table that comes from .obj files and calculate the 4K modulo remainder offsets from the relocation table.
void DLL::Add_Base_Relocation_table(PE::PE_OBJ* obj, int Expected_Section_Count){
    if (obj->Relocations.size() == 0)
        return;

    int Origo = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::PE_SIGNATURE_HEADER) + sizeof(PE::Header_64) + sizeof(PE::Section) * Expected_Section_Count + sizeof(PE::Symbol) * obj->Symbols.size() + obj->String_Table_Size;

    int Start_Of_Code = (Origo + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    int Start_Of_Data = (Start_Of_Code + obj->Header.Size_Of_Code + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    int Start_Of_Export_Table = (Start_Of_Data + obj->Header.Size_Of_Initialized_Data + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    int Start_Of_Import_Table = (Start_Of_Export_Table + obj->Header.Size_Of_Export_Table + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);
    int Start_Of_Import_Address_Table = Start_Of_Import_Table + (obj->Header.Size_Of_Import_Table - obj->Header.Size_Of_Import_Address_Table);
    int Start_Of_Base_Relocation_Table = (Start_Of_Import_Address_Table + obj->Header.Size_Of_Import_Address_Table + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1);

    Origo = Start_Of_Base_Relocation_Table;
    
    const int _4K = 4096;

    PE::Base_Relocation_Block start_block;
    start_block.Page_RVA = obj->Relocations[0].Virtual_Address;

    obj->Base_Relocations.Blocks.push_back(start_block);

    for (auto& i : obj->Relocations){
        //If current i.Virtual_Address is over the last block's RVA + 4K, then we need to create a new block
        if (i.Virtual_Address >= obj->Base_Relocations.Blocks.back().Page_RVA + _4K){
            PE::Base_Relocation_Block block;

            block.Page_RVA = i.Virtual_Address;
            obj->Base_Relocations.Blocks.push_back(block);
        }

        //check if the i->Virtual_Address is within the current block
        if (i.Virtual_Address < obj->Base_Relocations.Blocks.back().Page_RVA+ _4K){
            PE::Relocation_Field field;
            //calculate the offset difference between the current clock base RVA and i.virtual_address
            field.Set_Virtual_Address(i.Virtual_Address % _4K);
            field.Set_Type(PE::_IMAGE_REL_BASED_LOW); 

            obj->Base_Relocations.Blocks.back().Relocations.push_back(field);
        }
    }

    //now we need to add image base to all the blocks rva
    for (auto& i : obj->Base_Relocations.Blocks){
        i.Page_RVA += PE::_WINDOWS_PE_EXE_BASE_IMAGE;
        i.Block_Size = i.Relocations.size() * sizeof(PE::Relocation_Field) + sizeof(PE::Base_Relocation_Block::Page_RVA) + sizeof(PE::Base_Relocation_Block::Block_Size);
        obj->Header.Size_Of_Base_Relocation_Table += i.Block_Size;
    }

    obj->Header.Base_Relocation_Table = Origo;


    //Now make the section for the base relocation table.
    PE::Section section;

    section.Characteristics = PE::_IMAGE_SCN_CNT_INITIALIZED_DATA | PE::_IMAGE_SCN_MEM_READ | PE::_IMAGE_SCN_MEM_WRITE | PE::_IMAGE_SCN_ALIGN_512BYTES;
    memcpy(&section.Name, ".reloc", 6);
    section.Virtual_Address = obj->Header.Base_Relocation_Table;
    section.Virtual_Size = obj->Header.Size_Of_Base_Relocation_Table;
    section.Size_Of_Raw_Data = ((obj->Header.Size_Of_Base_Relocation_Table + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1));
    section.Pointer_To_Raw_Data = obj->Header.Base_Relocation_Table;
    section.Pointer_To_Relocations = 0;
    section.Pointer_To_Line_Numbers = 0;
    section.Number_Of_Relocations = 0;
    section.Number_Of_Line_Numbers = 0;

    obj->Sections.push_back(section);
}

void DLL::Write_Base_Relocation_Table(PE::PE_OBJ* obj, vector<unsigned char>& buffer){

    obj->Header.Base_Relocation_Table = buffer.size();

    unsigned long long Current_Offset = buffer.size();

    for (auto& i : obj->Base_Relocations.Blocks){
        obj->Header.Size_Of_Base_Relocation_Table += i.Block_Size;

        unsigned int Padding = Current_Offset % 32;

        buffer.insert(buffer.end(), Padding, 0);

        buffer.insert(buffer.end(), (unsigned char*)&i.Page_RVA, (unsigned char*)&i.Page_RVA + sizeof(i.Page_RVA));
        buffer.insert(buffer.end(), (unsigned char*)&i.Block_Size, (unsigned char*)&i.Block_Size + sizeof(i.Block_Size));

        for (auto& r : i.Relocations){

            buffer.insert(buffer.end(), (unsigned char*)&r, (unsigned char*)&r + sizeof(r));

        }

        Current_Offset += i.Block_Size;
    }

}

vector<unsigned char> DLL::Write_DLL(PE::PE_OBJ* obj){
    vector<unsigned char> Buffer;
    PE::Bull_Shit_Headers dos;

    //add DOS bullshittery
    Buffer.insert(Buffer.end(), (unsigned char*)&dos, (unsigned char*)&dos + sizeof(dos));

    // Add the PE_Signature
    Buffer.insert(Buffer.end(), (unsigned char*)&PE::PE_SIGNATURE_HEADER, (unsigned char*)&PE::PE_SIGNATURE_HEADER + sizeof(PE::PE_SIGNATURE_HEADER));

	Buffer.insert(Buffer.end(), (unsigned char*)&obj->Header, (unsigned char*)&obj->Header + sizeof(PE::Header_64));

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

            Current_Offset += Data.size();
		}

        Current_Offset += Padding;
	}

    for (auto r : obj->Raw_Sections){
        int Padding = ((Current_Offset + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1)) - Current_Offset;

        Buffer.insert(Buffer.end(), Padding, (unsigned char)0);

        Buffer.insert(Buffer.end(), r.Data.begin(), r.Data.end());

        Current_Offset += r.Data.size() + Padding;
    }

    Linker::Write_Export_Table(obj, Buffer);
    Linker::Write_Import_Table(obj, Buffer);
    Linker::Write_Import_Address_Table(obj, Buffer);
    DLL::Write_Base_Relocation_Table(obj, Buffer);

	//transform the 
	return Buffer;
}

unsigned int DLL::Get_Bull_Shit_Header_Size(vector<unsigned char> &buffer){
    // the bull shit headers usually have the size declared in the 0x3C, fi this is zero or empty, then the size is: sizeof(PE::BULLSHIT_HEADERS)
    int DOS_Header_Size_Location = 0x3C;

    int Tmp_Value = *(int*)&buffer[DOS_Header_Size_Location];

    return Tmp_Value;
}

// Throws a "Not Found exception if the DLL does not contain a export table."
PE::Section DLL::Get_Export_Table(vector<unsigned char> &buffer){

    // The location of export table are reported in two different separate locations.
    // First one is in the Section table as a ".edata" section name, which value is the address + image_base.
    // Second one is in the Extended optional headers (blue section in wiki png), which value has NOT the image base in it.
    PE::Header_64 header = Read_Headers(buffer);

    unsigned int Image_Base = header.Image_Base;

    unsigned int Export_Table_Relative_Virtual_Address = header.Export_Table;
    unsigned int Export_Table_Size = header.Size_Of_Export_Table;

    // We can find the export table by going through all the section tables, and looking what section table contains the export table.
    vector<PE::Section> Sections = Gather_All_Tables(buffer, header);

	unsigned long long Name;
    memcpy(&Name, ".edata\0\0", 8);

    for (auto section : Sections){
        if (section.Name == Name){
            return section;
        }

        string Current_Name;
        Current_Name.resize(6);
        memcpy(Current_Name.data(), &section.Name, 6);

        if (section.Virtual_Address <= Export_Table_Relative_Virtual_Address && section.Virtual_Address + section.Virtual_Size >= Export_Table_Relative_Virtual_Address + Export_Table_Size){

            // Now that we know what section contains this section, we need to get the relation between the two.
            unsigned int Distance = Export_Table_Relative_Virtual_Address - section.Virtual_Address;

            unsigned Final_Offset = Distance + section.Pointer_To_Raw_Data;

            PE::Section Virtual_export_Table_Section;
            Virtual_export_Table_Section.Pointer_To_Raw_Data = Final_Offset;
            Virtual_export_Table_Section.Virtual_Address = Final_Offset;
            Virtual_export_Table_Section.Virtual_Size = header.Size_Of_Export_Table;
            Virtual_export_Table_Section.Size_Of_Raw_Data = header.Size_Of_Export_Table;

            return Virtual_export_Table_Section;
        }
    }

    // Throw exception of missing export table
    throw Not_Found();
}

PE::Header_64 DLL::Read_Headers(vector<unsigned char>& buffer){
	//read the header of this obj file
	PE::Header_64 header = *(PE::Header_64*)(buffer.data() + Get_Bull_Shit_Header_Size(buffer) + sizeof(PE::PE_SIGNATURE_HEADER));

    // We need to check if the Loader_Flags needs to be zero, if not we need to start shifting the numbers around until the Loader_Flags is zero.
    // Normally the 0x20b means that the file is PE+ (64 bit), and 0x10b means PE (32 bit).
    if (header.Loader_Flags != 0 || header.Magic == 0x10b){
        PE::Header_32 Smaller_Header = *(PE::Header_32*)(buffer.data() + Get_Bull_Shit_Header_Size(buffer) + sizeof(PE::PE_SIGNATURE_HEADER));

        header = Smaller_Header;
    }

    return header;
}
