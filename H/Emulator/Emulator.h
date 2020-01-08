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
	int Original_Size = 0;
	//Cycles
	int Cycles = 0;
	//Operations
	vector<Token*> Input;
	//Math
	int Layer = 0;
	Token* Cheat;
	Token* Dest;
	Token* Source;
	vector<Token*> Log;
	bool Deep_Math_Done = false;
	bool Deep_Math = false;
	bool Double_Callation = false;
	//Registers
	int Register_Turn = 0;

	
	Emulator(vector<Token*>& In)
	{
		Input = In;
	}
	~Emulator()
	{
	}
	int Factory();
	void Start_Simulation(int start);
	void Branch_Picker(int i);
	void Next_Op_Picker(Token& T);
	bool Unlock_Requem(Token &T);
	Register* Optimized_Register_Giver(Token* T);
	int Get_Value_Of(Token* T);
	void Add_To_Log(Token* T);
	Token* Find_From_Log(Token* T);
	void Sync_Parameters(vector<Token*> &Parameters);

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
		Deep_Math_Done = other.Deep_Math_Done;
		Deep_Math = other.Deep_Math;
		//cpu
		Register_Turn = other.Register_Turn;
	}
private:

};


#endif