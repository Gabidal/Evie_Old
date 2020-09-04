#ifndef _PREPROSESSOR_H_
#define _PREPROSESSOR_H_

#include "../Flags.h"
#include "../Lexer/Component.h"
#include "../Docker/Docker.h"
#include "../UI/Usr.h"
#include "../Docker/ASM.h"
#include "../Docker/ELF.h"
#include "../Docker/LIB.h"
#include "../Docker/TXT.h"
#include "../Docker/Mangler.h"

#include <vector>

using namespace std;

class PreProsessor
{
public:
	PreProsessor(vector<Component> &list) : Input(list){}
	~PreProsessor(){}
	void Factory();
	void Include(int i);
	void Include(string filename);
	void If(int i);
	bool Calculate(vector<Component>);
	void Define_Const_Value(int i);
	void Replace_Const_Name_With_Value(vector<Component> &in);
	void Syntax_Correcter(vector<string> symbols, string type, int i);


	//std::map<string::const_name, Component::value>
	map<string, Component> Defined_Constants;
	vector<Component>& Input;
private:
};

#endif