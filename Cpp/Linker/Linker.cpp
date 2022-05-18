#include "../../H/Linker/Linker.h"

#include "../../H/Assembler/Assembler_Types.h"
#include "../../H/BackEnd/Selector.h"

extern Selector* selector;

Linker::Linker(vector<Byte_Map*> Input){

    for (auto i : Input){
        Output += selector->Assemble(i);
    }

}