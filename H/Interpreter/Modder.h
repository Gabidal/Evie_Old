#ifndef _MODDE_H_
#define _MODDER_H_
#include "../OpC/IR.h"
#include "../Back/Token.h"
#include "../UI/Usr.h"
#include <vector>
#include <map>

class Modder : public Symbol_Table
{
public:
	Modder(IR &i, vector<IR*> &out, vector<Token*> in) : I(i), Output(out)
	{
		Input = in;
	}

	map<string, Symbol_Table*> Get_Member_Pointters();
	map<string, Waiter*> Get_Member_Data();
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