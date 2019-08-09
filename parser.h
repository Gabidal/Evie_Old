#ifndef _PARSER_H_
#define _PARSER_H_
#include <string>
#include <vector>
#include <map>
#include <ctype.h>
#include <algorithm>
using namespace std;
string parameters;
string varbuffer;
string codbuffer;
string texbuffer;
string includes2;
int usedregister = 0;
string regbuffer;
int inLayer = 0;
int layerId = 0;
int returnLayer = 0;
int savedIfToElse = 0;
int savedElseToEnd = 0;
vector<string> LocalizedVariableNames;
vector<string> ifToElse;
vector<string> elseToEnd;
vector<string> jumpToEnd;
map<string, bool> variables;            //true == global; false == local
map <string, string> varPointers;
map <string, string> ArrayVariables;
vector<string> functions;
vector<string> localVars;
map<string, int> Types;
int localVarLocation;

vector<string> className;  //className . functionName:

extern int getError(char, string&, string, int, string&);
extern int getWord(char, string&, string, int);
extern int getReversedIndex(char, string, int);
extern int getReversedWord(char, string&, string, int);
extern string readFile(string name);

string sx()
{
    string spaces = "";
    for (int i = 0; i < inLayer; i++)
    {
        spaces += " ";
    }
    return spaces;
}

string autoValue(string normalSize, string multiplyer, int layer)
{
    if (multiplyer.size() > 0)
    {
        return normalSize + "*" + multiplyer + "*" + to_string(layer);
    }
    else
    {
        return normalSize;
    }
    
}

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

bool ifVarIsLocal(string name)
{
    string addition = "";
    if (LocalizedVariableNames.back() == " ")
    {
        addition = className.back();
    }
    else
    {
        addition = className.back() + LocalizedVariableNames.back() + ".";
    }
    
    auto node1 = variables.find(addition + name);
    if (node1 != variables.end())
    {
        if (node1->second == true)
        {
            return false;
        }
        else
        {
            return true;
        }
        
    }
    else
    {
        return false;
    }
    
}

string autoName(string name)
{
    bool isit = ifVarIsLocal(name);
    if (isit)
    {
        if (LocalizedVariableNames.back() == " ")
        {
            return className.back() + name;
        }
        else
        {
            return className.back() + LocalizedVariableNames.back() + "." + name;
        }
        
    }
    else
    {
        return name;
    }
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
    // a  = b + c
    offset = getReversedIndex(' ', parameters, index-1); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //b offset
    offset = getReversedWord(' ', para1, parameters, offset); //b 
    reverse(para1.begin(), para1.end());

    offset = getReversedIndex(' ', parameters, offset); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //a offset
    offset = getReversedWord(' ', para3, parameters, offset); //a
    reverse(para3.begin(), para3.end());
    
    index = getWord(' ', para2, parameters, index);  // c

    auto node = varPointers.find(autoName(para1));
    if (node != varPointers.end())
    {
        auto node1 = varPointers.find(autoName(para2));
        if (node1 != varPointers.end())
        {
            codbuffer += sx() + "add " + node->second + ", " + node1->second + "\n";
            codbuffer += sx() + "mov [" + autoName(para3) + "], " + node->second + "\n";
        }
        else
        {
            getFreeReg();
            string reg1 = regbuffer;
            codbuffer += sx() + "mov " + reg1 + ", dword [" + autoName(para2) + "]\n";
            codbuffer += sx() +  "add " + node->second + ", " + reg1 + "\n";
            codbuffer += sx() +  "mov [" + autoName(para3) + "], " + node->second + "\n";
            varPointers.insert(make_pair(para2, reg1));
        }
    }
    else
    {

        getFreeReg();
        trash1 = regbuffer;
        codbuffer += sx() +  "mov " + trash1 + ", dword [" + autoName(para1) + "]\n";
        getFreeReg();
        trash2 = regbuffer;
        codbuffer += sx() +  "mov " + trash2 + ", dword [" + autoName(para2) + "]\n";
        codbuffer += sx() +  "add " + trash1 + ", " + trash2 + "\n";
        codbuffer += sx() +  "mov [" + autoName(para3) + "], " + trash1 + "\n";
            varPointers.insert(make_pair(autoName(para1), trash1));
            varPointers.insert(make_pair(autoName(para2), trash2));
    }
}

void doSubstraction(int &index)
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
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //b offset
    offset = getReversedWord(' ', para1, parameters, offset); //b 
    reverse(para1.begin(), para1.end());

    offset = getReversedIndex(' ', parameters, offset); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //a offset
    offset = getReversedWord(' ', para3, parameters, offset); //a
    reverse(para3.begin(), para3.end());
    
    index = getWord(' ', para2, parameters, index);  // c
    auto node = varPointers.find(autoName(para1));
    if (node != varPointers.end())
    {
        auto node1 = varPointers.find(autoName(para2));
        if (node1 != varPointers.end())
        {
            codbuffer += sx() +  "sub " + node->second + ", " + node1->second + "\n";
            codbuffer += sx() +  "mov [" + autoName(para3) + "], " + node1->second + "\n";
        }
        else
        {
            getFreeReg();
            string reg1 = regbuffer;
            codbuffer += sx() +  "mov " + reg1 + ", dword [" + autoName(para2) + "]\n";
            codbuffer += sx() +  "sub " + node->second + ", " + reg1 + "\n";
            codbuffer += sx() +  "mov [" + autoName(para3) + "], " + node->second + "\n";
            varPointers.insert(make_pair(para2, reg1));
        }
    }
    else
    {
        getFreeReg();
        trash1 = regbuffer;
        codbuffer += sx() +  "mov " + trash1 + ", dword [" + autoName(para1) + "]\n";
        getFreeReg();
        trash2 = regbuffer;
        codbuffer += sx() +  "mov " + trash2 + ", dword [" + autoName(para2) + "]\n";
        codbuffer += sx() +  "sub " + trash1 + ", " + trash2 + "\n";
        codbuffer += sx() +  "mov [" + autoName(para3) + "], " + trash1 + "\n";
            varPointers.insert(make_pair(autoName(para1), trash1));
            varPointers.insert(make_pair(autoName(para2), trash2));
    }
}

void doMultiply(int &index)
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
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //b offset
    offset = getReversedWord(' ', para1, parameters, offset); //b 
    reverse(para1.begin(), para1.end());

    offset = getReversedIndex(' ', parameters, offset); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //a offset
    offset = getReversedWord(' ', para3, parameters, offset); //a
    reverse(para3.begin(), para3.end());
    
    index = getWord(' ', para2, parameters, index);  // c
    auto node = varPointers.find(autoName(para1));
    if (node != varPointers.end())
    {
        auto node1 = varPointers.find(autoName(para2));
        if (node1 != varPointers.end())
        {
            codbuffer += sx() +  "mov eax, " + node->second + "\n";
            codbuffer += sx() +  "mul " + node->second + "\n";
            codbuffer += sx() +  "mov [" + autoName(para3) + "], eax\n";
            codbuffer += sx() +  "mov " + node1->second + ", eax\n";
        }
        else
        {
            getFreeReg();
            string reg1 = regbuffer;
            codbuffer += sx() +  "mov eax, " + node->second + "\n";
            codbuffer += sx() +  "mov " + reg1 + ", dword [" + autoName(para2) + "]\n";
            codbuffer += sx() +  "mul " + reg1 + "\n";
            codbuffer += sx() +  "mov [" + autoName(para3) + "], eax\n";
            codbuffer += sx() +  "mov " + reg1 + ", eax\n";
            varPointers.insert(make_pair(para2, reg1));

        }
    }
    else
    {
        getFreeReg();
        trash1 = regbuffer;
        codbuffer += sx() +  "mov " + trash1 + ", dword [" + autoName(para1) + "]\n";
        getFreeReg();
        trash2 = regbuffer;
        codbuffer += sx() +  "mov " + trash2 + ", dword [" + autoName(para2) + "]\n";
            codbuffer += sx() +  "mov eax, " + trash1 + "\n";
            codbuffer += sx() +  "mul " + trash2 + "\n";
            codbuffer += sx() +  "mov [" + autoName(para3) + "], eax\n";
            codbuffer += sx() +  "mov " + trash2 + ", eax\n";
            varPointers.insert(make_pair(para1, trash1));
            varPointers.insert(make_pair(para2, trash2));
    }
}

void doAND(int &index)
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
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //b offset
    offset = getReversedWord(' ', para1, parameters, offset); //b 
    reverse(para1.begin(), para1.end());

    offset = getReversedIndex(' ', parameters, offset); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //a offset
    offset = getReversedWord(' ', para3, parameters, offset); //a
    reverse(para3.begin(), para3.end());
    
    index = getWord(' ', para2, parameters, index);  // c
    auto node = varPointers.find(para1);
    if (node != varPointers.end())
    {
        auto node1 = varPointers.find(para2);
        if (node1 != varPointers.end())
        {
            codbuffer += sx() + "and " + node->second + ", " + node1->second + "\n";
            codbuffer += sx() + "mov [" + para3 + "], " + node->second + "\n";
        }
        else
        {
            getFreeReg();
            string reg1 = regbuffer;
            codbuffer += sx() + "mov " + reg1 + ", dword [" + para2 + "]\n";
            codbuffer += sx() +  "and " + node->second + ", " + reg1 + "\n";
            codbuffer += sx() +  "mov [" + para3 + "], " + node->second + "\n";
            varPointers.insert(make_pair(para2, reg1));
        }
    }
    else
    {
        getFreeReg();
        trash1 = regbuffer;
        codbuffer += sx() +  "mov " + trash1 + ", dword [" + para1 + "]\n";
        getFreeReg();
        trash2 = regbuffer;
        codbuffer += sx() +  "mov " + trash2 + ", dword [" + para2 + "]\n";
        codbuffer += sx() +  "and " + trash1 + ", " + trash2 + "\n";
        codbuffer += sx() +  "mov [" + para3 + "], " + trash1 + "\n";
            varPointers.insert(make_pair(para1, trash1));
            varPointers.insert(make_pair(para2, trash2));
    }
}

void doNAND(int &index)
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
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //b offset
    offset = getReversedWord(' ', para1, parameters, offset); //b 
    reverse(para1.begin(), para1.end());

    offset = getReversedIndex(' ', parameters, offset); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //a offset
    offset = getReversedWord(' ', para3, parameters, offset); //a
    reverse(para3.begin(), para3.end());
    
    index = getWord(' ', para2, parameters, index);  // c
    auto node = varPointers.find(para1);
    if (node != varPointers.end())
    {
        auto node1 = varPointers.find(para2);
        if (node1 != varPointers.end())
        {
            codbuffer += sx() + "and " + node->second + ", " + node1->second + "\n";
            codbuffer += sx() + "not " + node->second + "\n";
            codbuffer += sx() + "mov [" + para3 + "], " + node->second + "\n";
        }
        else
        {
            getFreeReg();
            string reg1 = regbuffer;
            codbuffer += sx() + "mov " + reg1 + ", dword [" + para2 + "]\n";
            codbuffer += sx() +  "and " + node->second + ", " + reg1 + "\n";
            codbuffer += sx() + "not " + node->second + "\n";
            codbuffer += sx() +  "mov [" + para3 + "], " + node->second + "\n";
            varPointers.insert(make_pair(para2, reg1));
        }
    }
    else
    {
        getFreeReg();
        trash1 = regbuffer;
        codbuffer += sx() +  "mov " + trash1 + ", dword [" + para1 + "]\n";
        getFreeReg();
        trash2 = regbuffer;
        codbuffer += sx() +  "mov " + trash2 + ", dword [" + para2 + "]\n";
        codbuffer += sx() +  "and " + trash1 + ", " + trash2 + "\n";
        codbuffer += sx() + "not " + trash1 + "\n";
        codbuffer += sx() +  "mov [" + para3 + "], " + trash1 + "\n";
            varPointers.insert(make_pair(para1, trash1));
            varPointers.insert(make_pair(para2, trash2));
    }
}

void doNOR(int &index)
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
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //b offset
    offset = getReversedWord(' ', para1, parameters, offset); //b 
    reverse(para1.begin(), para1.end());

    offset = getReversedIndex(' ', parameters, offset); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //a offset
    offset = getReversedWord(' ', para3, parameters, offset); //a
    reverse(para3.begin(), para3.end());
    
    index = getWord(' ', para2, parameters, index);  // c
    auto node = varPointers.find(para1);
    if (node != varPointers.end())
    {
        auto node1 = varPointers.find(para2);
        if (node1 != varPointers.end())
        {
            codbuffer += sx() + "or " + node->second + ", " + node1->second + "\n";
            codbuffer += sx() + "not " + node->second + "\n";
            codbuffer += sx() + "mov [" + para3 + "], " + node->second + "\n";
        }
        else
        {
            getFreeReg();
            string reg1 = regbuffer;
            codbuffer += sx() + "mov " + reg1 + ", dword [" + para2 + "]\n";
            codbuffer += sx() +  "or " + node->second + ", " + reg1 + "\n";
            codbuffer += sx() + "not " + node->second + "\n";
            codbuffer += sx() +  "mov [" + para3 + "], " + node->second + "\n";
            varPointers.insert(make_pair(para2, reg1));
        }
    }
    else
    {
        getFreeReg();
        trash1 = regbuffer;
        codbuffer += sx() +  "mov " + trash1 + ", dword [" + para1 + "]\n";
        getFreeReg();
        trash2 = regbuffer;
        codbuffer += sx() +  "mov " + trash2 + ", dword [" + para2 + "]\n";
        codbuffer += sx() +  "or " + trash1 + ", " + trash2 + "\n";
        codbuffer += sx() + "not " + trash1 + "\n";
        codbuffer += sx() +  "mov [" + para3 + "], " + trash1 + "\n";
            varPointers.insert(make_pair(para1, trash1));
            varPointers.insert(make_pair(para2, trash2));
    }
}

void doXOR(int &index)
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
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //b offset
    offset = getReversedWord(' ', para1, parameters, offset); //b 
    reverse(para1.begin(), para1.end());

    offset = getReversedIndex(' ', parameters, offset); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //a offset
    offset = getReversedWord(' ', para3, parameters, offset); //a
    reverse(para3.begin(), para3.end());
    
    index = getWord(' ', para2, parameters, index);  // c
    auto node = varPointers.find(para1);
    if (node != varPointers.end())
    {
        auto node1 = varPointers.find(para2);
        if (node1 != varPointers.end())
        {
            codbuffer += sx() + "xor " + node->second + ", " + node1->second + "\n";
            codbuffer += sx() + "mov [" + para3 + "], " + node->second + "\n";
        }
        else
        {
            getFreeReg();
            string reg1 = regbuffer;
            codbuffer += sx() + "mov " + reg1 + ", dword [" + para2 + "]\n";
            codbuffer += sx() +  "xor " + node->second + ", " + reg1 + "\n";
            codbuffer += sx() +  "mov [" + para3 + "], " + node->second + "\n";
            varPointers.insert(make_pair(para2, reg1));
        }
    }
    else
    {
        getFreeReg();
        trash1 = regbuffer;
        codbuffer += sx() +  "mov " + trash1 + ", dword [" + para1 + "]\n";
        getFreeReg();
        trash2 = regbuffer;
        codbuffer += sx() +  "mov " + trash2 + ", dword [" + para2 + "]\n";
        codbuffer += sx() +  "xor " + trash1 + ", " + trash2 + "\n";
        codbuffer += sx() +  "mov [" + para3 + "], " + trash1 + "\n";
            varPointers.insert(make_pair(para1, trash1));
            varPointers.insert(make_pair(para2, trash2));
    }
}

void doOR(int &index)
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
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //b offset
    offset = getReversedWord(' ', para1, parameters, offset); //b 
    reverse(para1.begin(), para1.end());

    offset = getReversedIndex(' ', parameters, offset); //trash offset
    offset = getReversedWord(' ', trash, parameters, offset); //trash
    reverse(trash.begin(), trash.end());

    offset = getReversedIndex(' ', parameters, offset); //a offset
    offset = getReversedWord(' ', para3, parameters, offset); //a
    reverse(para3.begin(), para3.end());
    
    index = getWord(' ', para2, parameters, index);  // c
    auto node = varPointers.find(para1);
    if (node != varPointers.end())
    {
        auto node1 = varPointers.find(para2);
        if (node1 != varPointers.end())
        {
            codbuffer += sx() + "or " + node->second + ", " + node1->second + "\n";
            codbuffer += sx() + "mov [" + para3 + "], " + node->second + "\n";
        }
        else
        {
            getFreeReg();
            string reg1 = regbuffer;
            codbuffer += sx() + "mov " + reg1 + ", dword [" + para2 + "]\n";
            codbuffer += sx() +  "or " + node->second + ", " + reg1 + "\n";
            codbuffer += sx() +  "mov [" + para3 + "], " + node->second + "\n";
            varPointers.insert(make_pair(para2, reg1));
        }
    }
    else
    {
        getFreeReg();
        trash1 = regbuffer;
        codbuffer += sx() +  "mov " + trash1 + ", dword [" + para1 + "]\n";
        getFreeReg();
        trash2 = regbuffer;
        codbuffer += sx() +  "mov " + trash2 + ", dword [" + para2 + "]\n";
        codbuffer += sx() +  "or " + trash1 + ", " + trash2 + "\n";
        codbuffer += sx() +  "mov [" + para3 + "], " + trash1 + "\n";
            varPointers.insert(make_pair(para1, trash1));
            varPointers.insert(make_pair(para2, trash2));
    }
}
void makeVar(int &index)
{
    string para1;
    string para2;
    string para3;
    index = getWord(' ', para1, parameters, index);  //name
    index = getWord(' ', para2, parameters, index);  // = or :
    index = getWord(' ', para3, parameters, index);  // value or size
    if (para2 == ":")
    {
        if (LocalizedVariableNames.back() == " ")
        {
            varbuffer += className.back() + para1 + " times " + para3 + " dd 0\n";
            variables.insert(make_pair(className.back() + para1, true));
        }
        else
        {
            varbuffer += className.back() + LocalizedVariableNames.back() + para1 + " times " + para3 + " dd 0\n";
            variables.insert(make_pair(className.back() + LocalizedVariableNames.back() + para1, false));
        }
        ArrayVariables.insert(make_pair(para1, para3));
    }
    else
    {
        if (LocalizedVariableNames.back() == " ")
        {
            varbuffer += className.back() + para1 + " dd " + para3 + "\n";
            variables.insert(make_pair(className.back() + para1, true));
        }
        else
        {
            varbuffer += className.back() + LocalizedVariableNames.back() + para1 + " dd " + para3 + "\n";
            variables.insert(make_pair(className.back() + LocalizedVariableNames.back() + para1, false));
        }
    }
}

void callFunction(string function, int &index)
{
    while (true)
    {
        string para1;
        string error;
        int offset = getError(' ', para1, parameters, index, error);
        if (para1.length() > 0) 
        {
            auto node = varPointers.find(para1);
            if (node != varPointers.end())
            {
                codbuffer += sx() + "push " + node->second + "\n";
            }
            else
            {
                getFreeReg();
                string reg1 = regbuffer;
                codbuffer += sx() + "push " + "dword [" + autoName(para1) + "]\n";
            }
            
        }
        if (error != "\n")
        {
            index = offset;
        }
        else
        {
            break;
        }
    }
    codbuffer += sx() +   "call " + function + "\n";
}

string getReturn()
{
            auto node = varPointers.find("return");
            if (node != varPointers.end())
            {
                return node->second;
            }
            else
            {
                getFreeReg();
                string returnreg = regbuffer;
                codbuffer += sx() + "mov " + returnreg + ", dword [return]\n";
                varPointers.insert(make_pair("return", returnreg));
                return returnreg;
            }
            //return "  G::Error: return not found";
}

void useVar(int &index, string destination)
{
    string reg1;  //register
    string para2;  //[b]
    string para3;  // = or :
    index = getWord(' ', para3, parameters, index); //get the = or :
    index = getWord(' ', para2, parameters, index); //get the [b]
    getFreeReg();
    reg1 = regbuffer;
    auto varOnReg = varPointers.find(autoName(para2));
    if (para3 == ":")
    {
        if (isdigit(para2.at(0)))
        {
            string value;
            index = getWord(' ', value, parameters, index);
            value = "";
            index = getWord(' ', value, parameters, index);
            getFreeReg();
            string reg2 = regbuffer;
            auto node = varPointers.find(autoName(value));
            if (node != varPointers.end())
            {
                auto node1 = variables.find(autoName(destination));
                if (node1 != variables.end())
                {
                    codbuffer += sx() + "lea esi, " + autoName(destination) + "[4*(" + para2 + ")]\n";
                }
                codbuffer += sx() +  "mov [esi], " + node->second + "\n";
            }
            else
            {
                getFreeReg();
                string reg3 = regbuffer;
                codbuffer += sx() +  "mov " + reg3 + ", dword [" + autoName(value) + "]\n";
                varPointers.insert(make_pair(autoName(value), reg3));
                auto node1 = variables.find(autoName(destination));
                if (node1 != variables.end())
                {
                    codbuffer += sx() + "lea esi, " + autoName(destination) + "[4*(" + para2 + ")]\n";
                }
                codbuffer += sx() +  "mov [esi], " + reg3 + "\n";
            }
            if (isdigit(value.at(0)))
            {
                codbuffer += sx() +  "mov " + reg2 + ", " + value + "\n";
                auto node1 = variables.find(autoName(destination));
                if (node1 != variables.end())
                {
                    codbuffer += sx() + "lea esi, " + autoName(destination) + "[4*(" + para2 + ")]\n";
                }
                codbuffer += sx() +  "mov [esi], " + reg2 + "\n";
            }
        }
        else
        {
            auto node2 = variables.find(autoName(para2));
            if (node2 != variables.end())
            {
                    codbuffer += sx() +  "mov esi, dword [" + autoName(para2) + "]\n";
            }
            string value;
            auto node1 = variables.find(autoName(destination));
            if (node1 != variables.end())
            {
                codbuffer += sx() +  "lea esi, " + autoName(destination) + "[esi*4]\n";
            }
            index = getWord(' ', value, parameters, index);
            value = "";
            index = getWord(' ', value, parameters, index);
            if (isdigit(value.at(0)))
            {
                getFreeReg();
                codbuffer += sx() + "mov " + regbuffer + ", " + value + "\n";
                codbuffer += sx() + "mov [esi], " + regbuffer + "\n";
            }
            else
            {
                auto node = varPointers.find(autoName(value));
                if (node != varPointers.end())
                {
                    codbuffer += sx() +  "mov [esi], " + node->second + "\n";
                }
                else
                {
                    getFreeReg();
                    string reg2 = regbuffer;
                    auto node2 = variables.find(value);
                    if (node2 != variables.end())
                    {
                        codbuffer += sx() +  "mov " + reg2 + ", dword [" + autoName(value) + "]\n";
                    }
                    varPointers.insert(make_pair(autoName(value), reg2));
                    codbuffer += sx() +  "mov [esi], " + reg2 + "\n";
                }
            }
        }
    }
    else
    {
        string isArray;
        string value;
        int offset;
        offset = getWord(' ', isArray, parameters, index); //check for :
        offset = getWord(' ', value, parameters, offset); //get the value
        if (isArray == ":")
        {
            index = offset;
            auto node1 = varPointers.find(autoName(value));
            if (node1 != varPointers.end())
            {
                codbuffer += sx() +  "mov esi, " + node1->second + "\n";
            }
            else
            {
                if (isdigit(value.at(0)))
                {
                getFreeReg();
                string reg2 = regbuffer;
                codbuffer += sx() +  "mov esi, " + value + "\n";
                }
                else
                {
                getFreeReg();
                string reg2 = regbuffer;
                auto node2 = variables.find(autoName(value));
                if (node2 != variables.end())
                {
                    codbuffer += sx() +  "mov " + reg2 + ", dword [" + autoName(value) + "]\n";
                }
                varPointers.insert(make_pair(value, reg2));
                codbuffer += sx() +  "mov esi, " + reg2 + "\n";
                }
            }
            auto node2 = varPointers.find(autoName(destination));
            if (node2 != varPointers.end())
            {
                auto node3 = variables.find(autoName(para2));
                if (node3 != variables.end())
                {
                    codbuffer += sx() + "lea esi, " + autoName(para2) + "[esi * 4]\n"; 
                }
                codbuffer += sx() + "mov " + node1->second + ", dword [esi]\n";
            }
            else
            {
                getFreeReg();
                string reg2 = regbuffer;
                varPointers.insert(make_pair(destination, reg2));
                auto node2 = variables.find(para2);
                if (node2 != variables.end())
                {
                    codbuffer += sx() + "lea esi, dword " + autoName(para2) + "[esi * 4]\n";
                }
                codbuffer += sx() + "mov " + reg2 + ", dword " + "[esi]\n";
                auto node3 = variables.find(destination);
                if (node3 != variables.end())
                {
                    codbuffer += sx() + "mov [" + autoName(destination) + "], " + reg2 + "\n";
                }

            }

        }
        else
        {
            bool para2IsFunction = false;
            for (int i = 0; i < functions.size(); i++)
            {
                if (functions[i] == para2)
                {
                    para2IsFunction = true;
                }
            }
            if (para2IsFunction)
            {
                callFunction(para2, index);
                index = getWord(' ', para2, parameters, index);
                codbuffer += sx() + "mov [" + autoName(destination) + "], " + getReturn() + "\n";
            }
            else
            {
                if (varOnReg != varPointers.end())
                {
                    string para4;
                    para4 = varOnReg->second;
                    auto node = variables.find(autoName(destination));
                    if (node != variables.end())
                    {
                        codbuffer += sx() +  "mov [" + autoName(destination) + "] , " + para4 + "\n";
                    }
                }
                else
                {
                    getFreeReg();
                    string reg2 = regbuffer;
                    auto node = variables.find(autoName(destination));
                    if (node != variables.end())
                    {
                        codbuffer += sx() +  "mov " + reg1 + ", dword [" + autoName(para2) + "]\n";
                    }
                    /* codbuffer += sx() + "mov " + reg2 + ", " + reg1 + "\n";
                    auto node1 = variables.find(destination);
                    if (node1 != variables.end())
                    {
                        if (node1->second == true)
                        {
                            codbuffer += sx() +  "mov [" + destination + "] , " + reg1 + "\n";
                        }
                        else
                        {
                            codbuffer += sx() +  "mov [" + var() + destination + "] , " + reg1 + "\n";
                        }
                        
                    }*/
                    varPointers.insert(make_pair(autoName(para2), reg1));
                    varPointers.insert(make_pair(autoName(destination), reg1));
                }
            }
        }
    }
}

void doReturn()
{
    codbuffer += sx() + "mov esp, ebp\n" + sx() + "pop ebp\n";
    codbuffer += sx() +  "ret\n\n";
    localVarLocation = 0;
    localVars.clear();
    LocalizedVariableNames.pop_back();
}
void makeFunc(int &index)
{
    string para1;
    index = getWord(' ', para1, parameters, index);
    codbuffer += sx() + className.back() +  para1 + ":\n";
    functions.push_back(className.back() + para1);
    returnLayer++;
    vector<string> paraOrder;
    string reg1 = regbuffer;
    int i = 0;
    vector<string> localPointers;
    while (true)
    {
        string para2;
        string error;
        int offset = getError(' ', para2, parameters, index, error);
        if (para2.length() > 0) 
        {
            if (para2.find('%')!= string::npos)
            {
                localPointers.push_back(para2);
            }
            else
            {
                localVars.push_back(para2);
            }
        }
        if (parameters[offset-2] == '\n')
        {
            break;
        }
        if (error != "\n")
        {
            index = offset;
        }
        else
        {
            break;
        }
        i++;
    }

    codbuffer += sx() + "push ebp\n" + sx() + "mov ebp, esp\n";
    codbuffer += sx() + "sub esp, " + to_string(localVars.size() * 4) + "\n";
    LocalizedVariableNames.push_back(para1);

    for (int i = 0; 0 < localPointers.size(); i++)
    {
        getFreeReg();
        string reg2 = regbuffer;
        string para3 = localPointers.back();
        localPointers.pop_back();
        para3 = para3.substr(1);
        codbuffer += sx() + "mov " + reg2 + ", [ebp+" + to_string(4 * i + 8) + "]\n";
        varbuffer += className.back() + LocalizedVariableNames.back() + "." + para3 + " dd 0\n";
        codbuffer += sx() + "mov [" + className.back() + LocalizedVariableNames.back() + "." + para3 + "], " + reg2 + "\n";
        varPointers.insert(make_pair(className.back() + LocalizedVariableNames.back() + "." + para3, reg2));
        variables.insert(make_pair(className.back() + LocalizedVariableNames.back() + "." + para3, false));
    }
    for (int i = 0; 0 < localVars.size(); i++)
    {
        getFreeReg();
        string reg2 = regbuffer;
        string para3 = localVars.back();
        localVars.pop_back();
        codbuffer += sx() + "mov " + reg2 + ", [ebp+" + to_string(4 * i + 8) + "]\n";
        varbuffer += className.back() + LocalizedVariableNames.back()  + "." + para3 + " dd 0\n";
        codbuffer += sx() + "mov [" + className.back() + LocalizedVariableNames.back() + "." +  para3 + "], " + reg2 + "\n";
        varPointers.insert(make_pair(className.back() + LocalizedVariableNames.back() + "." + para3, reg2));
        variables.insert(make_pair(className.back() + LocalizedVariableNames.back() + "." + para3, false));
    }

}

string getJump(string condition)
{
    if (condition == "==")
    {
        return "jne ";
    }
    if (condition == "!=")
    {
        return "je ";
    }
    if (condition == ">")
    {
        return "jle ";
    }
    if (condition == "<")
    {
        return "jge ";
    }
    if (condition == "!>")
    {
        return "jg ";
    }
    if (condition == "!<")
    {
        return "jl ";
    }
    if (condition == "=>")
    {
        return "jl ";
    }
    if (condition == "=<")
    {
        return "jg ";
    }
    else
    {
        return "jmp ";
    }
}

void doComparing(int &i)
{
    string para1;  //a
    string para2;  // ==
    string para3;  //b
    i = getWord(' ', para1, parameters, i);
    i = getWord(' ', para2, parameters, i);
    i = getWord(' ', para3, parameters, i);
    para2 = getJump(para2);
    auto reg1 = varPointers.find(para1);
    auto reg2 = varPointers.find(para3);
    if (reg1 != varPointers.end())
    {
        if (reg2 != varPointers.end())
        {
            codbuffer += sx() +   "cmp " + reg1->second + ", " + reg2->second + "\n";
        }
        else
        {
            getFreeReg();
            para1 = regbuffer;
            codbuffer += sx() +   "mov " + para1 + ", dword [" + autoName(para3) + "]\n";
            codbuffer += sx() +   "cmp " + reg1->second + ", " + para1 + "\n";
            varPointers.insert(make_pair(autoName(para3), para1));
        }
    }
    else
    {
        getFreeReg();
        string reg3 = regbuffer;
        getFreeReg();
        string reg4 = regbuffer;
        codbuffer += sx() +   "mov " + reg3 + ", dword [" + autoName(para1) + "]\n";
        codbuffer += sx() +   "mov " + reg4 + ", dword [" + autoName(para3) + "]\n";
        codbuffer += sx() +   "cmp " + reg3 + ", " + reg4 + "\n";
        varPointers.insert(make_pair(autoName(para1), reg3));
        varPointers.insert(make_pair(autoName(para3), reg4));
    }
    inLayer++;
    layerId++;
    codbuffer += sx() +   para2 + "else" + to_string(inLayer) + to_string(layerId) + "\n";
    ifToElse.push_back(sx() + "else" + to_string(inLayer) + to_string(layerId) + ": \n");
    elseToEnd.push_back(sx() + "end" + to_string(inLayer) + to_string(layerId) + ": \n");
    jumpToEnd.push_back(sx() + "jmp end" + to_string(inLayer) + to_string(layerId) + "\n");
    savedIfToElse++;
    savedElseToEnd++;
}

void doElse()
{
    savedIfToElse--;
    savedElseToEnd--;
    codbuffer += jumpToEnd.back();
    codbuffer += ifToElse.back();
    jumpToEnd.pop_back();
    ifToElse.pop_back();
}

void doEnd()
{
    codbuffer += elseToEnd.back();
    elseToEnd.pop_back();
    inLayer--;
}

bool replace(string& str, const string& from, const string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void doInclude(int &i)
{
    int offset;
    string including;
    //string name;
    i -= 4;
    i = getWord('\n', including, parameters, i);
    replace(parameters, including, "");
    replace(including, "use ", "");
    includes2 = readFile(including);
    i = 0;
}

void makeNewType(int &index)
{
    string typeName;
    index = getWord(' ', typeName, parameters, index);
    Types.insert(make_pair(typeName, 0));
    className.push_back(typeName + ".");
}

void endType()
{
    className.pop_back();
}

void makeNew(int &index)
{
    string TypeName;
    string newTypeBranch;
    string ifNewBranchIsArray;
    string ArraySize = "";
    int initialSize = 0;
    index = getWord(' ', TypeName, parameters, index);
    index = getWord(' ', newTypeBranch, parameters, index);
    int offset = getWord(' ', ifNewBranchIsArray, parameters, index);
    if (ifNewBranchIsArray == ":")
    {
        index = offset;
        index = getWord(' ', ArraySize, parameters, index);
    }
    vector<string> LocalTypeVariables;
    vector<string> newBranchVariables;

    for (auto& i : variables) 
    {
        if (i.first.find(TypeName) != -1) 
        {
            LocalTypeVariables.push_back(i.first);
        }
    }
    for (int i = 0; 0 < LocalTypeVariables.size(); i++)
    {
        int offset = 0;
        string dest = "";
        int exponent = 0;
        reverse(LocalTypeVariables.back().begin(), LocalTypeVariables.back().end());
        offset = getWord('.', dest,LocalTypeVariables.back(), offset);
        reverse(dest.begin(), dest.end());
        for (auto& vars : variables) 
        {
            for (auto &j : Types)
            {
                string test = "";
                test = j.first + "." + dest;
                if (vars.first.find(test) != -1) 
                {
                    exponent++;
                    exponent++;
                }
            }
        }
        newBranchVariables.push_back(dest);
        LocalTypeVariables.pop_back();
        auto node1 = ArrayVariables.find(dest);
        if (node1 != ArrayVariables.end())
        {
            varbuffer += newTypeBranch + "." + newBranchVariables.back() + " times " + autoValue(node1->second, ArraySize, exponent) + " dd 0\n";
            variables.insert(make_pair(newTypeBranch + "." + newBranchVariables.back(), true));
            Types.insert(make_pair(newTypeBranch, (atoi(ArraySize.c_str()) * atoi(node1->second.c_str()) * exponent)));
        }
        else
        {
            varbuffer += newTypeBranch + "." + newBranchVariables.back() + " dd 0\n";
            variables.insert(make_pair(newTypeBranch + "." + newBranchVariables.back(), true));
        }
        newBranchVariables.pop_back();
    }
}

void parser(string destination, string &file, int &continu, string &varbuffer1, string &codbuffer1, string &texbuffer1, string &includes1)
{
    codbuffer = "";
    texbuffer = "";
    varbuffer = "";
    parameters = file;
    if (destination == "var")
    {
        makeVar(continu);
    }
    if (destination == "type")
    {
        makeNewType(continu);
    }
    if (destination == ";")
    {
        endType();
    }
    if (destination == "func")
    {
        makeFunc(continu);
    }
    if (destination == "+")
    {
        doAddition(continu);
    }
    if (destination == "-")
    {
        doSubstraction(continu);
    }
    if (destination == "&")
    {
        doAND(continu);
    }
    if (destination == "!&")
    {
        doNAND(continu);
    }
    if (destination == "!||")
    {
        doNOR(continu);
    }
    if (destination == "!|")
    {
        doXOR(continu);
    }
    if (destination == "||")
    {
        doOR(continu);
    }
    if (destination == "*")
    {
        for (auto it = varPointers.rbegin(); it != varPointers.rend(); it++) {
            if (it->second == "eax ")
            {
                varPointers.erase(it->second);
            }
        }

        for (auto node : varPointers) 
        {
            
        }
        doMultiply(continu);
    }
    if (destination == "ret")
    {
        doReturn();
    }
    if (destination == "if")
    {
        doComparing(continu);
    }
    if (destination == "else")
    {
        doElse();
    }
    if (destination == "end")
    {
        doEnd();
    }
    if (destination == "use")
    {
        doInclude(continu);
    }
    if (destination == "new")
    {
        makeNew(continu);
    }
    
    for (auto& i : variables) 
    {
        if (i.second == true)
        {
            if (i.first == destination) 
            {
                useVar(continu, destination);
            }
        }
        else
        {
            if (i.first == className.back() + LocalizedVariableNames.back() + "." + destination) 
            {
                useVar(continu, className.back() + LocalizedVariableNames.back() + "." + destination);
            }
        }
    }
    for (int i = 0; i < functions.size();i++)
    {
        if (functions[i] == destination)
        {
            callFunction(destination, continu);
        }
    }
    file = ::parameters;
    varbuffer1 += ::varbuffer;
    codbuffer1 += ::codbuffer;
    texbuffer1 += ::texbuffer;
    includes1 += ::includes2;
    includes2 = "";
}

#endif