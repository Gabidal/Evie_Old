#ifndef _LINKER_H_
#define _LINKER_H_

#include <vector>
#include <string>

using namespace std;

class Linker{
    public:

    vector<unsigned char> Link_PE_Object(vector<unsigned char> Input);

};

#endif