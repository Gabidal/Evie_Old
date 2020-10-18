#ifndef _SELECTOR_H_
#define _SELECTOR_H_
#include <vector>
#include <string>

#include "../Nodes/IR.h"
#include "../Nodes/Token.h"
#include "../BackEnd/x86.h"

using namespace std;

class Register_Descriptor {
public:
	//int First_Usage_Index = 0;
	int Last_Usage_Index = 0;

	string User = "";

	Register_Descriptor(int i, string usr) : Last_Usage_Index(i), User(usr){}
};

class Selector {
private:
	void Init();
	vector<pair<Register_Descriptor*, Token*>> Registers;
	vector<pair<Register_Descriptor*, Token*>> Parameter_Registers;


public:
	Token* Get_New_Reg(vector<IR*> source, int i, Token* t);
};

#endif