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
	Modder(IR &i, vector<IR*> out, vector<Token*> in) : I(i), Output(out)
	{
		Input = in;
		Factory();
	}

	map<string, Symbol_Table*> Get_Member_Pointters();
	map<string, Waiter*> Get_Member_Data();
	~Modder(){}

private:
	void Factory();
	void Detect_If(int i);
	void Passing(int i);
	vector<IR*> &Output;
	vector<Token*> Input;
	IR& I;
};


#endif