#include "../../H/Docker/ELF.h"
#include "../../H/UI/Safe.h"

// Returns true if the ELF-file is 32-bit, otherwise false
bool ELF::Get_Bits_Size(uint8_t* buffer)
{
   return reinterpret_cast<elf32_hdr*>(buffer)->e_ident[EI_CLASS] == 1;
}

uint64_t ELF::Get_Section_Header_Offset(uint8_t* buffer)
{
	return Get_Bits_Size(buffer) ? reinterpret_cast<elf32_hdr*>(buffer)->e_shoff : reinterpret_cast<elf64_hdr*>(buffer)->e_shoff;
}

uint64_t ELF::Get_Header_Amount(uint8_t* buffer)
{
	return Get_Bits_Size(buffer) ? reinterpret_cast<elf32_hdr*>(buffer)->e_shnum : reinterpret_cast<elf64_hdr*>(buffer)->e_shnum;
}

uint8_t* ELF::Get_Section_Names(uint8_t* buffer) {
    bool BIT_SIZE = Get_Bits_Size(buffer);
    uint16_t Index = Get_Bits_Size(buffer) ? reinterpret_cast<elf32_hdr*>(buffer)->e_shstrndx : reinterpret_cast<elf64_hdr*>(buffer)->e_shstrndx;
    uint64_t Current_Section_Header = Get_Section_Header_Offset(buffer);
    uint64_t Header_Count = Get_Header_Amount(buffer);
    vector<string> Names;

    if (BIT_SIZE) {
        elf32_shdr* Section_Headers = reinterpret_cast<elf32_shdr*>(&buffer[Current_Section_Header]);
        elf32_shdr& Section_Header = Section_Headers[Index];

        /*
            Made by Joonas Lehto 13/05/2020
              Master header:
              is x86 or x86-64
        | <-- sh_offset: int
              e_shstrndx: int (INDEX) = 31
        |
        |
        |
        |
        |-->  First Section Header:

              type: int
              name: int (index)

              .
              .
              .

              .rdata Section Header: (30)
              type: int
              name: int (index) = 2

              .rdata Section Header: (31)
              type: int
              name: int (index) = 2

              .
              .
              .

              TARGET e_shstrndx (31)
              type: int
              name: int (index)
              position: int (pointer)


              .
              .
              .

              Last Section Header:

              type: int
              name: int (index)









   2443FG F DF
  3qerFEF
  REFRFE
  WEF W FR  _glfwInit \0



  wdwwd                                                    0        1        2
  dwdwwwwwwwwwwwwwwgrrfrfefe ...........dw  3 r3rr  4 3 -> .text \0 .data \0 .rdata \0 => { .text, .data, .rdata }




        */

        return reinterpret_cast<uint8_t*>(&buffer[Section_Header.sh_offset]);

        string type = "";
        /*for (int i = 0; i < Section_Header.sh_size; i++)
        {
            if (position[i] == 0) {
                Names.push_back(type);
                type = "";
                continue;
            }
            type.push_back(position[i]);
        }*/
    }
    else
    {
        //this summer coming soon!
        elf64_shdr* Section_Headers = reinterpret_cast<elf64_shdr*>(&buffer[Current_Section_Header]);
        elf64_shdr& Section_Header = Section_Headers[Index];

        return reinterpret_cast<uint8_t*>(&buffer[Section_Header.sh_offset]);

        string type = "";
        /*for (int i = 0; i < Section_Header.sh_size; i++)
        {
            if (position[i] == 0) {
                Names.push_back(type);
                type = "";
                continue;
            }
            type.push_back(position[i]);
        }*/
    }
    //Names.insert(Names.begin() + 1, ".hash");       //!!!!
    //return Names;
}

Section ELF::Find_Section(uint8_t* buffer, string type) {
    bool BIT_SIZE = Get_Bits_Size(buffer);
    uint64_t Current_Section_Header = Get_Section_Header_Offset(buffer);
    uint64_t Header_Count = Get_Header_Amount(buffer);

    uint8_t* Names = Get_Section_Names(buffer);

    if (BIT_SIZE) {
        elf32_shdr* Section_Headers = reinterpret_cast<elf32_shdr*>(&buffer[Current_Section_Header]);
        for (int i = 0; i < Header_Count; i++)
        {
            elf32_shdr& Section_Header = Section_Headers[i];

            string name = (const char*)&Names[Section_Header.sh_name];

            if (name == type)
            {
                return { &buffer[Section_Header.sh_offset], Section_Header.sh_size };
            }
        }
    }
    else
    {
        elf64_shdr* Section_Headers = reinterpret_cast<elf64_shdr*>(&buffer[Current_Section_Header]);
        for (int i = 0; i < Header_Count; i++)
        {
            elf64_shdr& Section_Header = Section_Headers[i];

            string name = (const char*)&Names[Section_Header.sh_name];

            if (name == type)
            {
                return { &buffer[Section_Header.sh_offset], Section_Header.sh_size };
            }
        }
    }
    Report(Observation(ERROR, "Couldn't find section " + type, Position()));
    throw "Yeet";
}

void ELF::ELF_Analyzer(vector<string>& output)
{
    vector<string> Header_Data = DOCKER::Get_Header(DOCKER::FileName.back());
    if (Header_Data.size() < 1)
        Header_Data = DOCKER::Get_Header("elf..e");
    if (Header_Data.size() < 1)
        Header_Data = DOCKER::Get_Header("general");
    if (Header_Data.size() < 1)
        Report(Observation(ERROR, "Docker didn't find Header file for " + DOCKER::FileName.back(), Position()));
    
    //open & read the bin file
    vector<unsigned char> File_Buffer = DOCKER::Get_Char_Buffer_From_File(DOCKER::FileName.back(), DOCKER::Working_Dir);
    Section Function_Section = ELF::Find_Section(File_Buffer.data(), ".dynstr");
    for (int i = 0; i < Function_Section.size; i++) {
        if (Function_Section.start[i] == '\0')
            Function_Section.start[i] = '?';
    }
    string Tmp = string((char*)Function_Section.start, Function_Section.size);
    DOCKER::Append(output, DOCKER::Get_Names_Of(Tmp, DOCKER::Separate_Identification_Patterns(Header_Data)));
    DOCKER::Libs.push_back(DOCKER::Working_Dir + DOCKER::FileName.back());
    return;
}