#include "../../H/Back/Back.h"

void Back::Handle_Usation(int &i)
{
    if (Input.at(i)->is(Used) == false)
    {
        i++;
    }
}

void Back::Handle_Operators(int i)
{
    if (Input.at(i)->is(OPERATOR))
    {
        if (Input.at(i)->Parameters.at(0)->is(Variable))
        {
            Dest = Input.at(i)->Parameters.at(0);
        }
        else
        {
            Back b = *this;
            b.Input = Input.at(i)->Parameters;
            b.Factory();
            this->Dest = b.Dest;
        }
        if (Input.at(i)->Childs.at(0)->is(Variable) || Input.at(i)->Childs.at(0)->is(Number))
        {
            Source = Input.at(i)->Childs.at(0);
        }
        else
        {
            Back b = *this;
            b.Input = Input.at(i)->Parameters;
            b.Factory();
            this->Source = b.Source;
        }
        if (Input.at(i)->Name == "+")
        {
            Dest->SUM(Source);
        }
        else if (Input.at(i)->Name == "-")
        {
            Dest->SUBSTRACT(Source);
        }
        else if (Input.at(i)->Name == "*")
        {
            Dest->MULTIPLY(Source);
        }
        else if (Input.at(i)->Name == "/")
        {
            Dest->DIVIDE(Source);
        }
        else if (Input.at(i)->Name == "=")
        {
            Dest->MOVE(Source);
        }
    }
}

void Back::Handle_Variables(int i)
{
    if (Input.at(i)->is(Variable))
    {
        if (Priority_For_Parametering)
        {
            PUSH(Input.at(i)->InitVariable());
        }
    }
}

void Back::Handle_Function_Init(int i)
{
    if (Input.at(i)->is(Function))
    {
        Input.at(i)->InitFunction();
        Back b = *this;
        b.Input = Input.at(i)->Childs;
        StackFrame stack(Output);
        b.Factory();
    }
}

void Back::Handle_Type_Init(int i)
{
    if (Input.at(i)->is(TypE))
    {
        Back b = *this;
        b.Input = Input.at(i)->Childs;
        b.Factory();
    }
}

void Back::Handle_Call_Function(int i)
{
    if (Input.at(i)->is(Function) && Input.at(i)->is(Call))
    {
        if (Input.at(i)->Parameters.size() > 0)
        {
            Back b = *this;
            b.Input = Input.at(i)->Parameters;
            b.Priority_For_Parametering = true;
            b.Factory();
        }
    }
}

void Back::Handle_Arrays(int i)
{

}

void Back::Factory()
{
    for (int i = 0; i < Input.size(); i++)
    {
        /*if (Input.at(i)->is(Used) == false)
        {
            continue;
        }*/
        //Handle_Usation(i);
        Handle_Type_Init(i);
        Handle_Function_Init(i);
        Handle_Call_Function(i);
        Handle_Operators(i);
        Handle_Arrays(i);
        Handle_Variables(i);
    }
}


Back &Back::operator=(const Back& name)
{
    Output = name.Output;
    Input = name.Input;
    Dest = name.Dest;
    Source = name.Source;
    return *this;
}