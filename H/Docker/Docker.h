#ifndef _DOCKER_H_
#define _DOCKER_H_
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <fstream>
#include <iostream>
#include <filesystem>
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
		Start_Analyzer();
	}
	~Docker(){}

private:
	//vector<pair<Type, Regex string>>
	vector<pair<string, string>> Types;
	//open the file and look for the identifier of the file header
	void Start_Analyzer();
	//returns the filename of the header file
	vector<Component> Get_Header();
	//parse the tokens from the header file
	vector<Token*> Get_Parsed_Include_File(vector<Component> In);
	//parse the Tokens into Type'n Regex style.
	//and remove the binfile header rule syntax thingys!
	void Separate_Identification_Patterns(vector<Token*> Tokens);

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