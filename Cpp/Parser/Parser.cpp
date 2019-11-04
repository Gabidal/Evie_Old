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

void Parser::Pattern_Operators(int i)
{
    //set variable value;
    //a : a = b
    //a() + b
    if (Input.at(i).is(_OPERATOR) && Input.at(i-1).is(_TEXT) && Input.at(i).UsedToken == true)
    {
        Token OP(Assembly);
        OP.Flags |= OPERATOR;
        OP.Name = Input.at(i).WORD;

        Token A = Pattern_Child(Input.at(i).Tokens.at(0));
        Token B = Pattern_Child(Input.at(i).Tokens.at(1));
        
        OP.Parameters.push_back(A);
        OP.Childs.push_back(B);
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
                Name.addParameter(ptr);
                j++;
            }
            else if (Input.at(i+2).Tokens.at(j).is(_TEXT))
            {
                Token var(Assembly);
                var.Flags |= Parameter;
                var.Flags |= Variable;
                var.Size = 4;
                var.Name = Input.at(i+2).Tokens.at(j).WORD;
                
                Name.addParameter(var);
            }
        }
        Input.erase(Input.begin() + i + 2);
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
    }
}

void Parser::Pattern_Parenthesis(int i)
{
    /*func banana <deleted () > \n
    (
        var c = a + a
        b = d + c
    )*/
    if (Input.at(i).is(_PAREHTHESIS) && Input.at(i-3).WORD == "func" && ParentFunc != 0)
    {
        InsideOfFunction = true;
        Layer++;

        Parser parser(Input.at(i).Tokens);
        parser.ParentFunc = &Output.back();
        parser.Factory();
        ParentFunc = parser.ParentFunc;

        for (int i = 0; i < parser.Output.size(); i++)
        ParentFunc->addChild(parser.Output.at(i));
        ParentFunc->Flags |= PARENT;

        Layer--;
    }
    /*type banana
    (
        var 1
    )*/
    else if (Input.at(i).is(_PAREHTHESIS) && Input.at(i-3).WORD == "type" && ParentType != 0)
    {
        InsideOfType = true;
        Layer++;
        Parser parser(Input.at(i).Tokens);
        parser.ParentType = &Output.back();
        parser.Factory();
        ParentType = parser.ParentType;

        for (int i = 0; i < parser.Output.size(); i++)
        ParentType->addChild(parser.Output.at(i));
        ParentType->Flags |= PARENT;

        Layer--;
    }
    /*if ( a == b & a == c)
    (
        var 1
    )*/
    else if (Input.at(i).is(_PAREHTHESIS) && Input.at(i-1).WORD == "if")
    {
        Token IF(Assembly);
        IF.Flags |= PARENT & If & Used;
        IF.Name = to_string(ID) + "_if";

        Parser parser1(Input.at(i).Tokens);

        for (int i = 0; i < parser1.Output.size(); i++)
        IF.addParameter(parser1.Output.at(i));

        Parser parser2(Input.at(i+2).Tokens);

        for (int i = 0; i < parser2.Output.size(); i++)
        IF.addChild(parser2.Output.at(i));

        Output.push_back(IF);
    }
    /*while (a < b)
    (
        var 1
    )*/
    else if (Input.at(i).is(_PAREHTHESIS) && Input.at(i-1).WORD == "while")
    {
        Token WHILE(Assembly);
        WHILE.Flags |= PARENT & If & Used;
        WHILE.Name = to_string(ID) + "_while";

        Parser parser1(Input.at(i).Tokens);

        for (int i = 0; i < parser1.Output.size(); i++)
        WHILE.addParameter(parser1.Output.at(i));

        Parser parser2(Input.at(i+2).Tokens);

        for (int i = 0; i < parser2.Output.size(); i++)
        WHILE.addChild(parser2.Output.at(i));

        Output.push_back(WHILE);
    }
    
}

void Parser::Pattern_Init_Operators(int i)
{
    //a = b + c
    if (Input.at(i).is(_OPERATOR) && Input.at(i).UsedToken != true)
    {
        Input.at(i).Tokens.push_back(Input.at(i-1)); //b
        Input.at(i).Tokens.push_back(Input.at(i+1)); //c
        Input.erase(Input.begin() + i-1);
        Input.erase(Input.begin() + i+1);
        Input.at(i).UsedToken = true;
    }
}

Token Parser::Pattern_Child(Word w)
{
    Token t(Assembly);
    t.Name = w.WORD;
    if (InsideOfFunction)
    {
        t.Flags |= Private;
    }
    if (InsideOfType)
    {
        t.Flags |= Member;
    }
    if (w.Offsetter != 0)
    {
        t.Flags |= Array;
    }
    if (w._func)
    {
        t.Flags |= Call;
    }
    else
    {
        t.Flags |= Variable;
        t.Size = 4;
    }
    return t;
}

void Parser::Pattern_Init_Call_Func(int i)
{
    if (Input.at(i).is(_PAREHTHESIS) && Input.at(i-1).is(_TEXT) && Input.at(i-2).WORD != "func")
    {
        Input.at(i).WORD = Input.at(i-1).WORD;
        Input.at(i)._func = true;
        Input.erase(Input.begin() + i-1);
    }
}

void Parser::Pattern_Call_Func(int i)
{
    if (Input.at(i).is(_PAREHTHESIS) && Input.at(i)._func)
    {
        Token func(Assembly);
        func.Flags |= Call && Function;
        func.Name = Input.at(i).WORD;
        vector<Token> t;
        if (ParentType != 0)
        {
            t = ParentType->Childs;
        }
        else if (ParentType == 0)
        {
            t = Output;
        }
        
        
        if (int j = Find(func.Name, Function, t) != -1)
        {
            Output.at(j).Flags |= Used;
        }
        for (int j = 0; j < Input.at(i).Tokens.size(); j++)
        {
            if (Input.at(i+2).Tokens.at(j).WORD == "&")
            {
                Token ptr(Assembly);
                ptr.Flags |= Ptr;
                ptr.Flags |= Parameter;
                ptr.Size = 4;
                ptr.Name = Input.at(i+2).Tokens.at(j+1).WORD;
                func.addParameter(ptr);
                j++;
            }
            else if (Input.at(i+2).Tokens.at(j).is(_TEXT))
            {
                Token var(Assembly);
                var.Flags |= Parameter;
                var.Flags |= Variable;
                var.Size = 4;
                var.Name = Input.at(i+2).Tokens.at(j).WORD;
                
                func.addParameter(var);
            }
        }
        
        Output.push_back(func);
    }
    
}

int Parser::Find(string name, int flag, vector<Token> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list.at(i).Name == name && list.at(i).is(flag))
        {
            return i;
        }
    }
    return -1;
}

void Parser::Factory()
{
 
}