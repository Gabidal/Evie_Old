#ifndef GENERATOR_H_
#define GENERATOR_H_
#include <vector>
#include "Token.h"
#include "../OpC/IR.h"
using namespace std;


class Generator
{
public:
	vector<Token*> Input;
	vector<IR*> Output;
	Generator()
	{
	}

	~Generator();

private:

};


#endif