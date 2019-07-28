#ifndef _PARSER_H_
#define _PARSER_H_
#include <string>
#include <vector>
#include <map>
using namespace std;
string parameters;
string parbuffer;
int usedregister = 0;
string regbuffer;
vector<string> variables;
map <string, string> varPointers;

extern int getWord(char, string&, string, int);
extern int getReversedIndex(char, string, int);
extern int getReversedWord(char, string&, string, int);

void getFreeReg()
{
    if (usedregister == 3)
    {
        regbuffer = "edx ";
        usedregister = 0;
    }
    else if (usedregister == 2)
    {
        regbuffer = "ecx ";
        usedregister = 3;
    }
    else if (usedregister == 1)
    {
        regbuffer = "ebx ";
        usedregister = 2;
    }
    else if (usedregister == 0)
    {
        regbuffer = "eax ";
        usedregister = 1;
    }
}

void makeVar(int &index)
{
    string para1;
    string para2;
    string para3;
    index = getWord(' ', para1, parameters, index);
    index = getWord(' ', para2, parameters, index);
    index = getWord(' ', para3, parameters, index);
    parbuffer += para1 + " dd " + para3 + "\n";
    variables.push_back(para1);
}

void useVar(int &index, string destination)
{//mov reg, dword [b]
 //mov [a], reg
    string para1;  //register
    string para2;  //[b]
    index = getWord(' ', para2, parameters, index); //skip the '='
    para2 = "";
    index = getWord(' ', para2, parameters, index); //get the [b]
    getFreeReg();
    para1 = regbuffer;
    parbuffer += "\nmov " + para1 + ", dword [" + para2 + "]\n";
    parbuffer += "mov [" + destination + "]" + ", " + para1 + "\n";

    varPointers.insert(make_pair(destination, para1));
}

void doAddition(int &index)
{
    int offset;
    string para1;  //b
    string para2;  //c
    string para3;  //a
    string trash;
    string trash1;
    string trash2;
    // a       = b + c
    offset = getReversedIndex(' ', parameters, index-1); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash

    offset = getReversedIndex(' ', parameters, offset); //b offset
    offset = getReversedWord(' ', para1, parameters, offset); //b 

    offset = getReversedIndex(' ', parameters, offset); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash

    offset = getReversedIndex(' ', parameters, offset); //a offset
    offset = getReversedWord(' ', para3, parameters, offset); //a
    
    index = getWord(' ', para2, parameters, index);  // c
    auto node = varPointers.find(para1);
    if (node != varPointers.end())
    {
        auto node1 = varPointers.find(para1);
        if (node1 != varPointers.end())
        {
            parbuffer += "add " + node->second + ", " + node1->second + "\n";
            parbuffer += "mov [" + para3 + "], " + node->second;
        }
    }
    getFreeReg();
    trash1 = regbuffer;
    parbuffer += "mov " + trash1 + ", dword [" + para1 + "]\n";
    getFreeReg();
    trash2 = regbuffer;
    parbuffer += "mov " + trash2 + ", dword [" + para2 + "]\n";
    parbuffer += "add " + trash1 + ", " + trash2 + "\n";
    parbuffer += "mov [" + para3 + "], " + trash1 + "\n";
}

void makeFunc(int &index)
{
    string para1;
    index = getWord(' ', para1, parameters, index);
    parbuffer += para1 + ":\n";
}


void getParameter(int &index)
{ // "%1" -> "mov reg, dword [var]"
    string para1;
    index = getWord(' ', para1, parameters, index);
}

string parser(string destination, string file, int &continu)
{
    parbuffer = "";
    parameters = file;
    if (destination == "var")
    {
        makeVar(continu);
    }
    if (destination == "func")
    {
        makeFunc(continu);
    }
    if (destination.find("%") != -1)
    {
        getParameter(continu);
    }
    if (destination == "+")
    {
        doAddition(continu);
    }

    //...

    for (int i = 0; i < variables.size();i++)
    {
        if (variables[i] == destination)
        {
            useVar(continu, destination);
        }
    }
    return parbuffer;
}



#endif