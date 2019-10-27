#ifndef _READER_H_
#define _READER_H_
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

string Reader(string name)
{
    ifstream file(name);
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
    return BUFFER;
}

#endif