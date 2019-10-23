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
    Word &Previus;
public:
    bool INSIDE_OF_TYPE = false;
    bool INSIDE_OF_FUNC = false;

    Definer(string fileName);
    ~Definer();
    void Define(int i);
    void Pattern_Func(int i);
    void Pattern_Parenthesis(int i);
    int getWord(char end, string &destination, string source, int continu);
    int getReverseWord(char end, string &destination, string source, int continu);
    int findWord(string name);
    void Pattern_Locater(int i, Word &name);
    void Pattern_Variable(int i);
    void Pattern_Use(int i);
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