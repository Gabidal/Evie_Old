#include "../../H/Linker/Linker.h"

#include "../../H/Assembler/Assembler_Types.h"
#include "../../H/BackEnd/Selector.h"

extern Selector* selector;

Linker::Linker(vector<Byte_Map_Section*> Input){

    for (auto i : Input){
        for (auto j : i->Byte_Maps){
            pair<int, string> tmp = selector->Assemble(j);
            i->Calculated_Byte_Maps += tmp.second;
            i->Calculated_Size += tmp.first;
        }
    }

}