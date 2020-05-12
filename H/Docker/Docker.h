#ifndef _DOCKER_H_
#define _DOCKER_H_
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "../Back/Token.h"
//the analyzers
#include "../Lexer/Lexer.h"

class Docker
{
public:
	vector<Token*> Output;
	vector<Token*> Types;
	Docker(string FN, string WD, string PT) : FileName(FN), Working_Dir(WD), Priority_Type(PT){
		
	}
	void TXT_Analyzer();
	void DLL_Analyzer();
	void LIB_Analyzer();
	void OBJ_Analyzer();
	void ELF_Analyzer();
	~Docker(){}

private:
	string FileName = "";
	string Working_Dir = "";
	string Priority_Type = "";
	//map<ID, function ID>
	map<string, function<void()>> Translators;
};

#endif