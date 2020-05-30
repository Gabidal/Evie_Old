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
	void Make_Context();
	void Gather_Subroutins();
	void Make_Comment();
	string Get_Token_Info(Token* t);
	~Comment(){}
	Comment(IR* t) {
		OPCode = t;
		Make_Comment();
	}
private:
	IR* OPCode = nullptr;
	string Usr_Comment = "";
	string Context = "";
	string Sub_Content = "";
};

#endif
