#ifndef _COMMENT_H_
#define _COMMENT_H_
#include "Token.h"
#include "../OpC/IR.h"
#include <string>
#include <vector>
using namespace std;

class Comment
{
public:
	vector<string> Output;
	void Factory();
	void Detect_Complex_Numbers(Token* n);
	string Get_Token_Info(Token* t);
	~Comment(){}
	Comment(IR* t) {
		Input = t;
		Factory();
	}
private:
	IR* Input = nullptr;
};

#endif
