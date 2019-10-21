#ifndef _READER_H_
#define _READER_H_
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../Parser/Assembly_Definitions.h"
using namespace std;

vector<string> Reader(string name)
{
    ifstream file(name);
    vector<string>BUFFER;
    if (file.is_open() != true)
    {
        cout << "File not found!" + string(NL);
        exit(1);
    }
    else
    {
        string Line;
        while (getline(file, Line))
        {
            BUFFER.push_back(Line);
        }
    }
    return BUFFER;
}

#endif