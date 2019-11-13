#ifndef _BACK_H_
#define _BACK_H_
#include "Token.h"
#include <vector>
#include <string>
#include "Register.h"
#include "Assembly_Definitions.h"

class Back
{
private:
	 // nej
    // Mörkönenä was here. 20:09 thu 7.11.19;
public:
    string &Output;
    vector<Token*> Input;
    Token *Dest;
    Token *Source;

    void Handle_Usation(int &i);
    void Handle_Operators(int i);
    void Handle_Variables(int i);
    void Handle_Function_Init(int i);
    void Handle_Type_Init(int i);
    void Handle_Call_Function(int i);
    void Handle_Arrays(int i);
    void Handle_Fetching(int i);

    void Factory();
    Back &operator=(const Back& name);
    string Get_Output() { return Output;}
    Back(vector<Token*> In, string &out) : Input(In), Output(out)
    {
        
    }
    
    ~Back()
    {
        
    }
};



#endif