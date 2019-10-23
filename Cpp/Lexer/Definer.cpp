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
            destination += source[i];
        }
        else
        {
            i++;
            return i;
        }
    }
    return source.size();
}

int Definer::getReverseWord(char end, string &destination, string source, int continu)
{
    for (;source[continu] == ' ';continu--);
    for (int i = continu; i >= 0; i--)
    {
        if (source[i] != end && source[i] != '\n')
        {
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
        func.Flags |= FUNCTION;
        output.push_back(func);
    }
}

void Definer::Pattern_Locater(int i, Word &name)
{
    if (name.WORD.find("&") != -1)
    {
        //if pointing to an memory location;
        name.Flags |= LOCATER;
    }
    name.Flags |= VARIABLE;
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
                Parameter.Flags |= PARAMETER;
                output.push_back(Parameter);
            }
        }
        //if not find ',' then there is only one parameter
        else
        {
            Word Parameter = Word("");
            offset = getWord(')', Parameter.WORD, Lines.at(i), offset);
            Pattern_Locater(i, Parameter);
            Parameter.Flags |= PARAMETER;
            output.push_back(Parameter);
        }
        
    }
    else if (Lines.at(i-1).find("func") != -1)
    {
        if (Lines.at(i).find("(") != -1)
        {
            Paranthes.WORD = "(";
            Paranthes.Flags |= FUNCTION_START_PARENTHESIS;
            INSIDE_OF_FUNC = true;
        }
        else if (Lines.at(i).find(")") != -1)
        {
            Paranthes.WORD = ")";
            Paranthes.Flags |= FUNCTION_END_PARENTHESIS;
            INSIDE_OF_FUNC = false;
        }
    }
    else if (Lines.at(i-1).find("type") != -1)
    {
        if (Lines.at(i).find("(") != -1)
        {
            Paranthes.WORD = "(";
            Paranthes.Flags |= TYPE_START_PARENTHESIS;
            INSIDE_OF_TYPE = true;
        }
        else if (Lines.at(i).find(")") != -1)
        {
            Paranthes.WORD = ")";
            Paranthes.Flags |= TYPE_END_PARENTHESIS;
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
        VAR.Flags |= VARIABLE;
        if (INSIDE_OF_FUNC)
        {
            VAR.Flags |= MEMBER;
        }
        else if (INSIDE_OF_TYPE)
        {
            VAR.Flags |= PRIVATE;
        }
        output.push_back(VAR);
        Previus = output.at(output.size() - 1);
    }
}

void Definer::Pattern_Use(int i)
{
    int offset = 0;
    if ((offset = Lines.at(i).find("=")) != -1)
    {
        Word Equal("=");
        Equal.Flags |= OPERATOR;
        output.push_back(Equal);
    }
}

void Definer::Define(int i)
{

}