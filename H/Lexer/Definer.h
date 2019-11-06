#ifndef _DEFINER_H_
#define _DEFINER_H_
#include <vector>
#include <string>
#include "Word.h"
#include <fstream>
#include <iostream>
using namespace std;

class Definer
{
public:
    string Lines;
    vector<Word> output;
    bool INSIDE_OF_TYPE = false;
    bool INSIDE_OF_FUNC = false;

    void Define();

    void OpenFile(const char* fileName);
    void Direct(string raw);
    
    Definer()
    {
    }
    
    ~Definer()
    {
    }
};


#endif