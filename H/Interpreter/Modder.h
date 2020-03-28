#ifndef _MODDE_H_
#define _MODDER_H_
#include "../OpC/IR.h"
#include "../Back/Token.h"
#include <vector>
#include <map>

class Modder
{
public:
	Modder(int &i, vector<IR*> out, vector<Token*> in) : I(i), Output(out)
	{
		Input = in;
		Factory();
	}

	~Modder(){}

private:
	void Factory();
	void Detect_If(int i);
	void Detect_Operator(int i);
	void Detect_Parenthesis(int i);

	vector<IR*> &Output;
	vector<Token*> Input;
	int& I;
};


#endif