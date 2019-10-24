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
    bool INSIDE_OF_TYPE = false;
    bool INSIDE_OF_FUNC = false;

    Definer(string fileName);
    ~Definer();
    void Define(int i);
    int skipReverseParenthesis(int i, string &source);
    int Find(string name, vector<Word> source);
    void Pattern_Use(int i, string name);
    void Pattern_Func(int i);
    void Pattern_Parenthesis(int i);
    int getWord(char end, string &destination, string source, int continu);
    int getReverseWord(char end, string &destination, string source, int continu);
    int getAmount(char end, vector<int> &destination, string source);
    int findWord(string name);
    void Pattern_Locater(int i, Word &name);
    void Pattern_Variable(int i);
    void Pattern_Equ(int i);
    void Pattern_Math(int i);
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