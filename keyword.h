#ifndef _KEYWORD_H_
#define _KEYWORD_H_
#include <iostream>
#include <string>
using namespace std;

class keyword
{
    public:
    string name;
    int paramAmount;
    bool number;
    bool variable;
    keyword(string name, int amount, bool number, bool variable)
    {
        this->name = name;
        paramAmount = amount;
        this->number = number;
        this->variable = variable;
    }
};

#endif