#ifndef _MODDE_H_
#define _MODDER_H_
#include "../OpC/IR.h"
#include "../Back/Token.h"
#include "../UI/Usr.h"
#include <vector>
#include <map>

class Modder : public Object
{
public:
	Modder(IR &i, vector<IR*> &out, vector<Token*> in) : I(i), Output(out)
	{
		Input = in;
	}

	map<string, Object*> Get_Members();
	~Modder(){}
	void Factory();

private:
	void Detect_If(Token* t);
	bool Passing(Token* Condition);
	void Detect_Parenthesis(Token* t);
	void Detect_Operator(Token* t);
	vector<IR*> &Output;
	vector<Token*> Input;
	IR& I;
};


#endif