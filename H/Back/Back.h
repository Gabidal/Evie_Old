#ifndef _BACK_H_
#define _BACK_H_
#include "Token.h"
#include <vector>
#include <string>
#include "Assembly_Definitions.h"
#include "StackFrame.h"
#include <algorithm>
#include "../Linux/Linux.h"
extern int SYNTAX;

class Back
{
private:
	 // nej
    // Mörkönenä was here. 20:09 thu 7.11.19;
public:
    int IS_PUBLIC = 0;
    string &Output;
	string Strings = "";
    vector<Token*> Input;
    Token *Dest = nullptr;
    Token *Source = nullptr;
    Token *Cheat = nullptr;
    bool Priority_For_Parametering = false;
    bool Get_Direct = false;
    int Layer = 0;
    bool Deep_Math = false;
    bool Deep_Math_Done = false;
    bool Double_Callation = false;
    int &Syntax = SYNTAX;

    void Handle_Operators(int i);
    void Handle_Variables(int i);
    void Handle_Function_Init(int i);
    void Handle_Type_Init(int i);
    void Handle_Call_Function(int i);
    void Handle_Arrays(int i);
    void Handle_Conditions(int i);
    void Handle_Jumps(Token *condition, Token owner);
    void Handle_Returning(int i);
    void Handle_New(int i);
    void Handle_Variable_Initalization(int i);
	void Handle_String_Initalization(vector<Token *> *&T);
	void Set_All_References(string name, int flags, vector<Token*>& T);
    string END(int i);
    string SX();

    void Factory();
	void Factory_Variables();
    int Find(string name, int flag, vector<Token*> list);
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