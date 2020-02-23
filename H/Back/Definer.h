#ifndef _DEFINER_H_
#define _DEFINER_H_
#include "Token.h"
#include <vector>
#include <string>

            //_// This is where we try to define what are the types defined in source code.
            //_// And make them into reasonable tokens.

class Definer
{
private:
	 // nej
    // Mörkönenä was here. 20:09 thu 7.11.19;
public:
    vector<Token*> Input_Of_Tokens;
    vector<Token*> Defined_Types;
    vector<Token*> Output;
    int Get_Location_Of_Type_Constructor(string type);
    int Get_Definition_Setting(Token* t, string f);
    bool Has(Token* t, string s);
    void Factory();
    Definer()
    {
    }
    
    ~Definer(){}
};



#endif