#ifndef _LEXER_H_
#define _LEXER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include "keyword.h"
#include "parser.h"
using namespace std;
map<string, keyword> keyWords;

void initializeKeyWords()
{
    keyWords.insert(make_pair("var", keyword("var", 3, true, true)));
    keyWords.insert(make_pair("run", keyword("run", 2, true, true)));
    keyWords.insert(make_pair("func", keyword("func", 2, true, true)));
    keyWords.insert(make_pair("%", keyword("%", 2, true, true)));
}
string readFile(string name)
{
    string line;
    ifstream file(name, ios::ate | ios::binary);
    int length = file.tellg();
    file.seekg(0, file.beg);

    char* buffer = new char[length];
    memset(buffer, 0, length);

    if (file.is_open()) 
    {
        file.read(buffer, length);
    }
    file.close();
    return string(buffer);
}

int getWord(char end, string &destination, string source, int continu)
{
    for (int i = continu; i < source.size();i++)
    {
        if (source[i] != end && source[i] != '\n')
        {
            destination += source[i];
        }
        else
        {
            i++;
            return i;
        }
        
    }

    return source.size();
}

void writeFile(string name, string buffer)
{
    ofstream file(name);

    if (file.is_open()) {
        file.write(buffer.c_str(), buffer.length());
    }
    
    file.close();
}

void lexer(string file, string &outbuffer)
{
    string destination;
    int continu = 0;
    for (int i = 0; i < file.size(); i++)
    {
        destination = "";
        continu = getWord(' ', destination, file, continu);
        if (destination.find("%") != -1)
        {
            outbuffer += parser(destination, file, continu);
        }

        auto iterator = keyWords.find(destination);

        if (iterator != keyWords.end()) 
        {
            outbuffer += parser(destination, file, continu);
            destination = "";
        }
    }
}

#endif