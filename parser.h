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
vector<string> LocalizedVariableNames;  //
vector<string> ifToElse;
vector<string> elseToEnd;
vector<string> jumpToEnd;
map<string, bool> variables;            //true == global; false == local
map <string, string> varPointers;      //
map <string, string> ArrayVariables;   //
vector<string> functions;               //
vector<string> Macros;                  
vector<string> localVars;
map<string, int> Types;
map <string, bool> Strings;
vector<string> equs;
int localVarLocation;
bool skippedRet = false;
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

int getIndex(string name)
{
    for (int i = 0; i < Tokens.size(); i++)
    {
        if (Tokens.at(i).Name == name)
        {
            return i;
        }
    }
    cout << name + "doesnt exist!\n";
    return 0;
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
    string para1;
    string para2;
    string para3;
    index = getWord(' ', para1, parameters, index);  //name
    index = getWord(' ', para2, parameters, index);  // = or :
    index = getWord(' ', para3, parameters, index);  // value or size
    Token variable;
    Token size;
    if (para2 == ":")
    {
        if (LocalizedVariableNames.back() == " ")
        {
            variable.makePublic();
            size.makePublic();
        }
        else
        {
            variable.makePrivate(className.back(), LocalizedVariableNames.back());
            size.makePrivate(className.back(), LocalizedVariableNames.back());
        }

        bssbuffer += className.back() + para1 + " resd " + para3 + "\n";

        variable.makeName(para1);
        variable.makeArray(para3);
            
        size.makeEqu();
        size.makeName(para1 + ".size");
        variable.makeLink(size);

        varbuffer += className.back() + para1 + ".size equ $ - " + className.back() + para1 + "\n";
    }
    else
    {
        if (LocalizedVariableNames.back() == " ")
        {
            varbuffer += className.back() + para1 + " dd " + para3 + "\n";
            variable.makePublic();
        }
        else
        {
            varbuffer += className.back() + LocalizedVariableNames.back() + para1 + " dd " + para3 + "\n";
            variable.makePrivate(className.back(), LocalizedVariableNames.back());
        }

        variable.makeVar();
        variable.makeName(para1);
    }
    Tokens.push_back(variable);
}

void prepareFunction(int &index, string func)
{
    int funcIndex = getIndex(func);
    string parameter;
    for (int i = 0; i < Tokens.at(funcIndex).ParameterAmount; i++)
    {
        index = getWord(' ', parameter, parameters, index);
        int parIndex = getIndex(parameter);
        codbuffer += "push dword [" + Tokens.at(parIndex).getFullName() + "]\n";
    }
    if (Tokens.at(funcIndex).ifFunction)
    {
        codbuffer += "call " + Tokens.at(funcIndex).getFullName() + "\n";
    }
    else if (Tokens.at(funcIndex).ifMacro)
    { 
        codbuffer += Tokens.at(funcIndex).getFullName() + "\n";
    }
    else
    {
        cout << "uknown Function type :c\n";
    }
    
}

void makeInitialDestiantion(int &index, string dest)
{
    int destIndex = getIndex(dest);
    if (Tokens.at(destIndex).ifVar)
    {
        codbuffer += "push " + Tokens.at(destIndex).getFullName() + "\n";
    }
    else if (Tokens.at(destIndex).ifArray)
    {
        // get the ":" and the "index".
        string skip;
        string arrayIndex;
        index = getWord(' ', skip, parameters, index);
        index = getWord(' ', arrayIndex, parameters, index);
        //mov esi, [arrayIndex]
        //lea esi, dest[esi * 4]
        string memReg = getFreeMemReg();
        codbuffer += "mov " + memReg + ", dword [" + arrayIndex + "]\n";
        codbuffer += "lea " + memReg + ", " + dest + "[ " + memReg + "* 4]\n";
        codbuffer += "push dword [" + memReg + "]\n";
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
}

void getInitalDestination(int &index, string destReg)
{
    string memReg = getFreeMemReg();
    codbuffer += "pop " + memReg + "\n";
    codbuffer += "mov [" + memReg + "], " + destReg + "\n";
}

void callFunction(string function, int &index)
{
    int funcIndex = getIndex(function);
    for (int i = 0; i < Tokens.at(funcIndex).ParameterAmount; i++)
    {
        string parameter;
        index = getWord(' ', parameter, parameters, index);
        makeInitialDestiantion(index, parameter);
    }
    if (Tokens.at(funcIndex).ifFunction)
    {
        codbuffer += "call " + Tokens.at(funcIndex).getFullName() + "\n";
    }
    else if (Tokens.at(funcIndex).ifMacro)
    { 
        codbuffer += Tokens.at(funcIndex).getFullName() + "\n";
    }
    else
    {
        cout << "uknown Function type :c\n";
    }
}

string getReturn()
{
    int node = getIndex("return");
    if (Tokens.at(node).ifVar)
    {
        return Tokens.at(node).Name;
    }
    else
    {
        getFreeReg();
        string returnreg = regbuffer;
        codbuffer += sx() + "mov " + returnreg + ", dword [return]\n";
        Tokens.at(node).Reg = returnreg;
        return returnreg;
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

void doMath(int &index, string a, string math)
{
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
    codbuffer += opCode + Tokens.at(aI).getReg(codbuffer) + ", " + Tokens.at(bI).getReg(codbuffer) + "\n\n";
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
    //save the destination to stack.
    makeInitialDestiantion(index, destination);
    //skip the = mark.
    string skip;
    index = getWord(' ', skip, parameters, index);
    //start the math check.
    string bPart;
    index = getWord(' ', bPart, parameters, index);
    string math;
    int offset = getWord(' ', math, parameters, index);
    if (math == "+" || math == "-" || math == "/" || math == "*")
    {
        //this means that math exist on this same line of code :D.
        //so lets make it.
        index = offset;
        doMath(index, bPart, math);
    }
    //load the inital destination from stack and give it the inital sum.
    int bIndex = getIndex(bPart);
    getInitalDestination(index, Tokens.at(bIndex).getReg(codbuffer));
}

void makeFunc(int &index)
{
    string para1;
    index = getWord(' ', para1, parameters, index);
    codbuffer += sx() + className.back() +  para1 + ":\n";

    Token func;
    func.makeFunc(para1);
    if (className.back() != " ")
    {
        func.makePrivate("", className.back());
    }
    else
    {
        func.makePublic();
    }
    
    returnLayer++;
    vector<string> paraOrder;
    string reg1 = regbuffer;
    int i = 0;
    while (true)
    {
        string para2;
        string error;
        int offset = getError(' ', para2, parameters, index, error);
        Token Parameter;
        Parameter.makeName(para2);
        Parameter.makePrivate(para1, className.back());
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
            func.makeLink(Parameter);
            index = offset;
            break;
        }
        i++;
        func.makeLink(Parameter);
    }

    codbuffer += sx() + "push ebp\n" + sx() + "mov ebp, esp\n";
    codbuffer += sx() + "sub esp, " + to_string(func.ParameterAmount) + "\n";
    LocalizedVariableNames.push_back(para1 + ".");
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
        if (func.Links.at(i).ifPointer)
        {
            string memreg = getFreeMemReg();
            codbuffer += ";" + para3 + " is now Pointer.\n";
            codbuffer += sx() + "mov " + memreg + ", [ebp + " + to_string(4 * i + 8) + "]\n";
            codbuffer += sx() + "lea " + memreg + ", [" + memreg + "]\n";
            child.makePtr();
        }
        else
        {
            codbuffer += ";" + para3 + " is now Variable.\n";
            codbuffer += sx() + "mov " + reg2 + ", [ebp+" + to_string(4 * i + 8) + "]\n";
            child.makeVar();
        }

        varbuffer += className.back() + para1 + "." + para3 + " dd 0\n";

        codbuffer += sx() + "mov [" + className.back() + para1 + "." + para3 + "], " + reg2 + "\n";
        child.makePrivate(para1, className.back());
        Tokens.push_back(child);
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
    varbuffer += "\n" + typeName + ":\n";
}

void endType()
{
    className.pop_back();
    varbuffer += "\n\n";
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
    vector<string> LocalFunctions;
    vector<string> newLocalFunctions;

    for (auto& i : variables) 
    {
        if (i.first.find(TypeName) != -1) 
        {
            LocalTypeVariables.push_back(i.first);
        }
    }
    for (auto& i : ArrayVariables) 
    {
        if (i.first.find(TypeName) != -1) 
        {
            LocalTypeVariables.push_back(i.first);
        }
    }
    for (auto& i : functions)
    {
        if (i.find(TypeName) != -1)
        {
            LocalFunctions.push_back(i);
        }
    }
    reverse(LocalFunctions.begin(), LocalFunctions.end());
    reverse(LocalTypeVariables.begin(), LocalTypeVariables.end());
    for (int i = 0; 0 < LocalFunctions.size(); i++)
    {
        int offset = 1;
        string dest = "";
        reverse(LocalFunctions.back().begin(), LocalFunctions.back().end());
        offset = getWord('.', dest, LocalFunctions.back(), offset);
        reverse(dest.begin(), dest.end());
        reverse(LocalFunctions.back().begin(), LocalFunctions.back().end());
        LocalFunctions.back().pop_back();

        texbuffer += "\n%macro " + newTypeBranch + "." + dest + " 0\n";
        texbuffer += "  lea edi, [" + newTypeBranch + "]\n";
        texbuffer += "  call " + LocalFunctions.back() + "\n";
        texbuffer += "%endmacro\n\n";
        LocalFunctions.pop_back();
        Macros.push_back(newTypeBranch + "." + dest);
        functions.push_back(newTypeBranch + "." + dest + ".");
        varbuffer += "\n" + newTypeBranch + ":\n";

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
    varbuffer += "\n\n";
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
    codbuffer += "push eax\n";
    codbuffer += "mov eax, " + autoName(eax) + "\n";
    codbuffer += "mov ebx, " + autoName(ebx) + "\n";
    codbuffer += "mov ecx, " + autoName(ecx) + "\n";
    codbuffer += "mov edx, " + autoName(edx) + "\n";
    codbuffer += "int " + callingnumber + "\n";
    codbuffer += "mov [" + carry + "], eax\n";
    codbuffer += "pop eax\n";
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
    if (LocalizedVariableNames.back() != " ")
    {
        Strings.insert(make_pair(name, true));
        name = className.back() + LocalizedVariableNames.back() + name;
    }
    else
    {
        Strings.insert(make_pair(name, false));
        name = className.back() + name;
    }
    if (is == "=")
    {
        varbuffer += name + " db \"" + str + "\", 0\n";
        varbuffer += name + ".size equ $ - " + name + "\n\n";
        equs.push_back(name + ".size");
    }
    else
    {
        bssbuffer += name + " resb " + str + "\n";
        varbuffer += name + ".size dd " + str + "\n";
    }
    

}

void useStr(int &index, string destination)
{
    string command;
    string firstStr;

    index = getWord(' ', command, parameters, index);
    index = getWord(' ', firstStr, parameters, index);

    if (command == "=")
    {
        codbuffer += "lea edi, [" + autoName(destination, true) + "]\n";
        codbuffer += "lea esi, [" + autoName(firstStr, true) + "]\n";

        codbuffer += "push ecx\n";
        codbuffer += "mov ecx, [" + autoName(firstStr, true) + ".size]\n";
        codbuffer += "repz movsb \n";
    }
    else
    {
        // if this occurs it mean it's time for some functions baby!
        
    }
}

void parser(string destination, string &file, int &continu, string &varbuffer1, string &codbuffer1, string &texbuffer1, string &includes1, string &bssbuffer1)
{
    codbuffer = "";
    texbuffer = "";
    varbuffer = "";
    bssbuffer = "";
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
    }
    if (destination == "-")
    {
    }
    if (destination == "*")
    {
        disconnectFromRegister("eax ");
    }
    if (destination == "/")
    {
        disconnectFromRegister("eax ");
    }
    if (destination == "ret" || skippedRet == true)
    {
        doReturn();
        skippedRet = false;
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
    if (destination == "sys")
    {
        doInterruption(continu);
    }
    if (destination == "str")
    {
        makeNewString(continu);
    }
    int dest = getIndex(destination);
    if (Tokens.at(dest).ifString)
    {
        useStr(continu, destination);
    }

    if (Tokens.at(dest).ifVar || Tokens.at(dest).ifArray) 
    {
        useVar(continu, destination);
    }
    
    if (Tokens.at(dest).ifFunction)
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