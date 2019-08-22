#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>
#include <vector>
using namespace std;

extern int usedregister;

class Token
{
  public:
    void makeVar()
    {
      ifVar = true;
      ifReal = true;
    }

    void makePtr()
    {
        ifPointer = true;
        ifReal = true;
    }

    void makeName(string name)
    {
        Name = name;
    }

    void makePrivate(string funcName, string typeName)
    {
        FunctionLabelName = funcName;
        TypeLabelName = typeName;
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
        TypeLabelName = typeName;
        ifType = true;
        ifReal = true;
    }

    void makeMacro()
    {
        ifMacro = true;
        ifReal = true;
    }

    void makeArray(string size)
    {
        Size = size;
        ifArray = true;
        ifReal = true;
    }

    void makeString()
    {
        ifString = true;
        ifReal = true;
    }

    void makeEqu()
    {
        ifEqu = true;
        ifReal = true;
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

    void makeNextPlace()
    {
        PlaceInType++;
    }

    string getFullName()
    {
        if (ifGlobal)
        {
            return Name;
        }
        else if (TypeLabelName != " ")
        {
            return TypeLabelName + "." + FunctionLabelName + "." + Name;
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

    string getNextReg()
    {
        if (usedregister == 3)
        {
            usedregister = 0;
            return "edx ";
        }
        else if (usedregister == 2)
        {
            usedregister = 3;
            return "ecx ";
        }
        else if (usedregister == 1)
        {
            usedregister = 2;
            return "ebx ";
        }
        else if (usedregister == 0)
        {
            usedregister = 1;
            return "eax ";
        }
        return "eax ";
    }

    string getReg(string &buffer)
    {
        if (Reg == "")
        {
            Reg = getNextReg();
            buffer += "mov " + Reg + ", dword [" + getFullName() + "]\n";
            return Reg;
        }
        else
        {
            return Reg;
        }
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
    string owner = "";
    string FunctionLabelName = "";
    string TypeLabelName = "";
    string Name;
    string Size;
    string Reg;
    int PlaceInType = 0;
    int ParameterAmount = 0;
    vector <Token> Links;
};


#endif