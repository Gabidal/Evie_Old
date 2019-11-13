#ifndef _BACK_H_
#define _BACK_H_
#include "Token.h"
#include <vector>
#include <string>
#include "Register.h"

class Back
{
private:
	 // nej
    // Mörkönenä was here. 20:09 thu 7.11.19;
public:
    string &Output;
    vector<Token*> Input;
    void Factory();
    string Get_Output() { return Output;}
    Back(vector<Token*> In, string &out) : Input(In), Output(out)
    {
        
    }
    
    ~Back()
    {
        
    }
};



#endif