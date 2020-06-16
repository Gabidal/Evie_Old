#include "../../H/Mangler/Mangler.h"

string Mangler::Un_Mangle(string Name)
{
	if (Name.size() < 3) return Name + " ()";
	if (Name[0] != '_' || (Name[1] != 'Z')) return Name + " ()";

	vector<string> Result;
	//_Z6bananaii
	for (int i = 0; i < Name.size(); i++) {
		if (isdigit(Name[i]) != 0) {
			//6banana5apple
			string size = "";
			for (int j = i; j < Name.size(); j++)
				if (isdigit(Name[j]) != 0)
					size += Name[j];
			int Size = atoi((char*)Name[i]);
			Result.push_back(Name.substr(i+1, Size));
			i += Size;
		}
		//parameters
		else if (Name[i] == 'R' || Name[i] == 'P') {
			Result.push_back("ptr");
		}
		else {
			Result.push_back(", ");
		}
	}
	//construct the returnable fucntion
	string Func_Name = Result[0];
	Result.erase(Result.begin());
	string Parameters = " ( ";
	for (string i : Result) {
		Parameters += i;
	}
	Parameters += " )";
	return Func_Name + Parameters;
}

string Mangler::Mangle(Token* t)
{
	string Func_Name = "_Z" + to_string(t->Name.size()) + t->Name;
	for (Token* i : t->Left_Side_Token->Childs) {
		if (i->is("ptr"))
			Func_Name += "P";
		for (string s : i->Types) {
			if (s == "mangle")
				continue;
			if (s != "ptr")
				Func_Name += to_string(s.size()) + s;
		}
	}

	return Func_Name;
}

string Mangler::Get_Main_Name(string Name)
{
	if (Name.size() < 3) return Name;
	string tmp;
	tmp += Name.substr(0, 2);
	if (tmp != "_Z") return Name;


	for (int i = 0; i < Name.size(); i++) {
		if (isdigit(Name[i]) != 0) {
			//6banana5apple
			string size = "";
			for (int j = i; j < Name.size(); j++) {
				if (isdigit(Name[j]) != 0)
					size += Name[j];
				else
					break;
			}
			int Size = atoi(size.c_str());
			return Name.substr(i+1, Size);
		}
	}
	return "Unable_To_Mangle: " + Name;
}
