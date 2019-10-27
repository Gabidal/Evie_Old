#ifndef _DEFINER_H_
#define _DEFINER_H_
#include <vector>
#include <string>
#include "Reader.h"
#include "Word.h"
using namespace std;

class Definer
{
public:
    string Lines;
    vector<Word> output;
    bool INSIDE_OF_TYPE = false;
    bool INSIDE_OF_FUNC = false;

    Definer(const char* fileName);
    Definer(string raw);
    ~Definer();
    void Define();
};

Definer::Definer(string raw)
{
    Lines = raw;
    Define();
}

Definer::Definer(const char* fileName)
{
    Lines = Reader(fileName);
    Define();
}

Definer::~Definer()
{
}


#endif