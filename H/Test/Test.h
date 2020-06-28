#ifndef _TEST_H_
#define _TEST_H_

#include "../Lexer/Lexer.h"
#include "../Parser/Parser.h"
#include "../Back/Definer.h"
#include "../Emulator/Emulator.h"
#include "../Selector/Selector.h"
#include "../Back/Generator.h"
#include "../UI/Usr.h"
#include "../UI/Producer.h"
#include "../UI/Safe.h"
#include <sstream>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

class Test
{
public:
	Test();//factory
	~Test() {}
	void Print_Results();	//prints working & not working features into console
private:
	//			CLASS ID,   INPUT, RESULT
	vector<pair<string, pair<string, string>>> Working_Features;
	//			CLASS ID,   INPUT, RESULT
	vector<pair<string, pair<string, string>>> Not_Working_Features;
	//			CLASS ID,  FEATURE,  INPUT_STRING
	vector<pair<string, pair<string, string>>> Input;

	Token* Find(string name, vector<Token*>);
	string Replace(string Source, char oldVal, string newVal);
	void Report_Behaviour(int i, string report, bool working);

	void Parser_Constructors(int i);
	void Parser_Prototypes(int i);
	void Parser_Size(int i);

};

#endif