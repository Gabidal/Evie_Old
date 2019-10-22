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

void Definer::Pattern_Parenthesis(int i)
{
    Word Paranthes = Word("");
    if (Lines.at(i).find("func") != -1)
    {
        //for parameters
        for (int i = 0; i < )
        {

        }
    }
    else if (Lines.at(i-1).find("func") != -1)
    {
        if (Lines.at(i).find("(") != -1)
        {
            Paranthes.WORD = "(";
            Paranthes.Flags |= FUNCTION_START_PARENTHESIS;
        }
        else if (Lines.at(i).find(")") != -1)
        {
            Paranthes.WORD = ")";
            Paranthes.Flags |= FUNCTION_END_PARENTHESIS;
        }
    }
    else if (Lines.at(i-1).find("type") != -1)
    {
        if (Lines.at(i).find("(") != -1)
        {
            Paranthes.WORD = "(";
            Paranthes.Flags |= TYPE_START_PARENTHESIS;
        }
        else if (Lines.at(i).find(")") != -1)
        {
            Paranthes.WORD = ")";
            Paranthes.Flags |= TYPE_END_PARENTHESIS;
        }
    }
    output.push_back(Paranthes);
}

void Definer::Define(int i)
{

}