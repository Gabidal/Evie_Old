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
	Comment(Token* t) : AST(t) {}
	Comment(IR* t) : IR(t) {}
	void Factory();
	void Make_Context();
	void Gather_Subroutins();
	string Get_Info_From_AST(Token* t);
	string Get_Token_Info(Token* t);
	string Get_Comment();
	~Comment(){}

private:
	IR* OPCode = nullptr;
	Token* AST = nullptr;
	string Context = "";
	vector<string> Subroutins;
};

#endif
