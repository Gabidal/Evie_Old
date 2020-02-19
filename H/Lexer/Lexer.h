#ifndef _LEXER_H_
#define _LEXER_H_
#include <vector>
#include <string>
#include "Word.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

class Lexer
{
public:
    string Lines;
    int LineNumber = 0;
    vector<Word*> output;
    bool INSIDE_OF_TYPE = false;
    bool INSIDE_OF_FUNC = false;

    Lexer(){}
    ~Lexer(){}

    void Define();

    void OpenFile(const char* fileName);
    void Direct(string raw);
    
};


#endif