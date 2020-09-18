#ifndef _TOKEN_H_
#define _TOKEN_H_
#include "../Flags.h"

#include <string>
#include <vector>

using namespace std;

//memory(handle, operator(offsetter), num(12))
class Token{
private:
	long Flags = 0;
	int Life_Span = 0;
	int Size = 0;
	string Name;
	vector<Token*> Childs;
public:
	Token(long f) : Flags(f) {}
	Token(long f, string n) : Flags(f), Name(n) {}
	Token(long f, string n, int s) : Flags(f), Name(n), Size(s) {}
	Token(long f, string n, int s, vector<Token*> c) : Flags(f), Name(n), Size(s), Childs(c) {}
	bool is(int flag){return (Flags & flag) == flag;}
	bool Any(int flags){return (Flags & flags) != 0;}
	void add(int flag){this->Flags |= flag;}
	void remove(int flag){this->Flags ^= (Flags & flag);}
};

#endif