#ifndef _EMULATOR_H_
#define _EMULATOR_H_
#include <vector>
#include "../OpC/IR.h"
#include "../Back/Back.h"
using namespace std;

class Emulator
{
public:
	vector<IR*> Input;
	vector<string> Branching_Label;
	bool _NEED_FOR_FPU = false;



	void Long_Operation_Allocator(int &i);
	void Label_Recorder(int i);
	void Frame_Handler(int i);
	void FPU_Choser(int i);
	void Math(int i);
	Emulator()
	{
	}
	~Emulator(){}


	Emulator& operator=(const Emulator& other)
	{
		Branching_Label = other.Branching_Label;
		_NEED_FOR_FPU = other._NEED_FOR_FPU;
	}
private:

};


#endif