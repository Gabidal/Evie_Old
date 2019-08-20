#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>
#include <vector>
using namespace std;

class Token
{
  public:
    void makeVar()
    {
      ifVar = true;
    }

    void makeName(string name)
    {
        Name = name;
    }

    void makePrivate(string funcName, string typeName)
    {
        FunctionLabelName = funcName;
        TypeLabelName = typeName;
    }

    void makePublic()
    {
        ifGlobal = true;
    }

    void makeFunc(string func)
    {
        ifFunction = true;
        FunctionLabelName = func;
    }

    void makeType(string typeName)
    {
        TypeLabelName = typeName;
        ifType = true;
    }

    void makeMacro()
    {
        ifMacro = true;
    }

    void makeArray(string size)
    {
        Size = size;
        ifArray = true;
    }

    void makeString()
    {
        ifString = true;
    }

    void makeEqu()
    {
        ifEqu = true;
    }

    void linkToReg(string reg)
    {
        ifHasReg = true;
        Reg = reg;
    }

    void eraseReg()
    {
        ifHasReg = false;
        Reg = "";
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
        else if (TypeLabelName != "")
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
    }

    bool ifPointer = true;
    bool ifGlobal = false;
    bool ifType = false;
    bool ifFunction = false;
    bool ifMacro = false;
    bool ifArray = false;
    bool ifVar = false;
    bool ifString = false;
    bool ifEqu = false;
    bool ifHasReg = false;
    string FunctionLabelName = "";
    string TypeLabelName = "";
    string Name;
    string Size;
    string Reg;
    int PlaceInType = 0;
    vector <Token> Links;
};


#endif