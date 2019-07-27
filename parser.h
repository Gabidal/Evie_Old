#ifndef _PARSER_H_
#define _PARSER_H_
#include <string>
#include <map>
#include "keyword.h"
using namespace std;
string parameters;
string parbuffer;
int usedregister = 0;

extern int getWord(char, string&, string, int);

void typeVar(int &index)
{
    string para1;
    string para2;
    string para3;
    index = getWord(' ', para1, parameters, index);
    index = getWord(' ', para2, parameters, index);
    index = getWord(' ', para3, parameters, index);
    parbuffer += "jmp " + para1 + "end";
    parbuffer += "\n[section .data]\n";
    parbuffer += para1 + " dd " + para3;
    parbuffer += "\n[section .text]\n";
    parbuffer += para1 + "end:\n";
}

void typeFunc(int &index)
{
    string para1;
    index = getWord(' ', para1, parameters, index);
    parbuffer += para1 + ":\n";


}

void typeParameter(int &index)
{ // "%1" -> "mov eax, [ebp-4]"
    string para1;
    index = getWord(' ', para1, parameters, index);
    int i = atoi(para1.substr(1).c_str()) * 4;
    parbuffer += "mov ";
    if (usedregister == 3)
    {
        parbuffer += "edx ";
        usedregister = 0;
    }
    else if (usedregister == 2)
    {
        parbuffer += "ecx ";
        usedregister = 3;
    }
    else if (usedregister == 1)
    {
        parbuffer += "ebx ";
        usedregister = 2;
    }
    else if (usedregister == 0)
    {
        parbuffer += "eax ";
        usedregister = 1;
    }
    parbuffer += string(", ") + "[ebp -" + to_string(i) + "]\n";
}

string parser(string destination, string file, int &continu)
{
    parbuffer = "";
    parameters = file;
    if (destination == "var")
    {
        typeVar(continu);
    }
    if (destination == "func")
    {
        typeFunc(continu);
    }
    if (destination.find("%") != -1)
    {
        typeParameter(continu);
    }

    return parbuffer;
}



#endif