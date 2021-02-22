#ifndef _IRPOSTPROSESSOR_H_
#define _IRPOSTPROSESSOR_H_

#include "../Flags.h"
#include "../Nodes/IR.h"
#include "../Nodes/Token.h"
#include "../../H/BackEnd/Selector.h"


#include <vector>
#include <string>

using namespace std;

class IRPostProsessor {
private:
	vector<IR*>* Input;

	void Scale_To_Same_Size(int i);
	void Registerize(Token* t, int i);
	void Give_New_Register(Token* t, int i);
	void Handle_Global_Labels();
	void Clean_Selector(int& i);
	void Prepare_Function(int i);
	void Handle_Labels(int i);

	void Handle_Stack_Usages(Token* t);
	int Parse_Complex(IR* ir, int i, bool Registry);
public:
	IRPostProsessor(vector<IR*>* in) : Input(in) { Factory(); }
	void Factory();
};

#endif