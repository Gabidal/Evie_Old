#ifndef _DOCKER_H_
#define _DOCKER_H_
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "../Back/Token.h"
//the analyzers
#include "../Lexer/Lexer.h"
#include "../Lexer/Component.h"

class Docker
{
public:
	vector<Component> Output;
	Docker(string FN, string WD, string PT) : FileName(FN), Working_Dir(WD), Priority_Type(PT){
		//look up table at:https://en.wikipedia.org/wiki/List_of_file_signatures.
		//TXT files do not have a header
		//Translators.push_back({ "TXT", TXT_Analyzer });
		Translators.push_back({ "MZ", bind(&Docker::DLL_Analyzer, this)});
		Translators.push_back({ "!<arch>\62",  bind(&Docker::LIB_Analyzer, this) });
		Translators.push_back({ "\127ELF",  bind(&Docker::ELF_Analyzer, this) });
		Get_Analyzer();
	}
	~Docker(){}

private:
	vector<Token*> Types;
	//open the file and look for the identifier of the file header
	void Get_Analyzer();

	void TXT_Analyzer();
	void DLL_Analyzer();
	void LIB_Analyzer();
	void ELF_Analyzer();

	string FileName = "";
	string Working_Dir = "";
	string Priority_Type = "";
	//map<ID, function ID>
	vector<pair<string, function<void()>>> Translators;
};

#endif