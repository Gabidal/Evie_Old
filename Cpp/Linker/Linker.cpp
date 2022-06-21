#include "../../H/Linker/Linker.h"

#include "../../H/Assembler/Assembler_Types.h"
#include "../../H/BackEnd/Selector.h"

#include "../../H/Docker/OBJ.h"

extern Selector* selector;

//This file takes list of files and theyre contents and links them together
vector<unsigned char> Link_PE_Object(vector<vector<unsigned char>> Input){
    vector<unsigned char> Result;

    vector<PE::PE_OBJ> Objects;

    for (auto& i : Input){
        Objects.push_back(PE::PE_OBJ(i));
    }

    
    
    return Result;
}