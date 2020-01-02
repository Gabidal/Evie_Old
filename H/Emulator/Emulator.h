#ifndef _EMULATOR_H_
#define _EMULATOR_H_
#include <vector>
#include "../Back/Token.h"
using namespace std;

class Emulator
{
public:
	//CPU
	int &_EAX;
	int &_EBX;
	int &_ECX;
	int &_EDX;
	int &_EDI;
	int &_ESI;
	int &_EBP;
	int &_ESP;
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
	Emulator(vector<Token*>& In, int start, int a, int b, int c, int d, int i, int s, int p, int e) : _EAX(a), _EBX(b), _ECX(c), _EDX(d), _EDI(i), _ESI(s), _EBP(p), _ESP(e)
	{
		Input = In;
		Start = start;
	}
	~Emulator()
	{
	}
	void Factory();
	void Branch_Picker(int i);
	void Next_Op_Picker(Token& T);
	bool Unlock_Requem(Token &T);
	void Simulate_Math(Token& T);
	Emulator& operator=(const Emulator& other)
	{
		//give the registers
		_EAX = other._EAX;
		_EBX = other._EBX;
		_ECX = other._ECX;
		_EDX = other._ECX;
		_EDI = other._EDI;
		_ESI = other._ESI;
		_ESP = other._ESP;
		_EBP = other._EBP;
		//Stack
		Stack = other.Stack;
	}
private:

};


#endif