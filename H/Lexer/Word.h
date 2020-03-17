#ifndef _WORD_H_
#define _WORD_H_
#include <vector>
#include <string>
using namespace std;

constexpr int _KEYWORD(1 << 0);
constexpr int _UNDEFINED(1 << 1);
constexpr int _PAREHTHESIS(1 << 2);
constexpr int _END(1 << 3);
constexpr int _STRING(1 << 4);
constexpr int _NUMBER(1 << 5);
constexpr int _COMMENT(1 << 6);
constexpr int _OPERATOR(1 << 7);
constexpr int _TEXT(1 << 8);


class Word
{
private:

public:
    bool UsedToken = false;
    bool Self_Mirroring = false;
    bool _initted = false;
    bool _operatorized = false;
    bool _Call = false;
    bool _Giving_Address = false;
    int LineNumber = 0;
    int Flags = 0;
    string Fetcher = "";
    string _Pre_Modded = "";
    vector<Word*> Tokens;
    Word* Offsetter = nullptr;
    Word* L = nullptr;
    Word* R = nullptr;
    string WORD = "";

    bool is(int flag)
    {
        return (Flags & flag) == flag;
    }
    Word(string w) : WORD(w)
    {}
    
    ~Word()
    {}
};



#endif