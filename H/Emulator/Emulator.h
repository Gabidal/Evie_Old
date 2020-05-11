#ifndef _EMULATOR_H_
#define _EMULATOR_H_
#include <vector>
#include "../OpC/IR.h"
#include "../Back/Back.h"
#include "../Back/Token.h"
#include "../Interpreter/Modder.h"
using namespace std;

class Emulator
{
public:
	string& Output;
	vector<IR*> Input;
	vector<string> Branching_Label;
	bool _NEED_FOR_FPU = false;
	bool _IN_PROGRESS = false;
	bool _NEED_FOR_PARAMETERING = false;
	Token* Handle = nullptr;

	Token* Get_Info(Token* t);
	void Long_Operation_Allocator(int &i);
	void Label_Recorder(int i);
	void Frame_Handler(int i);
	void FPU_Choser(int i);
	void Child(int i);
	void Use_Assembly(int i);
	void Factory();
	void Pattern_User(int i);
	void Load_UID(int i);
	void Skip_Chained_Registers(Token* reg);
	void Link_Cache_User(Token* t);
	void Optimized_Register_Linking_Between_Different_Parameters(Token* o);
	void Register_Chooser(Token* t, int i);
	void Register_Loader(Token& t, int i);
	void Disconnect_Register(vector<Token*> t);
	void Update_Syntax_Tabs();
	void Set_Syntax_Tabs(IR* t);
	Emulator(string &in) : Output(in)
	{
	}
	~Emulator(){}
private:

};


#endif