#ifndef _PARSER_H_
#define _PARSER_H_
#include <vector>
#include <string>
#include "../Lexer/Component.h"
#include "../Back/Token.h"
#include "../Lexer/Lexer.h"
#include <algorithm>
#include <iostream>
using namespace std;

class Parser
{
public:

    int Space_Reservation = 0;
	//string Working_Dir = "";
    string Context = "Global Scope";
    vector<Component> Input;
    vector<Token*> Output;
    vector<Token*> Defined_Keywords;
    void Include_Files(int i);
    void Connect_Array(int i);
    void Connect_Address(int i);
    void Init_Definition(int &i);
    vector<string> Collect_All_Inherited_Types(int i);
    string Get_Size(int i, Token* t);
    void Init_Operator(int i);
    void Reserve_Operator_Tokens(int i);
    void Reserve_Function_Parameters(int i);
    void Patternize_Operations(int& i, string f);
    void Do_In_Order();
    void Init_Parenthesis(int i);
    void Init_Conditions(int i);
    void Type_Definition(int i);
    void Set_Right_Stack_Offset(Token* t);
    void Set_Right_Flag_Info(Token* t);
    string Defined(string name);
    vector<string> Get_Type(string name);
    int Count_Familiar_Tokens(int F, int i);
    void Init_Variable(int i);
    void Check_For_Correlation(int i);
    void Check_For_Correlation_Link(int i);
    void Check_For_Inter(int i);
    void Factory();
    void Append(vector<Token*>* Dest, vector<Token*> Source);
    //update the line number by detecting "\n"
    void Update_Line_Number(Component& t);
    //the Token.h constructor get the global line_number
    string Update_Dir(string File_Name);
    Parser &operator=(const Parser& other)
    {
        //Working_Dir = other.Working_Dir;
        //Input = other.Input;
        //Output = other.Output;
        Defined_Keywords = other.Defined_Keywords;
        return *this;
    }
    ~Parser()
    {
    }
};

#endif