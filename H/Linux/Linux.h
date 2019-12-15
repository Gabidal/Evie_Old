#ifndef _LINUX_H_
#define _LINUX_H_
#include <string>
#include "../Back/Assembly_Definitions.h"
#include "../Back/Registers.h"
#include "../Back/Token.h"
using namespace std;

class Linux
{
public:
    string Malloc();
    string Raw_Print();
    string Raw_In();
    string Call_Malloc(Token *t);
	string Call_Raw_Print(Token *size, Token *ptrStr);
	string Call_Raw_In(Token* size, Token* ptrStr);
    Linux()
    { 
    }
    ~Linux()
    {
    }
};




#endif