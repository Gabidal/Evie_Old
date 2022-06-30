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

    //Now find this function name from the symbol table
    for (auto& i : obj->Symbols){
        if (i.Get_Name(obj->String_Table_Buffer) == Starting_Function->Mangled_Name){
            obj->Header.Address_Of_Entry_Point = i.Value;
            break;
        }
    }

    unsigned char Optional = 0;

    if (sys->Info.Debug){

        Optional = PE::_IMAGE_FILE_DEBUG_STRIPPED;

    }

    unsigned long long Code_Size = 0;
    unsigned long long Data_Size = 0;

    unsigned int Code_Starting_Address = 0;
    unsigned int Data_Starting_Address = 0;

    unsigned long long Image_Size = 0;

    for (auto& i : obj->Content){
        if (i->Is_Data_Section){

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

    obj->Header.Machine = PE::_IMAGE_FILE_MACHINE_AMD64;
    obj->Header.Number_Of_Sections = obj->Sections.size();
    obj->Header.Size_Of_Optional_Header = 0xE0;
    obj->Header.Characteristics = PE::_IMAGE_FILE_EXECUTABLE_IMAGE | PE::_IMAGE_FILE_LARGE_ADDRESS_AWARE | Optional;
    obj->Header.Date_Time = time_t(time(NULL));
    obj->Header.Magic = PE::MAGIC_NUMBER;
    obj->Header.Linker_Version = 0;
    obj->Header.Size_Of_Code = Code_Size;
    obj->Header.Size_Of_Initialized_Data = Data_Size;
    obj->Header.Size_Of_Uninitialized_Data = 0;
    obj->Header.Base_Of_Code = Code_Starting_Address;
    //obj->Header.Base_Of_Data = Data_Starting_Address;
    obj->Header.Image_Base = PE::_WINDOWS_PE_EXE_BASE_IMAGE;
    obj->Header.Section_Alignment = PE::_SECTION_ALIGNMENT;
    obj->Header.File_Alignment = PE::_FILE_ALIGNMENT;
    obj->Header.Operating_System_Version = 0;
    obj->Header.Image_Version = 0;
    obj->Header.Subsystem_Version = 0;
    obj->Header.Win32_Version_Value = 0;
    obj->Header.Size_Of_Image = Image_Size;
    obj->Header.Size_Of_Headers = sizeof(PE::Header);
    obj->Header.Check_Sum = 0;
    obj->Header.Subsystem = 0;
    obj->Header.Dll_Characteristics = 0;
    obj->Header.Size_Of_Stack_Reserve = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Stack_Commit = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Heap_Reserve = PE::_BUCKET_SIZE;
    obj->Header.Size_Of_Heap_Commit = PE::_BUCKET_SIZE;


}

vector<unsigned char> Linker::Write_PE_Executable(PE::PE_OBJ* obj){
    vector<unsigned char> Buffer;

	Buffer.insert(Buffer.end(), (unsigned char*)&obj->Header, (unsigned char*)&obj->Header + sizeof(PE::Header));

	Buffer.insert(Buffer.end(), (unsigned char*)obj->Sections.data(), (unsigned char*)obj->Sections.data() + sizeof(PE::Section) * obj->Sections.size());

	Buffer.insert(Buffer.end(), (unsigned char*)obj->Symbols.data(), (unsigned char*)obj->Symbols.data() + sizeof(PE::Symbol) * obj->Symbols.size());

	Buffer.insert(Buffer.end(), (unsigned char*)&obj->String_Table_Size, (unsigned char*)&obj->String_Table_Size + sizeof(obj->String_Table_Size));

	Buffer.insert(Buffer.end(), obj->String_Table_Buffer.begin(), obj->String_Table_Buffer.end());

	for (auto i : obj->Content){

		for (auto& j : i->Byte_Maps){

			vector<unsigned char> Data = selector->Assemble(j);

			Buffer.insert(Buffer.end(), Data.begin(), Data.end());

		}

	}

	//transform the 
	return Buffer;
}