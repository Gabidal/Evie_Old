#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include "../Lexer/Word.h"
#include "../Back/Token.h"
#include "../UI/Usr.h"
#include <vector>
#include <string>

extern Usr* sys;

class Interpreter
{
public:
	Interpreter(vector<Word*> &in, int I, vector<Token*> D) {
		Input = in;
		i = I;
		Defined = D;
		Factory();
	}
	~Interpreter() {
	}

private:
	int i;
	vector<Word*> Input;
	vector<Word*> TMP;
	vector<Token*> Defined;
	void Factory();
	void Detect_Ifs();
	void Construct(int i);
};


#endif