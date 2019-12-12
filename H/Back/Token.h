#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>
#include <vector>

using namespace std;

//creators
#define _NULL_ (1<<0)
#define Public (1<<1)
#define Member (1<<2)
#define Used (1<<3)
#define Real (1<<4) 
#define Function (1<<6)
#define Macro (1<<7)
#define TypE (1<<8)
#define Define (1<<9)
//Variables
#define Number (1<<10)
#define Ptr (1<<11)
#define Variable (1<<12)
#define Array (1<<13)
#define Equ (1<<14)
//Logical
#define If (1<<15)
#define Else (1<<16)
#define While (1<<17)
#define Returning (1<<18)
//Arithmetic
#define OPERATOR (1<<19)

//Personan
#define Loader (1<<20)
#define Storer (1<<21)
#define Evaluation (1<<22)
#define NotOriginal (1<<23)
#define Parameter (1<<24)
#define Private (1<<25)
#define This (1<<26)
#define PARENT (1<<27)
#define Call (1<<28)
#define __NEW (1<<29)
#define HAS_FETCHER (1<<30)
#define Successour (1<<31)

class Register;

class Token
{
  public:
    int Flags = 0;
    int Size = 0;
    int Value = 0;
    int StackOffset = 4;
    int ParameterCount = 0;
    int AddedOffset = 4;
    int ParameterOffset = 0;
    bool _INITTED = false;
    int ID = 0;
    Token *Offsetter = nullptr;
    Token *ParentType = nullptr;
    Token *ParentFunc = nullptr;
    vector<Token*> SuccessorToken;
    Token *Former = nullptr;
    vector<Token*> Parameters;
    vector<Token*> Childs;
    string Name = "";
    Register *Reg = 0;
    string &output;
	vector<Token*> *Input;
    Token(string &out, vector<Token*> *T) : output(out), Input(T){}
    Token &operator=(const Token& name);

    bool is(int flag);
    bool Any(int flags);
    string getFullName();
    Register *getNewRegister();
    Register *getReg();
    //var
    string InitVariable();
    string MOVE(Token *Source);
    string SUM(Token *Source, Token *Dest);
    string SUBSTRACT(Token *Source, Token* Dest);
    string MULTIPLY(Token *Source);
    string DIVIDE(Token *Source);
    string COMPARE(Token *Source);
    string MOVEINSTACK();
    string GetAddress();
    //func
    vector<Token*> *Callations = new vector<Token*>;
    int CallationAmount = 0;
	Token* daddy_Func = nullptr;
    void addChild(Token *t, bool func);
    void addParameter(Token *Param);
    void InitFunction();
    void CallFunc(Token *Fetcher);
    //type
    Token *Origin = nullptr;
    //Fetcher
    Token *Fetcher = nullptr;
    //ptr
    void PTRING(Token *&T);
	bool Outside_Of_Parameters = false;
	//optimization
	bool fixed_Location = false;
	//array
	bool ARRAY = false;
	Token* repz = nullptr;
	//tmp
	Token* tmp = nullptr;
};

class Register
{
public:
    bool TaskForReturning = false;
    bool TaskForTypeAddress = false;
    bool TaskForMovingParameter = false;
    string Name = "";
    int Value = 0;
    Token *Base;
    Token *Current;
    Register(string name)
    {
        Name = name;
    }
    void Link(Token *Requester);
	void Apply(Token* Requester, vector<Token*> *T);
};
#endif

