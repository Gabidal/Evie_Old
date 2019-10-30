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
            ParentType->addChild(Var);
        }
        else if (InsideOfFunction)
        {
            Var.Flags |= Private;
            ParentFunc->addChild(Var);
        }
        else
        {
            Output.push_back(Var);
        }
        Input.at(i).UsedToken = true;
    }
}

void Parser::Pattern_Equal(int i)
{
    //set variable value;
    if (Input.at(i).is(_OPERATOR) && Input.at(i-1).is(_TEXT) && Input.at(i).WORD == "=")
    {
        //check for Array definitions;
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

void Parser::Pattern_Locator(int i)
{
    if (Input.at(i).WORD == "&")
    {
        Token ptr(Assembly);
        ptr.Flags |= Ptr;
        ptr.Name = Input.at(i+1).WORD;
        Output.push_back(ptr);
    }
}

void Parser::Pattern_Function(int i)
{
    //func banana(a, &b, c, &d)
    if (Input.at(i).is(_KEYWORD) && Input.at(i).WORD == "func")
    {
        //make new Function;
        Token Name(Assembly);
        Name.Flags |= Function;
        Name.Flags |= Real;
        Name.Name = Input.at(i+1).WORD;
        if (InsideOfType)
        {
            Name.ParentType = ParentType;
            Name.Flags |= Member;
        }
        
        //make the parameters;
        for (int j = 0; j < Input.at(i+2).Tokens.size(); j++)
        {
            if (Input.at(i+2).Tokens.at(j).WORD == "&")
            {
                Token ptr(Assembly);
                ptr.Flags |= Ptr;
                ptr.Flags |= Parameter;
                ptr.Size = 4;
                ptr.Name = Input.at(i+2).Tokens.at(j+1).WORD;
                ptr.ParameterOffset = Name.ParameterCount;
                Name.Parameters.push_back(ptr);
                Name.ParameterCount += ptr.Size;
                j++;
            }
            else if (Input.at(i+2).Tokens.at(j).is(_TEXT))
            {
                Token var(Assembly);
                var.Flags |= Parameter;
                var.Flags |= Variable;
                var.Size = 4;
                var.Name = Input.at(i+2).Tokens.at(j).WORD;
                var.ParameterOffset = Name.ParameterCount;
                Name.Parameters.push_back(var);
                Name.ParameterCount += var.Size;
            }
        }
        Input.erase(Input.begin() + i + 2);
        if (InsideOfType)
        {
            ParentType->addFunc(Name);
        }
        else
        {
            Output.push_back(Name);
        }
        ParentFunc = &Output.back();
    }
    
}

void Parser::Pattern_Type(int i)
{
    //type banana
    if (Input.at(i).WORD == "type")
    {
        Token Type(Assembly);
        Type.Flags |= TypE;
        Type.Flags |= Real;
        Type.Name = Input.at(i+1).WORD;
        Output.push_back(Type);
        ParentType = &Output.back();
    }
}

void Parser::Pattern_Parenthesis(int i)
{
    /*func banana   <deleted () >
    (

    )*/
    if (Input.at(i).is(_PAREHTHESIS) && Input.at(i-2).WORD == "func" && ParentFunc != 0)
    {
        ParentFunc->Flags |= Used;
        InsideOfFunction = true;
        
    }
    
}

void Parser::Factory()
{
 
}