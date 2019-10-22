#ifndef _DEFINER_H_
#define _DEFINER_H_
#include <vector>
#include <string>
#include "Reader.h"
#include "Word.h"
using namespace std;

class Definer
{
private:
    vector<string> Lines;
    vector<Word> output;
public:
    Definer(string fileName);
    ~Definer();
    void Define(int i);
    void Pattern_Func(int i);
    void Definer::Pattern_Parenthesis(int i);
    int getWord(char end, string &destination, string source, int continu);
};

Definer::Definer(string fileName)
{
    Lines = Reader(fileName);
    for (int i = 0; i < Lines.size(); i++)
    {
        Define(i);
    }
}

Definer::~Definer()
{
}


#endif