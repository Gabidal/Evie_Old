#include "../../H/Parser/Parser.h"

void Parser::Pattern_Init_Variable(int i)
{
    //((var) (a) (:) (b) (= 123))
    if (Input.at(i)->is(_KEYWORD) && Input.at(i+1)->is(_TEXT) && Input.at(i)->WORD == "var" && Input.at(i)->UsedToken == false)
    {
        //create new variable;
        Token *Var = new Token(Assembly);
        Var->Flags |= Variable;
        Var->Name = Input.at(i+1)->WORD;
        Var->Size = 4;
        if (InsideOfType && InsideOfFunction != true)
        {
            Var->Flags |= Member;
            ParentType->addChild(Var);
        }
        else if (InsideOfFunction)
        {
            Var->Flags |= Private;
            ParentFunc->addChild(Var);
        }
        else
        {
            Output.push_back(Var);
        }
        Input.at(i)->UsedToken = true;
    }
}

void Parser::Pattern_Variable(int i)
{
    vector<Token*> *T;
    if ((Input.at(i)->is(_TEXT) == false) && (Input.at(i)->is(_NUMBER) == false))
    {
        return;
    }
    if (Priority == false)
    {
        return;
    }
    
    Give_Input(T);
    
    if (Input.at(i)->is(_TEXT) && Find(Input.at(i)->WORD, Variable, *T) != -1)
    {
        int j = Find(Input.at(i)->WORD, Variable, *T);
        if ((i > 0 && Input.at(i-1)->WORD != "var") || Started != 0)
        {
            T->at(j)->Flags |= Used;
        }
        Token *t = new Token(Assembly);
        t = T->at(j);
        t->Size = 4;
        if (Input.at(i)->Offsetter != 0)
        {
            //if it is an array
            //if the offsetter is a Variable
            int k = Find(Input.at(i)->Offsetter->WORD, Variable, *T);
            if (k == -1)
            {
                //if the offsetter is a number
                k = Find(Input.at(i)->Offsetter->WORD, Number, *T);
            }
            if (k == -1)
            {
                //if the offsetter is a function
                k = Find(Input.at(i)->Offsetter->WORD, Call, *T);
            }
            if (k == -1)
            {
                //go foo youre self!
                return;
            }
            
            
            Token *ofsetter = new Token(Assembly);
            t = T->at(k);
            t->Offsetter = ofsetter;
            t->Flags |= Array;
            t->Size = 4;
        }
        if (Input.at(i)->_type)
        {
            //do fetching;
            Give_Input(T);
            int k = Find(Input.at(i)->Fetcher, NotOriginal, *T);
            t->Fetcher = T->at(k);
        }
        
        if (Priority)
        {
            Give_Output(T);
            T->push_back(t);
        }
        
    }
    Give_Input(T);
    if (Input.at(i)->is(_NUMBER))
    {
        Token *n = new Token(Assembly);
        n->Flags |= Number;
        n->Flags |= Real;
        n->Flags |= Used;
        n->Name = Input.at(i)->WORD;
        if (Priority)
        {
            Give_Output(T);
            T->push_back(n);
        }
    }
}

void Parser::Pattern_Operators(int i)
{
    //set variable value;
    //a <: a> = b
    //c = a<()> + b
    if (Input.at(i)->is(_OPERATOR) && Input.at(i)->Tokens.size() > 0 && Input.at(i)->UsedToken == true)
    {
        Token *OP = new Token(Assembly);
        OP->Flags |= OPERATOR;
        OP->Flags |= Used;
        OP->Name = Input.at(i)->WORD;

        Parser p = *this;
        p.Input = Input.at(i)->Tokens;
        p.Started = Input.at(i)->Tokens.size();
        p.Priority = true;
        
        p.Factory();
        //check this also in debugging!!!
        Token *A = new Token(Assembly);
        Token *B = new Token(Assembly);
        if (InsideOfFunction)
        {
            A = ParentFunc->Childs.at(ParentFunc->Childs.size() - 2);
            B = ParentFunc->Childs.at(ParentFunc->Childs.size() - 1);
            ParentFunc->Childs.erase(ParentFunc->Childs.begin() + ParentFunc->Childs.size() - 1);
            ParentFunc->Childs.erase(ParentFunc->Childs.begin() + ParentFunc->Childs.size() - 1);
        }
        else if (InsideOfType)
        {
            A = ParentType->Childs.at(ParentType->Childs.size() - 2);
            B = ParentType->Childs.at(ParentType->Childs.size() - 1);
            ParentType->Childs.erase(ParentType->Childs.begin() + ParentType->Childs.size() - 1);
            ParentType->Childs.erase(ParentType->Childs.begin() + ParentType->Childs.size() - 1);
        }
        else
        {
            A = p.Output.at(p.Output.size() - 2);
            B = p.Output.at(p.Output.size() - 1);
            p.Output.erase(p.Output.begin() + p.Output.size() - 1);
            p.Output.erase(p.Output.begin() + p.Output.size() - 1);
        }
        
        OP->Parameters.push_back(A);
        OP->Childs.push_back(B);

        vector<Token*> *T;
        Give_Output(T);
        T->push_back(OP);
    }
}

void Parser::Pattern_Init_Array(int i)
{
    // a : a
    int Mark;
    int Offset;
    int _Owner;
    if (i == Input.size() - 1)
    {
        return;
    }
    else if (i < 1)
    {
        return;
    }
    
    if (Input.at(i+1)->WORD == ":")
    {
        _Owner = i;
        Mark = i+1;
        Offset = i+2;
    }
    else if (Input.at(i-1)->WORD == ":")
    {
        _Owner = i-2;
        Mark = i-1;
        Offset = i;
    }
    else if (Input.at(i)->WORD == ":")
    {
        _Owner = i-1;
        Mark = i;
        Offset = i+1;
    }
    else
    {
        return;
    }
    if (Input.at(Mark)->UsedToken == false)
    {
        Input.at(_Owner)->Offsetter = Input.at(Offset);
        
        Input.erase(Input.begin() + Mark);
        Input.erase(Input.begin() + Offset - 1);
    }
}

/*void Parser::Pattern_Init_Locator(int i)
{
    if (Input.at(i)->WORD == "&")
    {
        Token *ptr = new Token(Assembly);
        ptr.Flags |= Ptr;
        ptr.Name = Input.at(i+1)->WORD;
        Output.push_back(ptr);
    }
}*/

void Parser::Pattern_Function(int i)
{
    //func banana(a, &b, c, &d)
    if (Input.at(i)->is(_KEYWORD) && Input.at(i)->WORD == "func")
    {
        //make new Function;
        Token *Name = new Token(Assembly);
        Name->Flags |= Function;
        Name->Flags |= Real;
        Name->Name = Input.at(i+1)->WORD;
        if (InsideOfType)
        {
            Name->ParentType = ParentType;
            Name->Flags |= Member;
        }
        
        //make the parameters;
        for (int j = 0; j < Input.at(i+2)->Tokens.size(); j++)
        {
            if (Input.at(i+2)->Tokens.at(j)->WORD == "&")
            {
                Token *ptr = new Token(Assembly);
                ptr->Flags |= Ptr;
                ptr->Flags |= Parameter;
                ptr->Size = 4;
                ptr->Name = Input.at(i+2)->Tokens.at(j+1)->WORD;
                Name->addParameter(ptr);
                j++;
            }
            else if (Input.at(i+2)->Tokens.at(j)->is(_TEXT))
            {
                Token *var = new Token(Assembly);
                var->Flags |= Parameter;
                var->Flags |= Variable;
                var->Size = 4;
                var->Name = Input.at(i+2)->Tokens.at(j)->WORD;
                
                Name->addParameter(var);
            }
        }
        Input.erase(Input.begin() + i + 2);
        vector<Token*> *T;
        Give_Output(T);
        T->push_back(Name);
    }
    
}

void Parser::Pattern_Type(int i)
{
    //type banana
    if (Input.at(i)->WORD == "type")
    {
        Token *Type = new Token(Assembly);
        Type->Flags |= TypE;
        Type->Flags |= Real;
        Type->Name = Input.at(i+1)->WORD;
        vector<Token*> *T;
        Give_Output(T);
        T->push_back(Type);
    }
}

void Parser::Pattern_Parenthesis(int i)
{
    /*func banana <deleted () > \n
    (
        var c = a + a
        b = d + c
    )*/
    if (Input.at(i)->is(_PAREHTHESIS) && (Input.at(i-3)->WORD == "func"))
    {
        vector<Token*> *T;
        Give_Output(T);
        int j = Find(Input.at(i-2)->WORD, Function, *T);
        ParentFunc = T->at(j);

        Layer++;
        Parser parser = *this;
        parser.Input = Input.at(i)->Tokens;
        parser.InsideOfFunction = true;
        parser.Started = Output.size();
        parser.Factory();
        ParentFunc->Flags |= PARENT;
        Layer--;
    }
    /*type banana
    (
        var 1
    )*/
    else if (Input.at(i)->is(_PAREHTHESIS) && Input.at(i-3)->WORD == "type")
    {
        vector<Token*> *T;
        Give_Output(T);

        int j = Find(Input.at(i-2)->WORD, TypE, *T);
        ParentType = T->at(j);

        Layer++;
        Parser parser = *this;
        parser.Input = Input.at(i)->Tokens;
        parser.InsideOfType = true;
        parser.Started = Output.size();
        parser.Factory();
        ParentType->Flags |= PARENT;
        Layer--;
    }
    /*if ( a == b & a == c)
    (
        var 1
    )*/
    else if (Input.at(i)->is(_PAREHTHESIS) && Input.at(i-1)->WORD == "if")
    {
        Token *IF = new Token(Assembly);
        IF->Flags |= PARENT & If & Used;
        IF->Name = to_string(ID) + "_if";

        Parser parser1 = *this;
        parser1.Input = Input.at(i)->Tokens;

        for (int i = parser1.Started; i < parser1.Output.size(); i++)
        IF->addParameter(parser1.Output.at(i));

        Parser parser2 = *this;
        parser2.Input = Input.at(i+2)->Tokens;

        for (int i = parser2.Started; i < parser2.Output.size(); i++)
        IF->addChild(parser2.Output.at(i));

        vector<Token*> *T;
        T->push_back(IF);
    }
    /*while (a < b)
    (
        var 1
    )*/
    else if (Input.at(i)->is(_PAREHTHESIS) && Input.at(i-1)->WORD == "while")
    {
        Token *WHILE = new Token(Assembly);
        WHILE->Flags |= PARENT & If & Used;
        WHILE->Name = to_string(ID) + "_while";

        Parser parser1 = *this;
        parser1.Input = Input.at(i)->Tokens;

        for (int i = 0; i < parser1.Output.size(); i++)
        WHILE->addParameter(parser1.Output.at(i));

        Parser parser2 = *this;
        parser2.Input = Input.at(i+2)->Tokens;

        for (int i = 0; i < parser2.Output.size(); i++)
        WHILE->addChild(parser2.Output.at(i));

        vector<Token*> *T;
        T->push_back(WHILE);
    }
    
}

void Parser::Pattern_Init_Operators(int &i)
{
    //<a = b>
    if (Input.at(i)->is(_OPERATOR) && Input.at(i)->UsedToken != true)
    {
        Input.at(i)->Tokens.push_back(Input.at(i-1)); //a
        Input.at(i)->Tokens.push_back(Input.at(i+1)); //b
        Input.erase(Input.begin() + i-1);
        Input.erase(Input.begin() + i);
        Input.at(i-1)->UsedToken = true;
        i--;
    }
}

void Parser::Pattern_Init_Call_Func(int i)
{
    //banana(1, 2)
    if (Input.at(i)->is(_PAREHTHESIS) && Input.at(i-1)->is(_TEXT) && Input.at(i-2)->WORD != "func")
    {
        Input.at(i-1)->Tokens = Input.at(i)->Tokens;
        Input.at(i-1)->_func = true;
        Input.at(i-1)->Flags |= _PAREHTHESIS;
        Input.erase(Input.begin() + i);
    }
}

void Parser::Pattern_Call_Func(int i)
{
    if (Input.at(i)->is(_PAREHTHESIS) && Input.at(i)->_func)
    {
        Token *func = new Token(Assembly);
        func->Flags |= Call;
        //func->Flags |= Function;
        func->Name = Input.at(i)->WORD;
        vector<Token*> *t;
        if (Input.at(i)->_type)
        {
            func->Flags |= This;
            func->Fetcher = Pattern_Fetcher(i);
            func->Flags |= Private;
        }
        

        /*
        Give_Input(t);
        if (Find(func->Name, Function, *t) != -1)
        {
            int j = Find(func->Name, Function, *t);
            t->at(j)->Flags |= Used;
        }*/

        if (Input.at(i)->Tokens.size() > 0)
        {
            Parser p = *this;
            p.Input = Input.at(i)->Tokens;
            p.Priority = true;
            p.GetDirect = true;
            p.Factory();
            for (int k = 0; k < p.Direct.size(); k++)
                func->addParameter(p.Direct.at(k));
        }
        Give_Output(t);
        t->push_back(func);
    }
    
}

void Parser::Pattern_Init_Type(int i)
{
    /*type banana
    (
        var a = 1
        apple(a, b, c)
    )
    new banana b
    <b.apple>(a, b, c)
    <b.a> : <b.a> = <b.a> : <b.a>
    */
    if (Input.at(i)->is(_OPERATOR) && Input.at(i)->WORD == ".")
    {
        Input.at(i+1)->_type = true;
        Input.at(i+1)->Fetcher = Input.at(i-1)->WORD;
        Input.erase(Input.begin() + i);
        Input.erase(Input.begin() + i-1);
    }
}

void Parser::Pattern_Init_New(int i)
{
    /*
    new banana b
    */
    if (Input.at(i)->is(_KEYWORD) && Input.at(i)->WORD == "new")
    {
        Input.at(i)->Tokens.push_back(Input.at(i+1));
        Input.at(i)->Tokens.push_back(Input.at(i+2));
        Input.erase(Input.begin() + i + 1);
        Input.erase(Input.begin() + i + 1);
    }
}

void Parser::Pattern_New(int i)
{
    /*
    new banana b
    */
    if (Input.at(i)->is(_KEYWORD) && Input.at(i)->WORD == "new")
    {
        // the template type classes are always made global
        vector<Token*> *T;
        Give_Output(T);
        int j = Find(Input.at(i)->Tokens.at(0)->WORD, TypE, Output);
        Token *t = new Token(Assembly);
        t->Childs = Output.at(j)->Childs;
        t->Name = Input.at(i)->Tokens.at(1)->WORD;
        t->Origin = Output.at(j);
        t->Flags |= __NEW;
        t->Flags |= NotOriginal;
        t->Flags |= Ptr;
        for (int k = 0; k < t->Childs.size(); k++)
        {
            if (t->Childs.at(k)->Size > 0)
            {
                t->Size += t->Childs.at(k)->Size;
            }
        }
        

        Output.at(j)->Flags |= Used;
        T->push_back(t);
    }
}

void Parser::Pattern_Return(int i)
{
    //return <a : b>
    if (Input.at(i)->is(_KEYWORD) && Input.at(i)->WORD == "return")
    {
        Token *r = new Token(Assembly);
        Parser p = *this;
        p.Priority = true;
        p.Input.clear();
        p.Input.push_back(Input.at(i+1));
        p.Factory();
        r->Name = "return";
        r->Childs.push_back(ParentFunc->Childs.at(ParentFunc->Childs.size() - 1));
        ParentFunc->Childs.erase(ParentFunc->Childs.begin() + ParentFunc->Childs.size() - 1);
        ParentFunc->Childs.push_back(r);
        ParentFunc->Flags |= Returning;
        Input.erase(Input.begin() + i+1);
    }
    
}

void Parser::Clean_Cilds()
{
    for (int j = 0; j < ParentFunc->Parameters.size(); j++)
    { 
        /*for (int k = 0; k < ParentFunc->Parameters.size(); k++)
        {
            if (ParentFunc->Childs.size() < 1 || ParentFunc->Parameters.size() < 1)
            {
                return;
            }
            if (ParentFunc->Childs.at(k).Name == ParentFunc->Parameters.at(j).Name)
            {
                ParentFunc->Childs.erase(ParentFunc->Childs.begin() + k);
                k--;
            }
        }*/
        if (ParentFunc->Childs.at(j)->Name == ParentFunc->Parameters.at(j)->Name)
        {
            ParentFunc->Childs.erase(ParentFunc->Childs.begin() + j);
        }
    }
}

Token *Parser::Pattern_Fetcher(int i)
{
    //banana.a
    if (Input.at(i)->_type)
    {
        vector<Token*> *T;
        Give_Input(T);
        int j = Find(Input.at(i)->Fetcher, NotOriginal, *T);
        Token *t = new Token(Assembly);
        if (j == -1)
        {
            return t;
        }
        t = T->at(j);
        return t;
    }
}

int Parser::Find(string name, int flag, vector<Token*> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list.at(i)->Name == name && list.at(i)->is(flag))
        {
            return i;
        }
    }
    return -1;
}

void Parser::Give_Input(vector<Token*> *&T)
{
    T = new vector<Token*>;
    if (InsideOfFunction)
    {
        if (ParentFunc->Parameters.size() > 0)
        {
            for (int i = 0; i < ParentFunc->Parameters.size(); i++)
                T->push_back(ParentFunc->Parameters.at(i));
        }
        for (int i = 0; i < ParentFunc->Childs.size(); i++)
            T->push_back(ParentFunc->Childs.at(i));
    }
    if (InsideOfType)
    {
        for (int i = 0; i < ParentType->Childs.size(); i++)
            T->push_back(ParentType->Childs.at(i));
    }
    for (int i = 0; i < Output.size(); i++)
    {
        if (Output.at(i)->Childs.size() > 0)
        {
            for (int j = 0; j < Output.at(i)->Childs.size(); j++)
            {
                T->push_back(Output.at(i)->Childs.at(j));
            }
        }
    }
    for (int i = 0; i < Output.size(); i++)
        T->push_back(Output.at(i));
}

void Parser::Give_Output(vector<Token*> *&T)
{
    if (GetDirect)
    {
        T = &Direct;
    }
    else if (InsideOfFunction)
    {
        T = &ParentFunc->Childs;
    }
    else if (InsideOfType)
    {
        T = &ParentType->Childs;
    }
    else
    {
        T = &Output;
    }
}

void Parser::Factory()
{
    for (int i = 0; i < Input.size(); i++)
    {
        //for Inits;
        Pattern_Init_New(i);
        Pattern_Init_Type(i);
        Pattern_Init_Call_Func(i);
        Pattern_Init_Array(i);
        Pattern_Init_Variable(i);
        Pattern_Init_Operators(i);
    }
    for (int i = 0; i < Input.size(); i++)
    {
        //for Makers;
        Pattern_New(i);
        Pattern_Function(i);
        Pattern_Type(i);
        Pattern_Parenthesis(i);
        Pattern_Call_Func(i);
        Pattern_Operators(i);
        Pattern_Variable(i);
        Pattern_Return(i);
    }
}