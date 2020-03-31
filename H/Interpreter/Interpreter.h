#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include "../Lexer/Word.h"
#include "../Back/Token.h"
#include "../UI/Usr.h"
#include <vector>
#include <string>
#include <optional>

extern Usr* sys;

class Interpreter
{
public:
	vector<Word*> Output;
	Interpreter(vector<Word*> &in, int I, vector<Token*> D) : Input(in) {
		i = I;
		Defined = D;
		Factory();
	}
	~Interpreter() {
	}

private:
	int i;
	vector<Word*> &Input;
	vector<Word*> TMP;
	vector<Token*> Defined;
	void Factory();
	void Detect_Ifs();
	void Detect_Patterns();
	bool Constructable(int i);
	void Detect_Mod();
	void Append(vector<string>* Dest, vector<string> Source);
	//void Append(vector<Word*>* Dest, vector<Word*> Source, int i);
	void Append(vector<Word*>* Dest, vector<Word*> Source);
};


#endif