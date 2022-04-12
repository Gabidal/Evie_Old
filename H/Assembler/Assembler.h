#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include "Assembler_Types.h"

#include <string>
#include <vector>

using namespace std;

//Transforms the input string into a vector of tokens
//Where 'mov rax, qword ptr [rax]', transforms into:
//name = mov:
//  Childs[0] = name = rax
//  Childs[1] = name = []:
//      Childs[0] = name = rax
//      size = qword ptr
//  size = qword ptr

class Assembler{
public:
    vector<Word> Words;

    Assembler(string Input){

    }

    vector<string> Tokenizer(string Input);
    void Factory();
};


#endif