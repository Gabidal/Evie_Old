#ifndef _LINKER_H_
#define _LINKER_H_

#include <vector>
#include <string>

#include "../Assembler/Assembler_Types.h"
#include "../Docker/OBJ.h"

using namespace std;

class Linker{
    public:

    static void En_Large_PE_Header(PE::PE_OBJ* obj);
    static void Update_Obj_Headers(PE::PE_OBJ* obj);

    static vector<unsigned char> Write_PE_Executable(PE::PE_OBJ* obj);

    static void Add_Export_Table(PE::PE_OBJ* obj, int expected_section_count);
    static void Add_Import_Table(PE::PE_OBJ* obj, int expected_section_count);
    static void Add_Import_Address_Table(PE::PE_OBJ* obj);

    static void Write_Export_Table(PE::PE_OBJ* obj, vector<unsigned char>& Buffer);
    static void Write_Import_Table(PE::PE_OBJ* obj, vector<unsigned char>& Buffer);
    static void Write_Import_Address_Table(PE::PE_OBJ* obj, vector<unsigned char>& Buffer);

    static PE::Export_Table* Read_Export_Table(PE::Section& s, vector<unsigned char>& Buffer);

};

#endif