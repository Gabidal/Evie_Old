#include "../../H/Parser/Parser.h"

void Parser::Pattern_Variable(int i)
{
    //((var) (a) (:) (b) (= 123))
    if (Input.at(i).is(_KEYWORD) && Input.at(i+1).is(_TEXT) && Input.at(i).WORD == "var" && Input.at(i).UsedToken == false)
    {
        //create new variable;
        Token Var(Assembly);
        Var.Flags |= Variable;
        Var.Flags |= Real;
        if (InsideOfType && InsideOfFunction != true)
        {
            Var.Flags |= Member;
        }
        else if (InsideOfFunction)
        {
            Var.Flags |= Public;
        }
        Output.push_back(Var);
        Input.at(i).UsedToken = true;
    }
    
    if (Input.at(i).is(_OPERATOR) && Input.at(i-1).is(_TEXT) && Input.at(i).WORD == "=")
    {
        //set variable value;
        Pattern_Array(i-1);
    }
}

void Parser::Pattern_Array(int i)
{
    // a : a
    int Mark;
    int Offset;
    int _Owner;
    if (Input.at(i+1).WORD == ":")
    {
        _Owner = i;
        Mark = i+1;
        Offset = i+2;
    }
    else if (Input.at(i-1).WORD == ":")
    {
        _Owner = i-2;
        Mark = i-1;
        Offset = i;
    }
    else if (Input.at(i).WORD == ":")
    {
        _Owner = i-1;
        Mark = i;
        Offset = i+1;
    }
    
    if (Input.at(Mark).UsedToken == false)
    {
        //it is highly possible that the most fresh push to the output vector is the owner of the ofsetter!
        Token *Offsetter;
        Offsetter->Flags |= Array;
        if (Input.at(Offset).is(_NUMBER))
        {
            Offsetter->Flags |= Number;
        }
        else if (Input.at(Offset).is(_TEXT))
        {
            Offsetter->Flags |= Variable;
        }
        Offsetter->Name = Input.at(Offset).WORD;

        Token &Owner = Output.back();
        Owner.Offsetter = Offsetter;

        Input.at(_Owner).Offsetter = &Input.at(Offset);
        
        Input.erase(Input.begin() + Mark);
        Input.erase(Input.begin() + Offset);
    }
}


void Parser::Factory()
{

}