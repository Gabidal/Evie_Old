#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

//#include "Assembler_Types.h"

#include <string>
#include <vector>
#include <map>

#include <unordered_set>

using namespace std;

//Transforms the input string into a vector of tokens
//Where 'mov rax, qword ptr [rax]', transforms into:
//name = mov:
//  Childs[0] = name = rax
//  Childs[1] = name = []:
//      Childs[0] = name = rax
//      size = qword ptr
//  size = qword ptr

class Symbol_Data{
public:
    long long Address;
    int Section_ID;
    class Node* Origin;
};

class Assembler{
public:
    vector<class Byte_Map_Section*> Output;

    //         name, Origin,        address, section id
    map<string, Symbol_Data> Symbol_Table;

    Assembler(){}

    void Factory(string Input);
    void Factory(vector<class IR*> IRs);

    //Tokenizer stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    vector<class Word*> Tokenizer(string Input);
    int Get_Paranthesis_Content_Length(char Opening_Paranthesis_Type, int Start_Index, string Input);
    char Get_Closing_Character(char Opening_Character);
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    //Grouper stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    vector<class Token*> Grouper(vector<class Word*> Tokens);

    //Parser stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    vector<class IR*> Parser(vector<class Token*> Tokens);

    //Post-Prosessor stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    vector<class IR*> Parser_Post_Prosessor(vector<class IR*> IRs);

    //Encoder stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    vector<class Byte_Map_Section*> Intermediate_Encoder(vector<class IR*>);

    void Apply_Self_Recursion(vector<class Byte_Map_Section*>& Sections);
    void Go_Through_Token_And_Replace_Local_Labels_With_Numbers(Token* Current, class Byte_Map* Back_Reference);
    void Go_Through_Token_And_Replace_Local_Labels_With_Numbers(Token* Current, Byte_Map* Back_Reference, unordered_set<Token*>& Trace);
    void Calculate_Constant_Expressions(Token* Current, unordered_set<Token*>& Trace);
    void Calculate_Constant_Expressions(Token* Current);
    

    //Symbol Table stuff
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    void Generate_Symbol_Table_For(string Label, long long Address, int Section_ID, class Node* Origin);
    void Replace_Symbol_With_Address(IR& ir);
};


#endif