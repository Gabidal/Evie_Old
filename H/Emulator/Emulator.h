#ifndef _EMULATOR_H_
#define _EMULATOR_H_
#include <vector>
#include "../OpC/IR.h"
#include "../Back/Back.h"
#include "../Back/Token.h"
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
	Token* Handle = nullptr;



	void Long_Operation_Allocator(IR* t, int i);
	void Label_Recorder(IR* t);
	void Register_Chooser(Token* t);
	void Frame_Handler(IR* t);
	void FPU_Choser(IR *t);
	void Child(IR* t);
	void Use_Assembly(IR* t);
	void Factory();
	Emulator(string &in) : Output(in)
	{
	}
	~Emulator(){}


	Emulator& operator=(const Emulator& other)
	{
		Branching_Label = other.Branching_Label;
		_NEED_FOR_FPU = other._NEED_FOR_FPU;
		Output = other.Output;
	}
private:

};


#endif