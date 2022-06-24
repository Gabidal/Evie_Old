#ifndef _LINKER_H_
#define _LINKER_H_

#include <vector>
#include <string>

namespace PE{
    class PE_OBJ;
};

using namespace std;

class Linker{
    public:

    void Resolve_Relocations(PE::PE_OBJ* obj);

};

#endif