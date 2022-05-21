#ifndef _LINKER_H_
#define _LINKER_H_

#include <vector>
#include <string>

using namespace std;

class Linker{
    public:
    string Output;

    Linker(vector<class Byte_Map_Section*> Input);

};

#endif