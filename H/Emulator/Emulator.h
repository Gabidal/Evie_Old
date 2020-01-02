#ifndef _EMULATOR_H_
#define _EMULATOR_H_
#include <vector>
#include "../Back/Token.h"
using namespace std;

class Emulator
{
public:
	//CPU
	int _EAX = 0;
	int _EBX = 0;
	int _ECX = 0;
	int _EDX = 0;
	int _EDI = 0;
	int _ESI = 0;
	int _EBP = 0;
	int _ESP = 0;
	//STACK
	vector<int> Stack;
	//Cycles
	int Cycles = 0;
	//Operations
	vector<Token*> Input;
	//start point
	int Start = 0;
	//Current
	Token* Current;
	//Next
	Token* Next;
	Emulator(vector<Token*>& In, int start)
	{
		Input = In;
		Start = start;
	}
	~Emulator()
	{
	}
	void Factory();
	void Branch_Picker(int i);
	void Next_Op_Picker(Token &T);
	void Unlock_Requem();
private:

};


#endif