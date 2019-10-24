#ifndef _WORD_H_
#define __WORD_H_
#include <vector>
#include <string>
using namespace std;

#define _KEYWORD (1<<0)
#define _START_PARENTHESIS (1<<1)
#define _END_PARENTHESIS (1<<2)
#define _FUNCTION (1<<3)
#define _FUNCTION_START_PARENTHESIS (1<<4)
#define _FUNCTION_END_PARENTHESIS (1<<5)
#define _TYPE (1<<6)
#define _TYPE_START_PARENTHESIS (1<<7)
#define _TYPE_END_PARENTHESIS (1<<8)
#define _VARIABLE (1<<9)
#define _IF (1<<10)
#define _ELSE (1<<11)
#define _ELSEIF (1<<12)
#define _LOOP (1<<13)
#define _NUMBER (1<<14)
#define _RETURN (1<<15)
#define _PROTOTYPE (1<<16)
#define _OFFSET (1<<17)
#define _PARAMETER (1<<18)
#define _ADDITION (1<<19)
#define _SUBTRACTION (1<<20)
#define _MULTIPLY (1<<21)
#define _DIVIDE (1<<22)
#define _COMMENT (1<<23)
#define _CALL (1<<24)
#define _INCLUDE (1<<25)
#define _VARIABLE_FETCH (1<<26)
#define _FUNCTION_FETCH (1<<27)
#define _LOCATER (1<<28)
#define _NEW (1<<29)
#define _USED (1<<30)
#define _MEMBER (1<<31)
#define _OPERATOR (1<<32)


class Word
{
private:

public:
    int LineNumber = 0;
    string WORD = "";
    int Priority = 0;
    Word *LeftLink;
    Word *RightLink;
    __int128_t Flags = 0;
    bool is(int flag);
    Word(string w);
    ~Word();
};


bool Word::is(int flag)
{
    return (Flags & flag) == flag;
}


Word::Word(string w) : WORD(w)
{}

Word::~Word()
{}


#endif