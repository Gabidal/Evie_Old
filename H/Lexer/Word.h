#ifndef _WORD_H_
#define _WORD_H_
#include <vector>
#include <string>
using namespace std;

#define KEYWORD (1<<0)
#define START_PARENTHESIS (1<<1)
#define END_PARENTHESIS (1<<2)
#define FUNCTION (1<<3)
#define FUNCTION_START_PARENTHESIS (1<<4)
#define FUNCTION_END_PARENTHESIS (1<<5)
#define TYPE (1<<6)
#define TYPE_START_PARENTHESIS (1<<7)
#define TYPE_END_PARENTHESIS (1<<8)
#define VARIABLE (1<<9)
#define IF (1<<10)
#define ELSE (1<<11)
#define ELSEIF (1<<12)
#define LOOP (1<<13)
#define NUMBER (1<<14)
#define RETURN (1<<15)
#define PROTOTYPE (1<<16)
#define OFFSET (1<<17)
#define PARAMETER (1<<18)
#define ADDITION (1<<19)
#define SUBTRACTION (1<<20)
#define MULTIPLY (1<<21)
#define DIVIDE (1<<22)
#define COMMENT (1<<23)
#define CALL (1<<24)
#define INCLUDE (1<<25)
#define VARIABLE_FETCH (1<<26)
#define FUNCTION_FETCH (1<<27)
#define LOCATER (1<<28)
#define NEW (1<<29)
#define USED (1<<30)


class Word
{
private:

public:
    int LineNumber = 0;
    string WORD = "";
    int Priority = 0;
    int Flags = 0;
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