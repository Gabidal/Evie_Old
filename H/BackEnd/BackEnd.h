#ifndef _BACKEND_H_
#define _BACKEND_H_
#include "x86.h"
#include "../UI/Usr.h"
#include "../Nodes/IR.h"
#include "../Nodes/Token.h"


#include <vector>
#include <string>

using namespace std;

class BackEnd {
private:
	string Seperator;
	string Register_Pre_Fix;
	string Number_Pre_Fix;
	string Label_Post_Fix;

	vector<IR*> Opcodes;

	vector<IR*> Input;
	string* Output;

	void Init();
	void Factory();
public:
	BackEnd(vector<IR*> in) : Input(in) {
		Output = new string("");
		Init();
	}
	BackEnd(vector<IR*> in, string* out) : Input(in), Output(out) {
		Init();
		Factory();
	}
};

#endif