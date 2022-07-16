#include "../../H/Docker/DLL.h"
#include "../../H/Linker/Linker.h"
#include "../../H/UI/Usr.h"
#include "../../H/Nodes/Node.h"
#include "../../H/BackEnd/Selector.h"

extern Usr* sys;
extern Selector* selector;

vector<PE::Section> DLL::Gather_All_Tables(vector<unsigned char> Buffer, PE::Header h)
{
	vector<PE::Section> Result;

	unsigned int Start_Of_Section_Table = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header);

	//Gather all sections
	for (int i = 0; i < h.Number_Of_Sections; i++)
	{
		PE::Section s = *(PE::Section*)&Buffer[Start_Of_Section_Table + (i * sizeof(PE::Section))];

		Result.push_back(s);
	}

	return Result;
}

vector<string> DLL::Gather_All_Export_Names(PE::Header h, vector<unsigned char> buffer, PE::Section s)
{
	PE::Export_Table* e = Linker::Read_Export_Table(s, buffer);

	return e->Name_Table;
}

void DLL::DLL_Analyser(vector<string>& Output)
{
	//get the header and then start up the section suckup syste 2000 :D
	//read the file
	vector<uint8_t> tmp = DOCKER::Get_Char_Buffer_From_File(DOCKER::Working_Dir.back().second + DOCKER::FileName.back(), "");
	vector<unsigned char> buffer = vector<unsigned char>(*(unsigned char*)tmp.data(), tmp.size());

	//read the header of this obj file
	PE::Header header = *(PE::Header*)&buffer;

	//now gather all the RVA sizes
	vector<PE::Section> Sections = Gather_All_Tables(buffer, header);

	unsigned long long Name;
    memcpy(&Name, ".edata", 6);

	for (auto i : Sections) {
		if (i.Name == Name) {
			//now we have the export table
			DOCKER::Append(Output, Gather_All_Export_Names(header, buffer, i));

			break;
		}
	}
}

void DLL::Enlarge_PE_Header(PE::PE_OBJ* obj){

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
    obj->Header.Image_Base = PE::_WINDOWS_PE_EXE_BASE_IMAGE;
    obj->Header.Size_Of_Image = Image_Size;

    Linker::Add_Export_Table(obj, 3);
    Linker::Add_Import_Table(obj, 2);
    DLL::Add_Base_Relocation_table(obj);

    for (auto& s : obj->Sections){

        obj->Header.Size_Of_Image += s.Size_Of_Raw_Data;

    }

    unsigned char Optional = 0;

    if (sys->Info.Debug){

        Optional = PE::_IMAGE_FILE_DEBUG_STRIPPED;

    }

    obj->Header.Machine = PE::_IMAGE_FILE_MACHINE_AMD64;
    obj->Header.Number_Of_Sections = obj->Sections.size();
    obj->Header.Pointer_To_Symbol_Table = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header) + obj->Sections.size() * sizeof(PE::Section);
    obj->Header.Size_Of_Optional_Header = (sizeof(PE::Header))- (offsetof(PE::Header, PE::Header::Characteristics) + sizeof(PE::Header::Characteristics));
    obj->Header.Characteristics = PE::_IMAGE_FILE_EXECUTABLE_IMAGE | PE::_IMAGE_FILE_LARGE_ADDRESS_AWARE | Optional;
    obj->Header.Date_Time = time_t(time(NULL));
    obj->Header.Magic = PE::MAGIC_NUMBER;
    obj->Header.Linker_Version = 0;
    obj->Header.Size_Of_Uninitialized_Data = 0;
    obj->Header.Base_Of_Code = Code_Starting_Address;
    //obj->Header.Base_Of_Data = Data_Starting_Address;
    obj->Header.Section_Alignment = PE::_SECTION_ALIGNMENT;
    obj->Header.File_Alignment = PE::_FILE_ALIGNMENT;
    obj->Header.Operating_System_Version = PE::_IMAGE_OS_VERSION;
    obj->Header.Image_Version = 0;
    obj->Header.Subsystem_Version = PE::_IMAGE_SUBSYSTEM_VERSION;
    obj->Header.Win32_Version_Value = 0;


    obj->Header.Size_Of_Headers = sizeof(PE::Header) + sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Section) * obj->Sections.size();

    int Padding = ((obj->Header.Size_Of_Headers + PE::_FILE_ALIGNMENT - 1) & ~(PE::_FILE_ALIGNMENT - 1)) - obj->Header.Size_Of_Headers;

    obj->Header.Size_Of_Headers += Padding;


    obj->Header.Check_Sum = 0;
    obj->Header.Subsystem = PE::_IMAGE_SUBSYSTEM_WINDOWS_CUI;
    obj->Header.Dll_Characteristics = 0;
    obj->Header.Size_Of_Stack_Reserve = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Stack_Commit = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Heap_Reserve = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Heap_Commit = PE::_BUCKET_SIZE;

    //Now we need to add the export and import tables
    obj->Header.Number_Of_Rva_And_Sizes = 15;
    
    Linker::Update_Obj_Headers(obj);

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
void DLL::Add_Base_Relocation_table(PE::PE_OBJ* obj){
    if (obj->Relocations.size() == 0)
        return;
    
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
        i.Page_RVA += obj->Header.Image_Base;
        i.Block_Size = i.Relocations.size() * sizeof(PE::Relocation_Field) + sizeof(PE::Base_Relocation_Block::Page_RVA) + sizeof(PE::Base_Relocation_Block::Block_Size);
        obj->Header.Size_Of_Base_Relocation_Table += i.Block_Size;
    }

    obj->Header.Base_Relocation_Table = sizeof(PE::Bull_Shit_Headers) + sizeof(PE::Header) + obj->Sections.size() * sizeof(PE::Section) + obj->Symbols.size() * sizeof(PE::Symbol) + obj->String_Table_Size + obj->Header.Size_Of_Image + obj->Header.Size_Of_Export_Table + obj->Header.Size_Of_Import_Table;


    //Now make the section for the base relocation table.
    PE::Section section;

    section.Characteristics = PE::_IMAGE_SCN_CNT_INITIALIZED_DATA | PE::_IMAGE_SCN_MEM_READ | PE::_IMAGE_SCN_MEM_WRITE;
    memcpy(&section.Name, ".reloc", 6);
    section.Virtual_Address = obj->Header.Base_Relocation_Table;
    section.Size_Of_Raw_Data = obj->Header.Size_Of_Base_Relocation_Table;
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

    Linker::Write_Export_Table(obj, Buffer);
    Linker::Write_Import_Table(obj, Buffer);
    DLL::Write_Base_Relocation_Table(obj, Buffer);

	//transform the 
	return Buffer;
}