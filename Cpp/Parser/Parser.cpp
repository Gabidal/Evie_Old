#include "../../H/Parser/Parser.h"

int ID = 0;

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
            Var->Flags |= Public;
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
        Token *t = new Token(Assembly);
        *t = *T->at(j);
        t->Size = 4;
        if (InsideOfFunction || InsideOfType || InsideOfCondition)
        {
            t->Flags |= Private;
        }else
        {
            t->Flags |= Public;
        }
        
        
        if (Input.at(i)->Offsetter != 0)
        {
            Parser p = *this;
            p.Input.clear();
            p.Input.push_back(Input.at(i)->Offsetter);
            p.GetDirect = true;
            p.Priority = true;
            p.Factory();
            Token *off = new Token(Assembly);
            off = p.Direct.at(0);
            t->Offsetter = off;
        }

        if (Input.at(i)->_type)
        {
            //do fetching;
            Give_Input(T);
            int k = Find(Input.at(i)->Fetcher, NotOriginal, *T);
            *t->Fetcher = *T->at(k);
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
        if (InsideOfType || InsideOfFunction)
        {
            n->Flags |= Private;
        }
        
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
        OP->Name = Input.at(i)->WORD;

        Parser p = *this;
        p.Input = Input.at(i)->Tokens;
        p.Started = Input.at(i)->Tokens.size();
        p.Priority = true;
        
        p.Factory();
        //check this also in debugging!!!
        Token *A = new Token(Assembly);
        Token *B = new Token(Assembly);
        if (InsideOfCondition)
        {
            A = ParentCondition->Childs.at(ParentCondition->Childs.size() - 2);
            B = ParentCondition->Childs.at(ParentCondition->Childs.size() - 1);
            ParentCondition->Childs.erase(ParentCondition->Childs.begin() + ParentCondition->Childs.size() - 1);
            ParentCondition->Childs.erase(ParentCondition->Childs.begin() + ParentCondition->Childs.size() - 1);
        }
        else if (InsideOfFunction)
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
    if (Input.at(i)->is(_OPERATOR) && Input.at(i)->WORD == ":")
    {
        Pattern_Init_Type(i + 2);
        Pattern_Init_Type(i - 2);
        Pattern_Init_Call_Func(i + 1);
        Pattern_Init_Call_Func(i - 1);
        Input.at(i-1)->Offsetter = Input.at(i+1);
        Input.erase(Input.begin() + i); // :
        Input.erase(Input.begin() + i); // offsetter
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

void Parser::Pattern_Condition(int i)
{
    //if ( a == b & a == c)
    if (Input.at(i)->_condition)
    {
        Token *condition = new Token(Assembly);

        if (Input.at(i)->WORD != "else")
        {
            Parser p = *this;
            p.Input = Input.at(i)->Tokens;
            p.GetDirect = true;
            p.Factory();
            condition->Parameters = p.Direct;
            if (Input.at(i)->_else_if)
            {
                condition->Flags |= If;
                condition->Flags |= Else;
                Substitute = ParentCondition;  // give if an place to be for time being;
            }
            else if (Input.at(i)->WORD == "if")
            {
                condition->Flags |= If;
            }
            else if (Input.at(i)->WORD == "while")
            {
                condition->Flags |= If;
                condition->Flags |= While;
            }
        }
        else
        {
            condition->Flags |= Else;
            Substitute = ParentCondition; // give if an place to be for time being;
        }
        
        condition->Name = Input.at(i)->WORD;
        condition->ID = ID;
        ID++;
        if (InsideOfFunction || InsideOfType)
        {
            condition->Flags |= Private;
        }
        
        vector<Token*> *T;
        Give_Output(T);
        T->push_back(condition);
        ParentCondition = condition;
    }
    
}

void Parser::Pattern_Parenthesis(int i)
{
    if (Input.size() - 1 < i && Input.size() - 1 - 3 < 0)
    {
        return;
    }
    
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
    else if (Input.at(i)->is(_PAREHTHESIS) && Input.at(i-2)->WORD == "if" && Input.at(i-2)->_condition)
    {
        Layer++;
        Parser parser = *this;
        parser.Input = Input.at(i)->Tokens;
        parser.InsideOfCondition = true;
        parser.Started = Output.size();
        parser.Factory();
        ParentCondition->Flags |= PARENT;
        if (Input.at(i-2)->_else_if)
        {
            ParentCondition->Flags |= Successour;
            Substitute->SuccessorToken.push_back(ParentCondition);
            ParentCondition->Former = Substitute;
            ParentCondition = Substitute;
        }
        
        Layer--;
    }
    /*else
    (
        var 1
    )*/
    else if (Input.at(i)->is(_PAREHTHESIS) && Input.at(i-2)->WORD == "else" &&  Input.at(i-2)->_condition)
    {
        Layer++;
        Parser parser = *this;
        parser.Input = Input.at(i)->Tokens;
        parser.InsideOfCondition = true;
        parser.Started = Output.size();
        parser.Factory();
        ParentCondition->Flags |= PARENT;
        ParentCondition->Flags |= Successour;
        Substitute->SuccessorToken.push_back(ParentCondition);
        ParentCondition->Former = Substitute;
        ParentCondition = Substitute;
        Layer--;
    }
    /*while (a < b)
    (
        var 1
    )*/
    else if (Input.at(i)->is(_PAREHTHESIS) && Input.at(i-2)->WORD == "while" &&  Input.at(i-2)->_condition)
    {
        Layer++;
        Parser parser = *this;
        parser.Input = Input.at(i)->Tokens;
        parser.InsideOfCondition = true;
        parser.Started = Output.size();
        parser.Factory();
        ParentFunc->Flags |= PARENT;
        Layer--;
    }
    
}

void Parser::Pattern_Init_Condition(int i)
{
    if (Input.at(i)->is(_KEYWORD) && (Input.at(i)->WORD == "if" || Input.at(i)->WORD == "else" || Input.at(i)->WORD == "while"))
    {
        //if (<a == <a + b>>)
        if (Input.at(i)->WORD == "else")
        {
            if (Input.at(i+1)->WORD == "if")
            {
                //else if;
                i++;
                Input.at(i)->Tokens = Input.at(i+1)->Tokens;
                Input.erase(Input.begin() + i + 1);
                Input.at(i)->_else_if = true;
                Input.erase(Input.begin() + i - 1);
                i--;
            }
            else
            {
                //just else;
            }
        }
        else
        {
            Input.at(i)->Tokens = Input.at(i+1)->Tokens;
            Input.erase(Input.begin() + i + 1);
        }
        Input.at(i)->_condition = true;
    }
}

void Parser::Pattern_Init_Operators(int &i)
{
    //<a = b>
    if (Input.at(i)->is(_OPERATOR) && Input.at(i)->UsedToken != true)
    {
        Pattern_Init_Call_Func(i+2);
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
    if (Input.size() - 1 < i)
    {
        return;
    }
    
    if (Input.at(i)->_func == false && Input.at(i)->is(_PAREHTHESIS) && Input.at(i-1)->is(_TEXT) && Input.at(i-2)->WORD != "func")
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

        
        Give_Output(t);
        if (Find(func->Name, Function, *t) != -1)
        {
            int j = Find(func->Name, Function, *t);
            t->at(j)->Flags |= Used;
        }

        Give_Input(t);
        int j = 0;
        if ((j = Find(func->Name, Returning, *t)) != -1)
        {
            func->Flags |= Returning;
        }
        

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
            return nullptr;
        }
        t = T->at(j);
        return t;
    }
    return nullptr;
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
    else if (InsideOfCondition)
    {
        T = &ParentCondition->Childs;
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

void Parser::Pattern_Array(int i)
{
    vector<Token*> *T;
    Give_Output(T);
    if (T->at(i)->Offsetter != 0)
    {
        T->at(i)->Flags |= Ptr;
    }
}

void Parser::Pattern_Init_String(int i)
{
    if (Input.at(i)->is(_STRING) || Input.at(i)->WORD == "\"")
    {
        string Result = "";
        for (int j = i + 1; j < Input.size(); j++)
        {
            if (Input.at(j)->is(_STRING) || Input.at(j)->WORD == "\"")
            {
                Input.erase(Input.begin() + j);
                break;
            }
            else
            {
                Result += Input.at(j)->WORD;
                Input.erase(Input.begin() + j);
                j--;
            }
        }
        Input.at(i)->WORD = Result;
    }
}

void Parser::Pattern_Include(int i)
{
    if (Input.at(i)->WORD == "using")
    {
        string tmp = "/home/gabidalg/GAS/IO/";
        string tmp2 = (tmp + Input.at(i + 1)->WORD).c_str();
        Input.erase(Input.begin() + i);
        Input.erase(Input.begin() + i);
        Definer *d = new Definer();
        d->OpenFile(tmp2.c_str());
        Parser p(d->output, Assembly);
        p.Factory();
        
        for (int j = 0; j < p.Output.size(); j++)
            Output.push_back(p.Output.at(j));
        
    }
}

void Parser::Pattern_Comments(int i)
{
    if (Input.at(i)->is(_COMMENT) || Input.at(i)->WORD == "#")
    {
        for (int j = i + 1; j < Input.size(); j++)
        {
            if (Input.at(j)->is(_END) || Input.at(j)->WORD == "\n")
            {
                Input.erase(Input.begin() + j);
                break;
            }
            else
            {
                Input.erase(Input.begin() + j);
                j--;
            }
        }
        Input.erase(Input.begin() + i);
    }
}

void Parser::Factory()
{
    for (int i = 0; i < Input.size(); i++)
    {
        Pattern_Comments(i);
    }
    for (int i = 0; i < Input.size(); i++)
    {
        Pattern_Init_String(i);
    }
    for (int i = 0; i < Input.size(); i++)
    {
        Pattern_Include(i);
    }
    for (int i = 0; i < Input.size(); i++)
    {
        Pattern_Init_Array(i);
    }
    for (int i = 0; i < Input.size(); i++)
    {
        //for Inits;
        Pattern_Init_New(i);
        Pattern_Init_Type(i);
        Pattern_Init_Call_Func(i);
        Pattern_Init_Variable(i);
        Pattern_Init_Operators(i);
        Pattern_Init_Condition(i);
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
        Pattern_Condition(i);
    }
    vector<Token*> *T;
    Give_Output(T);
    for (int i = 0; i < T->size(); i++)
    {
        Pattern_Array(i);
    }
    
}