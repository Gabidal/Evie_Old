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

    static vector<unsigned char> Write_PE_Executable(PE::PE_OBJ* obj);

};

#endif