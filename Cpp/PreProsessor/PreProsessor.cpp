#include "../../H/PreProsessor/PreProsessor.h"

extern Usr* sys;
extern string* FileName;

void PreProsessor::Factory() {
	Replace_Const_Name_With_Value(Input);
	for (int i = 0; i < Input.size(); i++) {
		If(i);
		Include(i);
		Detect_Directory_Usage_End(i);
	}

	Re_Arrnage_Components();
	return;
}

void PreProsessor::Include(int i)
{
	//use "file.x"
	//<summary>
	//Give it to Docker. it can handle many files
	//</summary>
	if (Input[i].Value != "use")
		return;
	if (!Input[(size_t)i+1].is(Flags::STRING_COMPONENT))
		return;

	string File_Name = Input[(size_t)i + 1].Value.substr(1, Input[(size_t)i + 1].Value.size() - 2);

	Docker D(File_Name);

	Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i);

	for (auto j : DOCKER::Output) {
		Syntax_Correcter(j.second, j.first, i);
	}
	DOCKER::Output.clear();

	DOCKER::Append(sys->Info.Libs, DOCKER::Libs);
	DOCKER::Append(sys->Info.Source_Files, DOCKER::Assembly_Source_File);
	DOCKER::Libs.clear();
	DOCKER::Assembly_Source_File.clear();

	Factory();
	return;
}

void PreProsessor::Include(string File_Name) {
	Docker D(File_Name);

	for (auto j : DOCKER::Output) {
		Syntax_Correcter(j.second, j.first, 0);
	}
	DOCKER::Output.clear();

	DOCKER::Append(sys->Info.Libs, DOCKER::Libs);
	DOCKER::Append(sys->Info.Source_Files, DOCKER::Assembly_Source_File);
	return;
}

void PreProsessor::Syntax_Correcter(vector<string> symbols, string filename, int i)
{
	//import loyal func [name]()()
	//import generic func [name]()()
	vector<Component> content;
	//FileName = new string(DOCKER::Working_Dir.back().second + filename);
	FileName = new string(DOCKER::Included_Files.back());
	vector<Component> tmp;
	if (filename == DOCKER::Get_File_Extension(filename)) {
		//if the filenmae doesnt have a file extension this happends.
	}
	else if (DOCKER::Get_File_Extension(filename) != "e") {
		for (auto j : symbols)
			if (j != "\n" && j != "")
				DOCKER::Append(tmp, Lexer::GetComponents( "import " + MANGLER::Un_Mangle(j) + "\n"));
	}
	else {
		for (auto j : symbols)
			if (j != "\n" && j != "")
				DOCKER::Append(tmp, Lexer::GetComponents(j));
	}
	DOCKER::Append(tmp, { Component(string(*FileName), Flags::END_OF_DIRECTIVE_CHANGING_FILE) });
	DOCKER::Append(Input, tmp, i);
}

void PreProsessor::Detect_Directory_Usage_End(int i)
{
	if (!Input[i].is(Flags::END_OF_DIRECTIVE_CHANGING_FILE))
		return;
	for (auto j : DOCKER::Working_Dir) {
		if (j.first == Input[i].Value)
			DOCKER::Working_Dir.pop_back();
	}
}

void PreProsessor::Re_Arrnage_Components()
{
	vector<Component*> Linear_Input = Linearise(Input);
	long long Line = 0;
	long long Character = 0;

	for (auto& i : Linear_Input) {
		if (i->is(Flags::END_COMPONENT))
			Line++;

		
	}
}

vector<Component*> PreProsessor::Linearise(vector<Component>& Tree)
{
	vector<Component*> Result;

	for (auto& i : Tree) {
		if (i.is(Flags::PAREHTHESIS_COMPONENT)) {
			vector<Component*> Tmp = Linearise(i.Components);
			Result.insert(Result.end(), Tmp.begin(), Tmp.end());
		}
		else {
			Result.push_back(&i);
		}
	}

	return Result;
}

void PreProsessor::If(int i)
{
	if (Input[i].Value != "if")
		return;
	if (!Input[(size_t)i + 1].is(Flags::PAREHTHESIS_COMPONENT))
		return;

	if (Calculate(Input[(size_t)i + 1].Components)) {
		vector<Component> tmp = Input[(size_t)i + 2].Components;
		Input.erase(Input.begin() + i);		//erase the if
		Input.erase(Input.begin() + i);		//erase the condition
		Input.erase(Input.begin() + i);		//erase the duplicated cholds of this pre if
		Input.insert(Input.begin() + i, tmp.begin(), tmp.end());
	}
	else {
		Input.erase(Input.begin() + i);		//erase the if
		Input.erase(Input.begin() + i);		//erase the condition
		Input.erase(Input.begin() + i);		//erase the duplicated cholds of this pre if
	}
	
	Factory();
	return;
}

bool PreProsessor::Calculate(vector<Component> condition)
{
	//0	, 1	, 2
	//OS == "win"
	//"win" == OS
	//OS = macro that has value "win" inside
	//first determine the side the SYS info is
	//Notice!!! this cannot happen after parser because if the preprosessed if has-
	//an include inside it, it wont work post parser!!!
	bool same = condition[0].Value == condition[2].Value;

	if (condition[1].Value == "==")
		return same;
	else if (condition[1].Value == "!=")
		return !same;

	return false;
}

void PreProsessor::Define_Const_Value(int i)
{
	//do this when you know gab, how to make const values in source files.
}

void PreProsessor::Replace_Const_Name_With_Value(vector<Component> &in)
{
	//<summary>
	//finds the defined const names and replaces-
	//them with the const value the names represents.
	//</summary>
	for (auto& c : in) {
		if (c.is(Flags::PAREHTHESIS_COMPONENT))
			Replace_Const_Name_With_Value(c.Components);
		else if (c.is(Flags::KEYWORD_COMPONENT))
			continue;
		else
			for (auto constant : Defined_Constants)
				if (c.Value == constant.first)
					c = constant.second;
	}
	return;
}

