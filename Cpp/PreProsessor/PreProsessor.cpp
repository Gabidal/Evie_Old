#include "../../H/PreProsessor/PreProsessor.h"

extern Usr* sys;

void PreProsessor::Factory() {
	Replace_Const_Name_With_Value(Input);
	for (int i = 0; i < Input.size(); i++) {
		If(i);
		Include(i);
	}
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

	string File_Name = Update_Working_Dir(Input[(size_t)i + 1].Value.substr(1, Input[(size_t)i + 1].Value.size() - 2));

	for (string s : Included_Files)
		if (File_Name == s)
		{
			cout << "Warning: " << Input.at((size_t)i + 1).Value << " is already included." << endl;
			Input.erase(Input.begin() + i + 1);
			Input.erase(Input.begin() + i);
			return;
		}

	Docker D(File_Name, Working_Dir);

	Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i);

	Input.insert(Input.begin() + i, D.Output.begin(), D.Output.end());

	Included_Files.push_back(File_Name);

	Factory();
	return;
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
	bool same = false;

	if (condition[0].Value == condition[2].Value)
		same = true;

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


string PreProsessor::Update_Working_Dir(string File_Name)
{
	int i = (int)File_Name.find_last_of('/');
	if (i != -1)
	{
		Working_Dir += File_Name.substr(0, (size_t)i + 1);
		return File_Name.substr((size_t)i + 1);
	}
	return File_Name;
}