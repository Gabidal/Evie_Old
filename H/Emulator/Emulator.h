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
	Token* Handle = nullptr;
	void Factory();
	Emulator(string &in) : Output(in){}
	~Emulator(){}
private:

};


#endif