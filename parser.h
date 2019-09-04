#ifndef _PARSER_H_
#define _PARSER_H_
#include <string>
#include <vector>
#include <map>
#include <ctype.h>
#include <algorithm>
#include "Token.h"
using namespace std;
vector <Token> Tokens;
string parameters;
string varbuffer;
string bssbuffer;
string codbuffer;
string texbuffer;
string includes2;
int usedregister = 0;
int freeMemReg = 0;
string regbuffer;
int inLayer = 0;
int layerId = 0;
int returnLayer = 0;
int savedIfToElse = 0;
int savedElseToEnd = 0;
vector<string> FunctionNames;  //
vector<string> ifToElse;
vector<string> elseToEnd;
vector<string> jumpToEnd;
bool skippedRet = false;

bool hasFunctionStackFrame = false;
int framesAmount = 0;
bool isElse = false;
int Syntax = 0;
bool ifReturnValue = false;
bool isIf = false;
bool isType = false;
int functionsAmount = 0;

string returningDestName;
string paraAmount;

extern int getError(char, string&, string, int, string&);
extern int getWord(char, string&, string, int);
extern int getReversedIndex(char, string, int);
extern int getReversedWord(char, string&, string, int);
extern string readFile(string name);

string sx()
{
    string spaces = "";
    for (int i = 0; i < Syntax; i++)
    {
        spaces += " ";
    }
    return spaces;
}

int getIndex(string name)
{
    int secondPriority = 0;
    for (int i = 0; i < Tokens.size(); i++)
    {
        if (Tokens.at(i).Name == name)
        {
            if (Tokens.at(i).ifGlobal == true)
            {
                secondPriority = i;
            }
            else if (Tokens.at(i).FunctionLabelName != " " && FunctionNames.back() != " " && Tokens.at(i).owner == FunctionNames.back())
            {
                return i;
            }
        }
    }
    return secondPriority;
    cout << name + "doesnt exist!\n";
}

void disconnectFromRegister(string reg)
{
    for (auto i = Tokens.rbegin(); i != Tokens.rend(); )
    {
        if (i->Reg == reg)
        {
            i->eraseReg();
        }
        else
        {
            i++;
        }
    }
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

string getFreeMemReg()
{
    if (freeMemReg == 0)
    {
        freeMemReg++;
        return "esi ";
    }
    else
    {
        freeMemReg--;
        return "edi ";
    }
}

string autoName(string name, bool isString = false)
{   
    if (Tokens.size() == 0)
    {
        cout << "no Variables exist\n";
        return "";
    }
    else
    {
        return Tokens.at(getIndex(name)).getFullName();
    }
    
}

void makeVar(int &index)
{
    string name;
    string setting;
    string value;
    index = getWord(' ', name, parameters, index);  // name
    index = getWord(' ', setting, parameters, index);  // = or :
    index = getWord(' ', value, parameters, index);  // value or size
    Token Variable;
    Token Size;
    Variable.makeName(name);
    // check if it is a local var.
    if (FunctionNames.back() == " ")
    {
        //if it is global var.
        Variable.makePublic();
    }
    else
    {
        //if it is public.
        Variable.makePrivate(FunctionNames.back());
        Variable.owner = FunctionNames.back();
    }

    if (setting == ":")
    {
        Variable.makeArray(value);
        bssbuffer += Variable.getFullName() + " resd " + value + "\n";
    }
    else
    {
        Variable.makeVar();
        varbuffer += Variable.getFullName() + " dd " + value + "\n";
    }
    
    Tokens.push_back(Variable);
}

int lookFor(char look, string source, vector<string> &functions)
{
    int result = 0;
    int offset = 0;
    while(true)
    {
        string skip;
        offset = getWord('(', skip, source, offset);
        if (skip.size() < 1)
        {
            break;
        }
        int real = getIndex(skip);
        if (Tokens.at(real).ifFunction)
        {
            result++;
            functions.push_back(skip);
        }
    }
    return result;
}

void prepareFunction(int &index, string func)
{
    codbuffer += sx() + ";Functions Parameters\n";
    int funcIndex = getIndex(func);
    string parameter;
    vector<string> Params;
    for (int i = 0; i < Tokens.at(funcIndex).ParameterAmount; i++)
    {
        string para2;
        string error;
        int offset = getError(',', para2, parameters, index, error);
        if (para2.size() < 1 || para2.find(')') != -1)
        {
            para2 = "";
            offset = getError(')', para2, parameters, index, error);
            functionsAmount = lookFor('(', para2, Params);
            if (para2 == "")
            {
                //if no parameters
                index = offset;
                break;
            }
            else if (error == ")")
            {
                index = offset;
            }
        }
        Params.push_back(para2);
    }
    for (int i = 0; 0 < Params.size(); i++)
    {
        parameter = Params.back();
        Params.pop_back();
        int paraIndex = getIndex(parameter);
        if (parameter.at(0) == '%')
        {
            parameter.erase(parameter.begin());
            int parIndex = getIndex(parameter);
            codbuffer += sx() + "push " + Tokens.at(parIndex).getFullName() + "\n";
        }
        else if (Tokens.at(paraIndex).ifVar)
        {
            codbuffer += sx() + "push dword [" + Tokens.at(paraIndex).getFullName() + "]\n";
        }
        else if (Tokens.at(paraIndex).ifString)
        {
            codbuffer += sx() + "push " + Tokens.at(paraIndex).getFullName() + "\n";
        }
        else if (true)
        {
            
        }
        else if (Tokens.at(paraIndex).ifArray)
        {
            string skip;
            string bPart;
            index = getWord(' ', skip, parameters, index);
            index = getWord(' ', bPart, parameters, index);
            if (isdigit(bPart.at(0)) || bPart.at(0) == '-')
            {
                //lea esi, a[123 * 4]
                //push dword [esi]
                string reg1 = getFreeMemReg();
                codbuffer += sx() + "lea " + reg1 + ", " + Tokens.at(paraIndex).getFullName() + "[" + bPart + " * 4]\n";
                codbuffer += sx() + "push dword [" + reg1 + "]\n";
            }
            else
            {
                //mov edi, dword [index]
                //lea esi, a[edi * 4]
                //push dword [esi]
                string reg1 = getFreeMemReg();
                string reg2 = getFreeMemReg();
                int bIndex = getIndex(bPart);
                codbuffer += sx() + "mov " + reg1 + ", dword [" + Tokens.at(bIndex).getFullName() + "]\n";
                codbuffer += sx() + "lea " + reg2 + ", " + Tokens.at(paraIndex).getFullName() + "[" + reg1 + "* 4]\n";
                codbuffer += sx() + "push dword [" + reg2 + "]\n";
            }
        }
        
    }
    if (Tokens.at(funcIndex).ifFunction)
    {
        codbuffer += sx() + "\n" + sx() + ";Call the function\n";
        codbuffer += sx() + "call function_" + Tokens.at(funcIndex).getFullName() + "\n";
    }
    else if (Tokens.at(funcIndex).ifMacro)
    { 
        codbuffer += Tokens.at(funcIndex).getFullName() + "\n";
    }
    else
    {
        cout << sx() + "uknown Function type :c\n";
    }
    
}

string arrayInitialization(int &index, int destIndex)
{
    // get the ":" and the "index".
    string skip;
    string arrayIndex;
    index = getWord(' ', skip, parameters, index);
    index = getWord(' ', arrayIndex, parameters, index);
    if (isdigit(arrayIndex.at(0)) || arrayIndex.at(0) == '-')
    {
        //lea esi, a[123 * 4]
        //push dword [esi]
        string reg1 = getFreeMemReg();
        codbuffer += sx() + "lea " + reg1 + ", " + Tokens.at(destIndex).getFullName() + "[" + arrayIndex + " * 4]\n";
        return reg1;
    }
    else
    {
        //mov edi, dword [banana]
        //lea esi, a[edi * 4]
        //push dword [esi]
        string reg1 = getFreeMemReg();
        int indexIndex = getIndex(arrayIndex);
        codbuffer += sx() + "mov " + reg1 + ", dword [" + Tokens.at(indexIndex).getFullName() + "]\n";
        codbuffer += sx() + "lea " + reg1 + ", " + Tokens.at(destIndex).getFullName() + "[" + reg1 + "* 4]\n";
        return reg1;
    }
}

void makeInitialDestiantion(int &index, string dest)
{
    codbuffer += sx() + ";The inital destination\n";
    int destIndex = getIndex(dest);
    if (dest.size() < 1)
    {
        return;
    }
    if (dest.at(0) == '%')
    {
        dest.erase(dest.begin());
        int destIndex2 = getIndex(dest);
        codbuffer += sx() + "push dword [" + Tokens.at(destIndex2).getFullName() + "]\n";
    }
    else if (Tokens.at(destIndex).ifVar)
    {
        codbuffer += sx() + "push " + Tokens.at(destIndex).getFullName() + "\n";
    }
    else if (Tokens.at(destIndex).ifArray)
    {
        codbuffer += sx() + "push " + arrayInitialization(index, destIndex) + "\n";
    }
    else if (Tokens.at(destIndex).ifFunction)
    {
        // get the parameter's for the function.
        prepareFunction(index, dest);
    }
    else
    {
        cout << "bad destination: " + dest + "\n";
    }
    codbuffer += sx() + "\n";
}

void getInitalDestination(int &index, string destReg)
{
    string memReg = getFreeMemReg();
    codbuffer += "\n" + sx() + ";Get the destination to: " + memReg + "\n";
    codbuffer += sx() + "pop " + memReg + "\n";
    codbuffer += sx() + "mov [" + memReg + "], " + destReg + "\n\n";
}

void callFunction(string function, int &index)
{
    prepareFunction(index, function);
}

void doReturn()
{
    bool waselse = false;
    bool wasif = false;
    bool secondphase = false;
    if (functionsAmount != 0)
    {
        functionsAmount--;
        return;
    }
    if (ifReturnValue)
    {
        ifReturnValue = false;
        secondphase = true;
        return;
    }
    else
    {
        codbuffer += "\n";
        codbuffer += sx() + ";making a stack frame end\n";
        codbuffer += sx() + "mov esp, ebp\n" + sx() + "pop ebp\n";
    }
    Syntax--;
    if (isElse)
    {
        codbuffer += elseToEnd.back();
        elseToEnd.pop_back();
        inLayer--;
        isElse = false;
        waselse = true;
    }
    else if (isIf)
    {
        isIf = false;
        wasif = true;
    }
    if (framesAmount == 1 && secondphase == false && waselse == false && wasif == false)
    {
        codbuffer += sx() +  "ret\n\n";
        FunctionNames.pop_back();
        Syntax = 0;
    }
    else
    {
        codbuffer += "\n";
    }
}

void doMath(int &index, string a, string math)
{
    codbuffer += "\n" + sx() + ";Math do: " + math + "\n";
    string b;
    index = getWord(' ', b, parameters, index);
    //a +/*- b
    int aI = getIndex(a);
    int bI = getIndex(b);
    string opCode;
    if (math == "+")
    {
        opCode = "add ";
    }
    else if (math == "-")
    {
        opCode = "sub ";
    }
    else if (math == "/")
    {
        opCode = "idiv ";
    }
    else
    {
        opCode = "imul ";
    }
    if (Tokens.at(bI).ifFunction)
    {
        prepareFunction(index, b);
    }
    codbuffer += sx() + opCode + Tokens.at(aI).getReg(codbuffer) + ", " + Tokens.at(bI).getReg(codbuffer) + "\n\n";
    //check if there is more math to do.
    math = "";
    int offset = getWord(' ', math, parameters, index);
    if (math == "\n" || math == " " || math == "ret")
    {
        return;
    }
    else if (math == "+" || math == "-" || math == "/" || math == "*")
    {
        //this means that math exist on this same line of code :D.
        //so lets make it.
        index = offset;
        doMath(index, a, math);
    }
}

void useVar(int &index, string destination)
{
    codbuffer += "\n"; //giving some readability
    //save the destination to stack.
    makeInitialDestiantion(index, destination);
    //skip the = mark.
    string skip;
    index = getWord(' ', skip, parameters, index);
    //check if increas reguest.
    if (skip == "+=" || skip == "-=")
    {
        string upcrease;
        index = getWord(' ', upcrease, parameters, index);
        string condition;
        if (skip == "+=")
        {
            condition = "add ";
        }
        else
        {
            condition = "sub ";
        }
        int destIndex = getIndex(destination);
        if (isdigit(upcrease.at(0)) || upcrease.at(0) == '-')
        {
            codbuffer += sx() + condition + Tokens.at(destIndex).getReg(codbuffer) + ", "+ upcrease +"\n";
        }
        else
        {
            int upcreaseI = getIndex(upcrease);
            codbuffer += sx() + condition + Tokens.at(destIndex).getReg(codbuffer) + ", "+ Tokens.at(upcreaseI).getReg(codbuffer) +"\n";
        }
        
        getInitalDestination(index, Tokens.at(destIndex).getReg(codbuffer));
        return;
    }
    //start the math check.
    string bPart;
    index = getWord(' ', bPart, parameters, index);
    string destTest;

    if (bPart.find('(') != -1)
    {
        int offset = getWord('(', destTest, bPart, 0);
        if (int i = getIndex(destTest) != 0)
        {
            int recruit = getReversedIndex('(', bPart, bPart.size());
            bPart = destTest;
            index -= recruit;
        }
    }
    int bIndex = getIndex(bPart);
    string math;
    int offset = getWord(' ', math, parameters, index);
    if (Tokens.at(bIndex).ifFunction != true)
    {
        if (math == "+" || math == "-" || math == "/" || math == "*")
        {
            //this means that math exist on this same line of code :D.
            //so lets make it.
            index = offset;
            doMath(index, bPart, math);
        }
    }

    // check if B part is a function
    if (Tokens.at(bIndex).ifFunction)
    {
        prepareFunction(index, bPart);
        string secondareMath;
        offset = getWord(' ', secondareMath, parameters, index);
        if (secondareMath == "+" || secondareMath == "-" || secondareMath == "/" || secondareMath == "*")
        {
            //this means that math exist on this same line of code :D.
            //so lets make it.
            index = offset;
            doMath(index, bPart, secondareMath);
        }
    }

    //if B part is a array
    if (Tokens.at(bIndex).ifArray)
    {
        //mov esi, dword array[index]
        getFreeReg();
        string reg1 = regbuffer;
        codbuffer += sx() + "mov " + reg1 + ", dword [" + arrayInitialization(index, bIndex) + "]\n";
        getInitalDestination(index, reg1);
        return;
    }

    //load the inital destination from stack and give it the inital sum.
    getInitalDestination(index, Tokens.at(bIndex).getReg(codbuffer));
}

void makeFunc(int &index)
{
    string para1;
    index = getWord('(', para1, parameters, index);
    codbuffer += "function_" + para1 + ":\n";
    Syntax++;
    Token func;
    func.makeFunc(para1);
    func.makePublic();
    
    returnLayer++;
    vector<string> paraOrder;
    string reg1 = regbuffer;
    int i = 0;
    while (true)
    {
        string para2;
        string error;
        int offset = getError(',', para2, parameters, index, error);
        if (para2.size() < 1 || para2.find(')') != -1)
        {
            para2 = "";
            offset = getError(')', para2, parameters, index, error);
            if (para2 == "")
            {
                //if no parameters
                func.ParameterAmount = 0;
                index = offset;
                break;
            }
        }
        else
        {
            offset++; // skip the " " after the ,
        }
        Token Parameter;
        Parameter.makeName(para2);
        Parameter.makePrivate(para1);
        if (para2.length() > 0) 
        {
            if (para2.find('%')!= string::npos)
            {
                Parameter.makePtr();
            }
            else
            {
                Parameter.makeVar();
            }
        }
        if (error == "\n")
        {
            if (para2 != "(")
            {
                func.makeLink(Parameter);
                index = offset;
            }
            break;
        }
        else if (error == ")")
        {
            index = offset;
            func.makeLink(Parameter);
            break;
        }
        else
        {
            func.makeLink(Parameter);
            index = offset;
        }
        i++;
    }
    codbuffer += sx() + ";making a function stack frame\n";
    codbuffer += sx() + "push ebp\n" + sx() + "mov ebp, esp\n\n";
    if (func.ParameterAmount > 0)
    {
        codbuffer += sx() + "sub esp, " + to_string(func.ParameterAmount * 4) + "\n";
    }
    hasFunctionStackFrame = true;
    FunctionNames.push_back(para1);
    Tokens.push_back(func);

    for (int i = 0; i < func.ParameterAmount; i++)
    {
        getFreeReg();
        string reg2 = regbuffer;
        string para3 = func.Links.at(i).Name;
        if (func.Links.at(i).ifPointer)
        {
            para3.erase(para3.begin());
        }

        Token child;
        child.makeName(para3);
        child.ifChild = true;
        child.owner = para1;
        child.Reg = reg2;
        codbuffer += sx() + "\n";
        if (func.Links.at(i).ifPointer)
        {
            string memreg = getFreeMemReg();
            codbuffer += sx() + ";" + para3 + " is now an Pointer.\n";
            codbuffer += sx() + "mov " + memreg + ", [ebp + " + to_string(4 * i + 8) + "]\n";
            codbuffer += sx() + "lea " + memreg + ", [" + memreg + "]\n";
            child.makePtr();
        }
        else
        {
            codbuffer += sx() + ";" + para3 + " is now an Variable.\n";
            codbuffer += sx() + "mov " + reg2 + ", [ebp+" + to_string(4 * i + 8) + "]\n";
            child.makeVar();
        }

        varbuffer += para1 + "." + para3 + " dd 0\n";

        child.makePrivate(para1);
        codbuffer += sx() + "mov [" + child.getFullName() + "], " + reg2 + "\n";
        Tokens.push_back(child);
    }
    paraAmount = to_string(func.ParameterAmount * 4);
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
    if (condition == "!>" || condition == ">!")
    {
        return "jg ";
    }
    if (condition == "!<" || condition == "<!")
    {
        return "jl ";
    }
    if (condition == "=>" || condition == ">=")
    {
        return "jl ";
    }
    if (condition == "=<" || condition == "<=")
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
    isIf = true;
    string a;  //a
    string condition;  // ==
    string b;  //b
    string acomp;
    string bcomp;
    i = getWord(' ', a, parameters, i);
    int aI = getIndex(a);
    if (Tokens.at(aI).ifArray)
    {
        getFreeReg();
        string reg1 = regbuffer;
        codbuffer += sx() + "mov " + reg1 + ", dword [" + arrayInitialization(i, aI) + "]\n";
        acomp = reg1;
    }
    else
    {
        acomp = Tokens.at(aI).getReg(codbuffer);
    }
    
    i = getWord(' ', condition, parameters, i);
    i = getWord(' ', b, parameters, i);
    int bI = getIndex(b);
    if (Tokens.at(bI).ifArray)
    {
        getFreeReg();
        string reg1 = regbuffer;
        codbuffer += sx() + "mov " + reg1 + ", dword [" + arrayInitialization(i, bI) + "]\n";
        bcomp = reg1;
    }
    else
    {
        bcomp = Tokens.at(bI).getReg(codbuffer);
    }
    condition = getJump(condition);
    
    codbuffer += sx() +   "cmp " + acomp + ", " + bcomp + "\n";
    
    inLayer++;
    layerId++;
    codbuffer += sx() + condition + "else" + to_string(inLayer) + to_string(layerId) + "\n";
    ifToElse.push_back(sx() + "else" + to_string(inLayer) + to_string(layerId) + ":\n");
    elseToEnd.push_back(sx() + "end" + to_string(inLayer) + to_string(layerId) + ":\n");
    jumpToEnd.push_back(sx() + "jmp end" + to_string(inLayer) + to_string(layerId) + "\n");
    savedIfToElse++;
    savedElseToEnd++;
    Syntax++;
}

void doElse()
{
    savedIfToElse--;
    savedElseToEnd--;
    codbuffer += jumpToEnd.back();
    codbuffer += ifToElse.back();
    jumpToEnd.pop_back();
    ifToElse.pop_back();
    isElse = true;
    Syntax++;
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
    Token type;
    type.makeType(typeName);
    type.makePublic();
    varbuffer += "\n" + typeName + ":\n";
    isType = true;
}

void makeNew(int &index)
{
  //
}

void doInterruption(int &index)
{
    string eax;
    string ebx;
    string ecx;
    string edx;
    string callingnumber;
    string carry;
    index = getWord(' ', eax, parameters, index);
    index = getWord(' ', ebx, parameters, index);
    index = getWord(' ', ecx, parameters, index);
    index = getWord(' ', edx, parameters, index);
    index = getWord(' ', callingnumber, parameters, index);
    index = getWord(' ', carry, parameters, index);
    int aI = getIndex(eax);
    int bI = getIndex(ebx);
    int cI = getIndex(ecx);
    int dI = getIndex(edx);
    codbuffer += "\n" + sx() + "push eax\n";
    if (isdigit(eax.at(0)) || eax.at(0) == '-')
    {
        codbuffer += sx() + "mov eax, " + eax + "\n";
    }
    else
    {
        codbuffer += sx() + "mov eax, dword [" + Tokens.at(aI).getFullName() + "]\n";
    }
    if (isdigit(ebx.at(0)) || ebx.at(0) == '-')
    {
        codbuffer += sx() + "mov ebx, " + ebx + "\n";
    }
    else
    {
        codbuffer += sx() + "mov ebx, dword [" + Tokens.at(bI).getFullName() + "]\n";
    }
    if (isdigit(ecx.at(0)) || ecx.at(0) == '-')
    {
        codbuffer += sx() + "mov ecx, " + ecx + "\n";
    }
    else
    {
        codbuffer += sx() + "mov ecx, dword [" + Tokens.at(cI).getFullName() + "]\n";
    }
    if (isdigit(edx.at(0)) || edx.at(0) == '-')
    {
        codbuffer += sx() + "mov edx, " + edx + "\n";
    }
    else
    {
        codbuffer += sx() + "mov edx, dword [" + Tokens.at(dI).getFullName() + "]\n";
    }
    
    codbuffer += sx() + "int " + callingnumber + "\n";
    codbuffer += sx() + "mov [" + carry + "], eax\n";
    codbuffer += sx() + "pop eax\n\n";
}

void makeNewString(int &index)
{
    string name;
    string is;
    string str;
    index = getWord(' ', name, parameters, index);
    index = getWord(' ', is, parameters, index);
    index = getWord('"', str, parameters, index);
    index = getWord('"', str, parameters, index);
    Token String;
    String.makeString();
    String.makeName(name);
    if (FunctionNames.back() == " ")
    {
        String.makePublic();
    }
    else
    {
        String.makePrivate(FunctionNames.back());
    }
    varbuffer += String.getFullName() + " db \"" + str + "\", 0\n";
    Tokens.push_back(String);
}

void useStr(int &index, string destination)
{
    string command;
    string b;

    index = getWord(' ', command, parameters, index);
    index = getWord(' ', b, parameters, index);
    int destI = getIndex(destination);
    int bI = getIndex(b);

    if (Tokens.at(bI).ifString)
    {
        codbuffer += "\n" + sx() + ";Load the destination.\n";
        codbuffer += sx() + "lea edi, [" + Tokens.at(destI).getFullName() + "]\n";
        codbuffer += sx() + ";Load the source.\n";
        codbuffer += sx() + "lea esi, [" + Tokens.at(bI).getFullName() + "]\n";
        codbuffer += sx() + "push esi\n";
    }
    else
    {
        codbuffer += "\n" + sx() + ";Load the destination.\n";
        codbuffer += sx() + "lea edi, [" + Tokens.at(destI).getFullName() + "]\n";
        codbuffer += sx() + ";Load the source.\n";
        prepareFunction(index, b);
    }

    codbuffer += "\n" + sx() + ";Load the destination.\n";
    codbuffer += sx() + "call len\n";
    codbuffer += sx() + "pop ecx\n";
    codbuffer += sx() + "repnz movsb \n\n";
}

void returnValue(int &index)
{
    string dest;
    index = getWord(' ', dest, parameters, index);
    int destIndex = getIndex(dest);
    codbuffer += sx() + ";returning from stack frame\n";
    codbuffer += sx() + "mov esp, ebp\n" + sx() + "pop ebp\n\n";
    codbuffer += sx() + ";returning a value from function\n";
    codbuffer += sx() + "pop eax\n";
    codbuffer += sx() + "add esp, " + paraAmount + "\n";
    codbuffer += sx() + "push dword [" + Tokens.at(destIndex).getFullName() + "]\n";
    Syntax--;
    codbuffer += sx() + "jmp eax\n\n";
    ifReturnValue = true;
}

void parser(string destination, string &file, int &continu, string &varbuffer1, string &codbuffer1, string &texbuffer1, string &includes1, string &bssbuffer1)
{
    codbuffer = "";
    texbuffer = "";
    varbuffer = "";
    bssbuffer = "";
    parameters = file;
    string destTest;

    if (destination.find('(') != -1)
    {
        int offset = getWord('(', destTest, destination, 0);
        if (int i = getIndex(destTest) != 0)
        {
            int recruit = getReversedIndex('(', destination, destination.size());
            destination = destTest;
            continu -= recruit;
        }
    }

    int dest = getIndex(destination);
    if (destination.size() > 0 && destination.at(0) == '#')
    {
        string trash;
        continu = getWord('\n', trash, parameters, continu);
    }
    else if (destination == "return")
    {
        returnValue(continu);
    }
    else if (destination == "var")
    {
        makeVar(continu);
    }
    else if (destination == "type")
    {
        makeNewType(continu);
    }
    else if (destination == "func")
    {
        makeFunc(continu);
    }
    else if (destination == "*")
    {
        disconnectFromRegister("eax ");
    }
    else if (destination == "/")
    {
        disconnectFromRegister("eax ");
    }
    else if (destination == ")")
    {
        doReturn();
        framesAmount--;
    }
    else if (destination == "(")
    {
        if (hasFunctionStackFrame)
        {
            hasFunctionStackFrame = false;
        }
        else
        {
            codbuffer += "\n" + sx() + ";making a stack frame start\n";
            codbuffer += sx() + "push ebp\n" + sx() + "mov ebp, esp\n\n";
        }
        framesAmount++;
    }
    else if (destination == "if")
    {
        doComparing(continu);
    }
    else if (destination == "else")
    {
        doElse();
    }
    else if (destination == "use")
    {
        doInclude(continu);
    }
    else if (destination == "new")
    {
        makeNew(continu);
    }
    else if (destination == "sys")
    {
        doInterruption(continu);
    }
    else if (destination == "str")
    {
        makeNewString(continu);
    }
    else if (Tokens.at(dest).ifString)
    {
        useStr(continu, destination);
    }
    else if (Tokens.at(dest).ifVar || Tokens.at(dest).ifArray) 
    {
        useVar(continu, destination);
    }
    else if (Tokens.at(dest).ifFunction)
    {
        callFunction(destination, continu);
    }

    file = parameters;
    varbuffer1 += varbuffer;
    bssbuffer1 += bssbuffer;
    codbuffer1 += codbuffer;
    texbuffer1 += texbuffer;
    includes1 += includes2;
    includes2 = "";
}

#endif