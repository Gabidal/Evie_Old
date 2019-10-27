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

    Definer(string raw)
    {
        Lines = raw;
        Define();
    }
    
    Definer(const char* fileName)
    {
        
    ifstream file(fileName);
    string BUFFER;
    if (file.is_open() != true)
    {
        cout << "File not found!\n";
        exit(1);
    }
    else
    {
        string Line;
        while (getline(file, Line))
        {
            BUFFER += Line;
        }
    }
    Lines = BUFFER;
        Define();
    }
    
    ~Definer()
    {
    }
};


#endif