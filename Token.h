#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>
#include <vector>
using namespace std;

extern int usedregister;
extern string sx();
extern string getFreeMemReg();
extern void getFreeReg();
extern string regbuffer;
extern string codbuffer;
class Token;
extern vector<Token> Tokens;
extern vector<string> FunctionNames;
extern int getIndex(string name);

class Token
{
  public:
    void makeVar()
    {
      ifVar = true;
      ifReal = true;
      Size = 4;
    }

    void makePtr()
    {
        ifPointer = true;
        ifReal = true;
        Size = 4;
    }

    void makeName(string name)
    {
        Name = name;
    }

    void makePrivate(string funcName)
    {
        FunctionLabelName = funcName;
        ifReal = true;
    }

    void makePublic()
    {
        ifGlobal = true;
        ifReal = true;
    }

    void makeFunc(string func)
    {
        ifFunction = true;
        Name = func;
        ifReal = true;
    }

    void makeType(string typeName)
    {
        ifType = true;
        ifReal = true;
    }

    void makeMacro()
    {
        ifMacro = true;
        ifReal = true;
    }

    void makeArray(int size)
    {
        Size = size;
        ifArray = true;
        ifReal = true;
    }

    void makeString(int size)
    {
        ifString = true;
        ifReal = true;
        Size = size;
    }

    void makeEqu()
    {
        ifEqu = true;
        ifReal = true;
        Size = 2;
    }

    void linkToReg(string reg)
    {
        ifHasReg = true;
        Reg = reg;
        ifReal = true;
    }

    void eraseReg()
    {
        ifHasReg = false;
        Reg = "";
        ifReal = true;
    }

    string getFullName()
    {
        if (ifType == false && ifInStack)
        {
            if (Tokens.at(getIndex(FunctionNames.back())).This == "")
            {
                //if the class address is deleted in midle of function.
                string reg = getFreeMemReg();
                codbuffer += sx() + "mov " + reg + ", [ebp + 8]\n";
                Tokens.at(getIndex(FunctionNames.back())).This = reg;
            }
            string result;
            string funcThisReg = Tokens.at(getIndex(FunctionNames.back())).This;
            This = funcThisReg;
            result = This + "+ " + to_string(PlaceInStack);
            return result;
        }
        if (ifGlobal)
        {
            return Name;
        }
        else
        {
            return FunctionLabelName + "." + Name;
        }
    }

    void makeLink(Token newLink)
    {
        Links.push_back(newLink);
        ifReal = true;
        ParameterAmount++;
    }

    void addChild(Token &t)
    {
        t.PlaceInStack = PlaceInStack * 4;
        PlaceInStack++;
        t.ifInStack = true;
        t.typeName = Name;
        t.This = this->This;
        this->Size += t.Size;
        Links.push_back(t);
    }

    string getReg()
    {
        if (Reg == "")
        {
            getFreeReg();
            Reg = regbuffer;
            if (ifFunction)
            {
                codbuffer += sx() + "pop " + Reg + "\n";
            }
            else if (ifVar)
            {
                codbuffer += sx() + "mov " + Reg + ", dword [" + getFullName() + "]\n";
            }
            else if (ifArray)
            {
                codbuffer += sx() + "lea " + Reg + ", [" + getFullName() + "]\n";
            }
            
            return Reg;
        }
        else
        {
            if (ifReturner)
            {
                codbuffer += sx() + "pop " + Reg + "\n";
            }
            return Reg;
        }
    }

    void makeReturnable()
    {
        ifReturner = true;
    }

    bool ifReal = false;
    bool ifNumber = false;
    bool ifPointer = false;
    bool ifGlobal = false;
    bool ifType = false;
    bool ifFunction = false;
    bool ifMacro = false;
    bool ifArray = false;
    bool ifVar = false;
    bool ifString = false;
    bool ifEqu = false;
    bool ifHasReg = false;
    bool ifChild = false;
    bool ifReturner = false;
    bool ifInStack = false;
    string typeName = "";
    string owner = "";
    string FunctionLabelName = " ";
    string Name;
    int Size = 0;
    string Reg;
    string Value;
    string This;
    int PlaceInStack = 0;
    int ParameterAmount = 0;
    vector <Token> Links;
};


#endif