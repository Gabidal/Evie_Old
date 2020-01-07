#ifndef _EMULATOR_H_
#define _EMULATOR_H_
#include <vector>
#include "../Back/Token.h"
#include "../Back/Registers.h"
using namespace std;

class Emulator
{
public:
	//STACK
	vector<int> Stack;
	//Cycles
	int Cycles = 0;
	//Operations
	vector<Token*> Input;
	//start point
	int Start = 0;
	//Math
	int Layer = 0;
	Token* Cheat;
	Token* Dest;
	Token* Source;
	//Registers
	int Register_Turn = 0;
	
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
	void Next_Op_Picker(Token& T);
	bool Unlock_Requem(Token &T);
	Register* Optimized_Register_Giver(Token* T);

	int Simulate_Equ(Token* Dest, Token* Source);
	int Simulate_Add(Token* Dest, Token* Source, Token* Cheat);
	int Simulate_Sub(Token* Dest, Token* Source, Token* Cheat);
	int Simulate_Mul(Token* Dest, Token* Source, Token* Cheat);
	int Simulate_Div(Token* Dest, Token* Source, Token* Cheat);
	Emulator& operator=(const Emulator& other)
	{
		//Stack
		Stack = other.Stack;
		//math
		Layer = other.Layer;
		//cpu
		Register_Turn = other.Register_Turn;
	}
private:

};


#endif