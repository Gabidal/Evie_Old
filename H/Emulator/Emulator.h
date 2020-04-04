#ifndef _EMULATOR_H_
#define _EMULATOR_H_
#include <vector>
#include "../OpC/IR.h"
#include "../Back/Back.h"
#include "../Back/Token.h"
#include "../Interpreter/Modder.h"
#include <map>
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
	map<Token*, Token*> Register_Lock;

	Token* Get_Info(Token* t);
	void Long_Operation_Allocator(int &i);
	void Label_Recorder(int i);
	void Register_Chooser(Token* t);
	void Register_Loader(Token& t, int i);
	void Frame_Handler(int i);
	void FPU_Choser(int i);
	void Child(int i);
	void Use_Assembly(int i);
	void Factory();
	void Pattern_User(int i);
	void Load_UID(int i);
	Emulator(string &in) : Output(in)
	{
	}
	~Emulator(){}
private:

};


#endif