#include "../../H/Linker/Linker.h"

#include "../../H/Assembler/Assembler_Types.h"
#include "../../H/BackEnd/Selector.h"

extern Selector* selector;

Linker::Linker(vector<Byte_Map_Section*> Input){

    for (auto& i : Input){
        for (int j = 0; j < i->Byte_Maps.size(); j++){
            string tmp = selector->Assemble(i->Byte_Maps[j]);
            i->Calculated_Byte_Maps += tmp;

            //give the 
        }
    }

}