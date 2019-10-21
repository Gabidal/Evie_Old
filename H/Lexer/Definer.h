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
    vector<Word> Buffer;
public:
    Definer(string fileName);
    ~Definer();
    void Define();
    void MakeKeyword(string s);
    void MakeStartParenthesis(string s);
    void MakeEndParenthesis(string s);
    void MakeFunction(string s);
    void MakeFUNCTION_START_PARENTHESIS(string s);
    void MakeFUNCTION_END_PARENTHESIS(string s);
    void MakeTYPE(string s);
    void MakeTYPE_START_PARENTHESIS(string s);
    void MakeTYPE_END_PARENTHESIS(string s);
    void MakeVARIABLE(string s);
    void MakeIF(string s);
    void MakeELSE(string s);
    void MakeELSEIF(string s);
    void MakeLOOP(string s);
    void MakeNUMBER(string s);
    void MakeRETURN(string s);
    void MakePROTOTYPE(string s);
    void MakeOFFSET(string s);
    void MakePARAMETER(string s);
    void MakeADDITION(string s);
    void MakeSUBTRACTION(string s);
    void MakeMULTIPLY(string s);
    void MakeDIVIDE(string s);
    void MakeCOMMENT(string s);
    void MakeCALL(string s);
    void MakeINCLUDE(string s);
    void MakeVARIABLE_FETCH(string s);
    void MakeFUNCTION_FETCH(string s);
    void MakeLOCATER(string s);
    void MakeNew(string s);
};

Definer::Definer(string fileName)
{
    Lines = Reader(fileName);
}

Definer::~Definer()
{
}


#endif