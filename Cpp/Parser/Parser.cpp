#include "../../H/Parser/Parser.h"

int ID = 0;

void Parser::Pattern_Init_Sys_Functions()
{
    Token *Malloc = new Token(Assembly, Output);
    Malloc->Flags |= Function;
    Malloc->ParameterCount = 1;
    Malloc->Flags |= Returning;
    Malloc->Name = "Malloc";

    Token *Print = new Token(Assembly, Output);
    Print->Flags |= Function;
    Print->ParameterCount = 2;
    Print->Name = "raw_print";
    
    Token *In = new Token(Assembly, Output);
    In->Flags |= Function;
    In->ParameterCount = 2;
    In->Flags |= Returning;
    In->Name = "raw_in";

    Output->push_back(Malloc);
    Output->push_back(Print);
    Output->push_back(In);
}

void Parser::Pattern_Init_Variable(int i)
{
    //((var) (a) (:) (b) (= 123))
    if (Input.at(i)->is(_KEYWORD) && Input.at(i+1)->is(_TEXT) && Input.at(i)->WORD == "var" && Input.at(i)->UsedToken == false)
    {
        //create new variable;
        Token *Var = new Token(Assembly, Output);
        Var->Flags |= Variable;
        Var->Name = Input.at(i+1)->WORD;
        Var->Size = 4;
        if (InsideOfType && InsideOfFunction != true)
        {
            Var->Flags |= Member;
            ParentType->addChild(Var, false);
        }
        else if (InsideOfFunction)
        {
            Var->Flags |= Private;
            ParentFunc->addChild(Var, true);
        }
        else
        {
            Var->Flags |= Public;
            Output->push_back(Var);
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

	Give_Context(T);
    
    if (Input.at(i)->is(_TEXT) && (Find(*T, Input.at(i)->WORD, Variable | Ptr) != nullptr))
    {
        Token *r = Find(*T, Input.at(i)->WORD, Variable | Ptr);
        Token *t = new Token(Assembly, *&Output);
        *t = *r;
        t->Size = 4;
        if (InsideOfFunction)
        {
            t->Flags |= Private;
			t->ParentFunc = ParentFunc;
		}
		else if (InsideOfType)
		{
			t->Flags |= Member;
			t->ParentType = ParentType;
		}
		else
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
            Token *off = new Token(Assembly, Output);
            off = p.Direct.at(0);
            t->Flags |= Array;
            t->Offsetter = off;
        }

        if (Input.at(i)->_type && (Find(*Output, Input.at(i)->Fetcher, NotOriginal) != nullptr))
        {
            //do fetching;
            t->Fetcher = Find(*Output, Input.at(i)->Fetcher, NotOriginal);
        }

        if (Input.at(i)->_ptr)
        {
            t->Flags |= Ptr;
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
        Token *n = new Token(Assembly, Output);
        n->Flags |= Number;
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
    if (Input.at(i)->is(_OPERATOR) && (Input.at(i)->Tokens.size() > 0) && (Input.at(i)->UsedToken == true) && Input.at(i)->WORD != "&")
    {
        Token *OP = new Token(Assembly, Output);
        OP->Flags |= OPERATOR;
        OP->Name = Input.at(i)->WORD;

        Parser p = *this;
        p.Input = Input.at(i)->Tokens;
        p.Started = Input.at(i)->Tokens.size();
        p.Priority = true;
        
        p.Factory();
        //check this also in debugging!!!
        Token *A = new Token(Assembly, Output);
        Token *B = new Token(Assembly, Output);
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
            A = p.Output->at(p.Output->size() - 2);
            B = p.Output->at(p.Output->size() - 1);
            p.Output->erase(p.Output->begin() + p.Output->size() - 1);
            p.Output->erase(p.Output->begin() + p.Output->size() - 1);
        }
        
        OP->Parameters.push_back(A);
        OP->Childs.push_back(B);

        vector<Token*> *T;
        Give_Output(T);
        T->push_back(OP);
    }
}

void Parser::Pattern_Init_Array(int &i)
{
    // a : a
    if (Input.at(i)->is(_OPERATOR) && Input.at(i)->WORD == ":")
    { 
        int s = Input.size() - 1;
        if ((s < (i+2)) != true)
        {
            i = i + 2;
            Pattern_Init_Type(i);
        }
        if (((i-2) < 0) != true)
        {
            i = i - 2;
            Pattern_Init_Type(i);
        }
        Pattern_Init_Call_Func(i + 1);
        Pattern_Init_Call_Func(i - 1);
        Input.at(i-1)->_array = true;
        Input.at(i-1)->Offsetter = Input.at(i+1);
        Input.erase(Input.begin() + i); // :
        Input.erase(Input.begin() + i); // offsetter
    }
}

void Parser::Pattern_Init_Locator(int &i)
{
    if (Input.at(i)->WORD == "&")
    {
        Input.at(i+1)->_ptr = true;
        Input.erase(Input.begin() + i);
        i--;
    }
}

void Parser::Pattern_Function(int i)
{
    //func banana(a, &b, c, &d)
    if (Input.at(i)->is(_KEYWORD) && Input.at(i)->WORD == "func")
    {
        //make new Function;
        Token *Name = new Token(Assembly, Output);
        Name->Flags |= Function;
        Name->Name = Input.at(i+1)->WORD;
        if (InsideOfType)
        {
            Name->ParentType = ParentType;
            Name->Flags |= Member;
        }
        
        //make the parameters;
        for (int j = 0; j < int(Input.at(i+2)->Tokens.size()); j++)
        {
            if (Input.at(i+2)->Tokens.at(j)->is(_TEXT))
            {
                Token *var = new Token(Assembly, Output);
				if ((j > 0) && (Input.at(i + 2)->Tokens.at(j-1)->WORD == "&"))
				{
					var->Flags |= Ptr;
					var->Flags |= Parameter;
					var->Size = 4;
					var->Name = Input.at(i + 2)->Tokens.at(j)->WORD;
				}
				else
				{
					var->Flags |= Parameter;
					var->Flags |= Variable;
					var->Size = 4;
					var->Name = Input.at(i + 2)->Tokens.at(j)->WORD;
				}
				var->ParentFunc = Name;
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
        Token *Type = new Token(Assembly, Output);
        Type->Flags |= TypE;
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
        Token *condition = new Token(Assembly, Output);

        if (Input.at(i)->WORD != "else")
        {
            Parser p = *this;
            p.Input = Input.at(i)->Tokens;
            p.GetDirect = true;
			p.Priority = true;
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
    int a = Input.size() - 1;
    if (((a - 3) < 0) || (i - 3) < 0)
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
        parser.Started = Output->size();
        parser.Factory();
        ParentFunc->Flags |= PARENT;
        ParentFunc = nullptr;
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
        parser.Started = Output->size();
        parser.Factory();
        ParentType->Flags |= PARENT;
        ParentType = nullptr;
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
        parser.Started = Output->size();
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
        parser.Started = Output->size();
        parser.Factory();
        ParentCondition->Flags |= PARENT;
        ParentCondition->Flags |= int(Successour);
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
        parser.Started = Output->size();
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
    if (Input.at(i)->is(_OPERATOR) && Input.at(i)->UsedToken != true && (Input.at(i)->WORD != "?") && (Input.at(i)->WORD != ","))
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
    int s = Input.size();
    if ((s - 1) < i)
    {
        return;
    }
    
    if ((Input.at(i)->_evaluate == false) && (Input.at(i)->_func == false) && Input.at(i)->is(_PAREHTHESIS) && Input.at(i-1)->is(_TEXT) && (Input.at(i-2)->WORD != "func"))
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
        Token *func = new Token(Assembly, Output);
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

        func->ParentFunc = ParentFunc;
        func->ParentType = ParentType;
        
        Give_Input(t);
        if (Find(func->Name, Function, *t) != -1)
        {
            int j = Find(func->Name, Function, *t);
            t->at(j)->CallationAmount++;
            t->at(j)->Callations->push_back(func);
			func->daddy_Func = t->at(j);
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
			for (int k = 0; k < int(p.Direct.size()); k++)
			{
				p.Direct.at(k)->Outside_Of_Parameters = true;
				func->addParameter(p.Direct.at(k));
			}
        }
        Give_Output(t);
        t->push_back(func);
    }
    
}

void Parser::Pattern_Init_Type(int &i)
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
        i -= 1;
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
        Token *n = new Token(Assembly, Output);
        n->Flags |= __NEW;
        n->Name = "new";

        // the template type classes are always made global
        vector<Token*> *T;
        Give_Output(T);
        int j = Find(Input.at(i)->Tokens.at(0)->WORD, TypE, *Output);
        Token *t = new Token(Assembly, Output);
        t->Childs = Output->at(j)->Childs;
        t->Name = Input.at(i)->Tokens.at(1)->WORD;
        t->Origin = Output->at(j);
        t->Flags |= NotOriginal;
        t->Flags |= Ptr;
        t->Flags |= Variable;
        for (int k = 0; k < int(t->Childs.size()); k++)
        {
            if (t->Childs.at(k)->Size > 0)
            {
                t->Size += t->Childs.at(k)->Size;
            }
        }
        Give_Output(T);
        T->push_back(n);
        if (InsideOfType && (InsideOfFunction != true))
        {
            t->Flags |= Member;
            ParentType->addChild(t, false);
        }
        else if (InsideOfFunction)
        {
            t->Flags |= Private;
            ParentFunc->addChild(t, true);
        }
        else
        {
            Give_Output(T);
            T->push_back(t);
        }
        Output->at(j)->Callations->push_back(t);
        j = Find("Malloc", Function, *Output);
        Output->at(j)->Callations->push_back(t);
        Output->at(j)->CallationAmount++;
    }
}

void Parser::Pattern_Init_Evaluation(int i)
{
    if ((int(Input.size()) - 1) < i)
    {
        return;
    }
    if (Input.at(i)->_func == false && Input.at(i)->is(_PAREHTHESIS) && Input.at(i-1)->is(_OPERATOR) && Input.at(i-1)->WORD == "?")
    {
        Input.at(i-1)->Tokens = Input.at(i)->Tokens;
        Input.at(i-1)->_evaluate = true;
        Input.at(i-1)->Flags |= _PAREHTHESIS;
        Input.erase(Input.begin() + i);
    }
}

void Parser::Pattern_Evaluation(int i)
{
    //?(a : b * 4)
    if (Input.at(i)->_evaluate)
    {
        Parser p = *this;
        p.Input = Input.at(i)->Tokens;
        p.GetDirect = true;
        p.Factory();

        Token *E = new Token(Assembly, Output);
        E->Childs = p.Direct;
        E->Flags |= Evaluation;
        E->Name = "?";
        
        vector<Token*> *T;
        Give_Output(T);
        T->push_back(E);
    }
}

void Parser::Pattern_Return(int i)
{
    //return <a : b>
    if (Input.at(i)->is(_KEYWORD) && Input.at(i)->WORD == "return")
    {
        Token *r = new Token(Assembly, Output);
        Parser p = *this;
        p.Priority = true;
        p.Input.clear();
        p.Input.push_back(Input.at(i+1));
        p.GetDirect = true;
        p.Factory();
        r->Name = "return";
        r->Flags |= Returning;
        r->Childs = p.Direct;
        vector<Token*> *T;
        Give_Output(T);
        T->push_back(r);
		if (ParentFunc != nullptr)
			ParentFunc->Flags |= Returning;
		else
			ParentType->Flags |= Returning;
        Input.erase(Input.begin() + i+1);
    }
}

void Parser::Clean_Cilds()
{
    for (int j = 0; j < int(ParentFunc->Parameters.size()); j++)
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
        Token *t = new Token(Assembly, Output);
        if (j == -1)
        {
            return nullptr;
        }
        t = T->at(j);
        return t;
    }
    return nullptr;
}

Token *Parser::Find(vector<Token*> T, string name, int flag)
{
    for (int i = 0; i < int(T.size()); i++)
    {
        if (T.at(i)->Name == name && T.at(i)->Any(flag))
        {
            return T.at(i);
        }
        if (Find(T.at(i)->Childs, name, flag) != nullptr)
        {
            return Find(T.at(i)->Childs, name, flag);
        }
        if (Find(T.at(i)->Parameters, name, flag) != nullptr)
        {
            return Find(T.at(i)->Parameters, name, flag);
        }
    }
    return nullptr;
}

int Parser::Find(string name, int flag, vector<Token*> list)
{
    for (int i = 0; i < int(list.size()); i++)
    {
        if (list.at(i)->Name == name && list.at(i)->is(flag))
        {
            return i;
        }
        else if (list.at(i)->Childs.size() > 0)
        {
            if (Find(name, flag, list.at(i)->Childs) != -1)
            {
                return Find(name, flag, list.at(i)->Childs);
            }
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
            T->insert(T->end(), ParentFunc->Parameters.begin(), ParentFunc->Parameters.end());
        }
        T->insert(T->end(), ParentFunc->Childs.begin(), ParentFunc->Childs.end());
    }
    if (InsideOfType)
    {
        T->insert(T->end(), ParentType->Childs.begin(), ParentType->Childs.end());
    }
    T->insert(T->end(), Output->begin(), Output->end());
}

void Parser::Give_Context(vector<Token*>*& T)
{
	T = new vector<Token*>;
	if (InsideOfCondition)
	{
		T->insert(T->end(), ParentCondition->Parameters.begin(), ParentCondition->Parameters.end());
		T->insert(T->end(), ParentCondition->Childs.begin(), ParentCondition->Childs.end());
	}
	if (InsideOfFunction)
	{
		T->insert(T->end(), ParentFunc->Parameters.begin(), ParentFunc->Parameters.end());
		T->insert(T->end(), ParentFunc->Childs.begin(), ParentFunc->Childs.end());
	}
	if (InsideOfType)
	{
		T->insert(T->end(), ParentType->Childs.begin(), ParentType->Childs.end());
	}
	else
	{
		T = Output;
	}
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
        T = Output;
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
        for (int j = i + 1; j < int(Input.size()); j++)
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
        string tmp = "C:\\Users\\Quanf\\source\\repos\\GAS\\GAS\\IO\\";
        string tmp2 = (tmp + Input.at(i + 1)->WORD).c_str();
        Input.erase(Input.begin() + i);
        Input.erase(Input.begin() + i);
        Definer *d = new Definer();
        d->OpenFile(tmp2.c_str());
        Parser p(d->output, Assembly);
		*p.Output = *Output;
		int tmpsize = p.Output->size();
        p.Factory();
        
        for (int j = tmpsize; j < int(p.Output->size()); j++)
            Output->push_back(p.Output->at(j));
        
    }
}

void Parser::Pattern_Comments(int i)
{
    if (Input.at(i)->is(_COMMENT) || Input.at(i)->WORD == "#")
    {
        for (int j = i + 1; j < int(Input.size()); j++)
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
    /*for (int i = 0; i < int(Input.size()); i++)
    {
        Pattern_Comments(i);
    }*/
    for (int i = 0; i < int(Input.size()); i++)
    {
        Pattern_Init_String(i);
    }
    for (int i = 0; i < int(Input.size()); i++)
    {
        Pattern_Include(i);
    }
    for (int i = 0; i < int(Input.size()); i++)
    {
        Pattern_Init_Type(i);
    }
    for (int i = 0; i < int(Input.size()); i++)
    {
        Pattern_Init_Array(i);
    }
    for (int i = 0; i < int(Input.size()); i++)
    {
        Pattern_Init_Evaluation(i);
    }
    for (int i = 0; i < int(Input.size()); i++)
    {
        Pattern_Init_Locator(i);
    }
    for (int i = 0; i < int(Input.size()); i++)
    {
        //for Inits;
        Pattern_Init_New(i);
        Pattern_Init_Call_Func(i);
        Pattern_Init_Variable(i);
        Pattern_Init_Operators(i);
        Pattern_Init_Condition(i);
    }
    for (int i = 0; i < int(Input.size()); i++)
    {
        //for Makers;
        Pattern_Evaluation(i);
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
    for (int i = 0; i < int(T->size()); i++)
    {
        Pattern_Array(i);
    }
    
}