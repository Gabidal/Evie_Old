#ifndef _WORD_H_
#define _WORD_H_
#include <vector>
#include <string>
using namespace std;

#define _KEYWORD (1<<0)
#define _UNDEFINED (1<<1)
#define _PAREHTHESIS (1<<2)
#define _END (1<<3)
#define _STRING (1<<4)
#define _NUMBER (1<<5)
#define _COMMENT (1<<6)
#define _OPERATOR (1<<7)
#define _TEXT (1<<8)


class Word
{
private:

public:
    bool UsedToken = false;
    Word *Offsetter = 0;
    string Fetcher = "";
    bool _func = false;
    bool _type = false;
    bool _condition = false;
    bool _else_if = false;
    bool _evaluate = false;
    bool _ptr = false;
    bool _array = false;
	bool _string = false;
	bool _address_operator = false;
    vector<Word*> Tokens;
    int LineNumber = 0;
    string WORD = "";
    int Flags = 0;

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