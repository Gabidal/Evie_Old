#ifndef _MOV_H_
#define _MOV_H_

#include <string>
#include "Token.h"
#include "Register.h"
using namespace std;

static string MakeFrame(Token *t)
{
    string result;
    if (t->is(Member) || t->is(Private))
    {
        result = "[" + t->getFullName() + "]";
    }
    else if (t->is(Public))
    {
        result = "dword [" + t->getFullName() + "]";
    }
    
}

static string InitToken(Token *t)
{
    string result = "";
    if (t->is(Member))
    {
        Register ParentReg = t->ParentType->Reg;
        if (ParentReg.Name == "null")
        {
            //allocate new Register for class address place holding.
            t->ParentType->Reg = t->getReg();
        }
        result = "mov " + ParentReg.Name + ", " + MakeFrame(t) + "\n";
    }
    else if (t->is(Public))
    {
        
    }
    else if (t->is(Equ))
    {
        
    }
    return result;
    
}

static string MOV(Token *Destination, Token *Source)
{
    if ()
    {
        /* code */
    }
    
}

#endif