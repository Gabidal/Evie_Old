#include "../../H/Lexer/Definer.h"

int Definer::getWord(char end, string &destination, string source, int continu)
{
    for (;source[continu] == ' ';)
    {
        continu++;
    }
    for (int i = continu; i < source.size();i++)
    {
        if (source[i] != end && source[i] != '\n')
        {
            //abc(a, a)
            destination += source[i];
            if (source[i + 1] == '(')
            {
                return i;
            }
        }
        else
        {
            i++;
            return i;
        }
    }
    return source.size();
}

int Definer::skipReverseParenthesis(int i, string &source)
{
    string dest;
    int offset = getReverseWord('(', dest, source, i - 1);
    return offset;
}

int Definer::getReverseWord(char end, string &destination, string source, int continu)
{
    for (;source[continu] == ' ';continu--);
    for (int i = continu; i >= 0; i--)
    {
        if (source[i] != end && source[i] != '\n')
        {
            if (source[i] == ')')
            {
                i = skipReverseParenthesis(i, source);
            }
            
            destination += source[i];
        }
        else
        {
            i--;
            return i;
            destination.reserve();
        }
    }
    return 0;
}

int Definer::getAmount(char end, vector<int> &destination, string source)
{
    int offset = 0;
    while (true)
    {
        string wanted;
        offset = getWord(end, wanted, source, offset);
        if (source.at(offset) == end)
        {
            destination.push_back(offset);
        }
        else if (offset == source.size() || offset == 0)
        {
            break;
        }
        
    }
    return -1;
}

int Definer::Find(string name, vector<Word> source)
{
    for (int i = 0; i < source.size(); i++)
    {
        if (source.at(i).WORD == name)
        {
            return i;
        }
    }
    return -1;
}

void Definer::Pattern_Func(int i)
{
    //look if Function is made to whole or into an prototype
    if (Lines.at(i).find("func") != -1)
    {
        string name;
        int offset = getWord(' ', name, Lines.at(i), 0);
        name = "";
        offset = getWord('(', name, Lines.at(i), offset);
        Word func = Word(name);
        func.Flags |= _FUNCTION;
        output.push_back(func);
    }
}

void Definer::Pattern_Locater(int i, Word &name)
{
    if (name.WORD.find("&") != -1)
    {
        //if pointing to an memory location;
        name.Flags |= _LOCATER;
    }
    name.Flags |= _VARIABLE;
}

void Definer::Pattern_Parenthesis(int i)
{
    Word Paranthes = Word("");
    if (Lines.at(i).find("func") != -1 && Lines.at(i).find("(") != -1)
    {
        //for parameters
        //first find the ','
        string empty;
        //starting offset;
        int offset = getWord('(', empty, Lines.at(i), 0);

        if (Lines.at(i).find(",") != -1)
        {
            //there are more than one parameter.
            while(true)
            {
                Word Parameter = Word("");
                offset = getWord(',', Parameter.WORD, Lines.at(i), offset);
                Pattern_Locater(i, Parameter);
                Parameter.Flags |= _PARAMETER;
                output.push_back(Parameter);
            }
        }
        //if not find ',' then there is only one parameter
        else
        {
            Word Parameter = Word("");
            offset = getWord(')', Parameter.WORD, Lines.at(i), offset);
            Pattern_Locater(i, Parameter);
            Parameter.Flags |= _PARAMETER;
            output.push_back(Parameter);
        }
        
    }
    else if (Lines.at(i-1).find("func") != -1)
    {
        if (Lines.at(i).find("(") != -1)
        {
            Paranthes.WORD = "(";
            Paranthes.Flags |= _FUNCTION_START_PARENTHESIS;
            INSIDE_OF_FUNC = true;
        }
        else if (Lines.at(i).find(")") != -1)
        {
            Paranthes.WORD = ")";
            Paranthes.Flags |= _FUNCTION_END_PARENTHESIS;
            INSIDE_OF_FUNC = false;
        }
    }
    else if (Lines.at(i-1).find("type") != -1)
    {
        if (Lines.at(i).find("(") != -1)
        {
            Paranthes.WORD = "(";
            Paranthes.Flags |= _TYPE_START_PARENTHESIS;
            INSIDE_OF_TYPE = true;
        }
        else if (Lines.at(i).find(")") != -1)
        {
            Paranthes.WORD = ")";
            Paranthes.Flags |= _TYPE_END_PARENTHESIS;
            INSIDE_OF_TYPE = false;
        }
    }
    output.push_back(Paranthes);
}

void Definer::Pattern_Variable(int i)
{
    //  var a || = 123
    int offset = 0;
    if (Lines.at(i).find("var") != -1)
    {
        //if not working use space after "var ";
        string trash;
        offset = Lines.at(i).find("var");
        offset = getWord(' ', trash, Lines.at(i), offset);
        Word VAR = Word("");
        offset = getWord(' ', VAR.WORD, Lines.at(i), offset);
        VAR.Flags |= _VARIABLE;
        output.push_back(VAR);
    }
}

void Definer::Pattern_Equ(int i)
{
    int offset = 0;
    if ((offset = Lines.at(i).find("=")) != -1)
    {
        Word Equal("=");
        Equal.Flags |= _OPERATOR;
        output.push_back(Equal);
    }
}

void Definer::Pattern_Use(int i, string name)
{
    int offset;
    if ((offset = Find(name, output)) != -1)
    {
        //this happens if the wanted thing has been finded.
        output.at(offset).Flags |= _USED;
        Word newCopy("");
        newCopy = output.at(offset);
        output.push_back(newCopy);
    }
}

void Definer::Pattern_Math(int i)
{
    //a = a + a * a / c(a, a) + a
    vector<int> MathPositions;
    getAmount('+', MathPositions, Lines.at(i));
    getAmount('-', MathPositions, Lines.at(i));
    getAmount('*', MathPositions, Lines.at(i));
    getAmount('/', MathPositions, Lines.at(i));
    for (int j : MathPositions)
    {
        Word Math("");
        Math.WORD = Lines.at(i).at(MathPositions.at(j));
        Math.Flags |= _OPERATOR;
        
        int offset = MathPositions.at(j);
        Word LVar("");
        offset = getReverseWord(' ', LVar.WORD, Lines.at(i), offset);
        LVar.Flags |= _VARIABLE;
        LVar.Flags |= _USED;
        Math.LeftLink = &LVar;

        offset = MathPositions.at(j);
        Word RVar("");
        offset = getWord(' ', RVar.WORD, Lines.at(i), offset);
        RVar.Flags |= _VARIABLE;
        RVar.Flags |= _USED;
        Math.RightLink = &RVar;


        output.push_back(Math);
    }
}

void Definer::Define(int i)
{

}