#ifndef _MODDE_H_
#define _MODDER_H_
#include "../OpC/IR.h"
#include "../Back/Token.h"
#include <vector>
#include <map>

class Modder
{
public:
	Modder(IR &i, vector<IR*> out, vector<Token*> in) : I(i), Output(out)
	{
		Input = in;
		Factory();
	}

	~Modder(){}

private:
	void Factory();

	map<string, vector<IR*>> Items;
	vector<IR*> &Output;
	vector<Token*> Input;
	IR& I;
};


#endif