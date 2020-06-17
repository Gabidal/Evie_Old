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
#include <regex>
//the analyzers
#include "../Lexer/Lexer.h"
#include "../Lexer/Component.h"
#include "Section.h"
#include "../../H/UI/Usr.h"
#include "../Mangler/Mangler.h"
//thanks for contribitors at github that are making linux, im not part of the writing team of the file!
//https://github.com/torvalds/linux/blob/master/include/uapi/linux/elf.h
#include "ELF.h"
#include "LIB.h"


class Docker
{
public:
	vector<Component> Output;
	Docker(string FN, string WD, string PT) : FileName(FN), Working_Dir(WD), Priority_Type(PT){
		//look up table at:https://en.wikipedia.org/wiki/List_of_file_signatures.
		//TXT files do not have a header
		//Translators.push_back({ "TXT", TXT_Analyzer });
		Translators.push_back({ "MZ", bind(&Docker::DLL_Analyzer, this)});
		Translators.push_back({ "!<arch>",  bind(&Docker::LIB_Analyzer, this) });
		Translators.push_back({ "\x7F" "ELF",  bind(&Docker::ELF_Analyzer, this) });
		Start_Analyzer();
	}
	~Docker(){}

private:
	//vector<pair<Type, Regex string>>
	vector<pair<string, string>> Types;
	//open the file and look for the identifier of the file header
	void Start_Analyzer();
	//returns the filename of the header file
	vector<Component> Get_Header(string File_Name);
	//parse the tokens from the header file
	//parse the Tokens into Type'n Regex style.
	//and remove the binfile header rule syntax thingys!
	void Separate_Identification_Patterns(vector<Component> Tokens);
	//open file to constexpr char buffer
	vector<unsigned char> Get_Char_Buffer_From_File(string FN, string WD);
	//Read section
	//		function_names, type
	vector<pair<string, string>> Get_Names_Of(Section area);
	//Syntaxly_Correct_Return_Of_Vector_Strings
	void Syntax_Correcter(vector<pair<string, string>> symbols);
	//append 
	void Append(vector<Component>& Dest, vector<Component> Source);


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