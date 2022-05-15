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

    //Tokenizer stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    vector<Word*> Tokenizer(string Input);
    int Get_Paranthesis_Content_Length(char Opening_Paranthesis_Type, int Start_Index, string Input);
    char Get_Closing_Character(char Opening_Character);
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    //Grouper stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    vector<class Token*> Grouper(vector<Word*> Tokens);

    //Parser stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    vector<class IR*> Parser(vector<class Token*> Tokens);

    //Post-Prosessor stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    vector<class IR*> Parser_Post_Prosessor(vector<class IR*> IRs);

    //Encoder stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    vector<Byte_Map*> Intermediate_Encoder(vector<class IR*>);

    void Factory();
};


#endif