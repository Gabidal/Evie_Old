#ifndef _BACKEND_H_
#define _BACKEND_H_
#include "x86.h"
#include "../UI/Usr.h"
#include "../Nodes/IR.h"
#include "../Nodes/Token.h"
#include "../../H/BackEnd/Selector.h"


#include <vector>
#include <string>

using namespace std;

class BackEnd {
private:
	string Seperator = "";
	string Register_Pre_Fix = "";
	string Number_Pre_Fix = "";
	string Label_Post_Fix = "";

	vector<IR*> Opcodes;

	vector<IR*> Input;
	string* Output;

	void Init();
	void Factory();
	void Operator_Builder(IR* i);
	void Label_Builder(IR* i);
	void End_Of_Function_Builder(IR* i);
	void Call_Builder(IR* i);
	void Global_Builder(IR* i);

	string Token_Builder(Token* t, bool Inside_Content = false);
public:
	BackEnd(vector<IR*> in) : Input(in) {
		Output = new string("");
		Init();
		Factory();
	}
	BackEnd(vector<IR*> in, string& out) : Input(in), Output(&out) {
		Init();
		Factory();
	}
};

#endif