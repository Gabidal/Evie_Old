#include "../../H/Docker/Mangler.h"
#include "../../H/Nodes/Node.h"
#include <iomanip>
#include <sstream>

map<string, pair<int, string>> MANGLER::IDS;

string MANGLER::Un_Mangle(string raw) {
	//try to find if there are any prefixes and remove them into another string
	string PreFix;
	if ((int)raw.find_last_of(' ') >= 0) {
		int pre_i = (int)raw.find_last_of(' ');
		PreFix = raw.substr(0, pre_i + 1);
		raw = raw.substr((size_t)pre_i + 1, raw.size());
	}
	string Function = "";
	vector<string> Parenthesis;
	string Return_Type = "";
	bool Func_Name = true;
	string Current;
	string Current_Variable = "";
	string Current_PreFix = "";
	string Current_Complex_Name = "";
	string STD = "";
	vector<string> Current_Parameter_Inheritted;
	//type ptr new  type
	if (raw[0] == '_' && raw[1] == 'Z') {
		//C++ unmangler
		//_Z3NEWi3ABC
		STD = "cpp";
		for (int i = 2; i < raw.size(); i++) {
			Current = raw[i];
			Current_Complex_Name += raw[i];
			//for char based aliases.
			if (MANGLER::IDS.find(Current) != MANGLER::IDS.end()) {
				if (MANGLER::IDS.at(Current).first == MANGLER::VARIABLE) {
					//when a new variable starts appearing we want to push the previus into the function-
					//parameters string.
					if (Current_Variable != "") {
						Parenthesis.push_back(Current_Variable);
						Current_Variable = "";
						Current_PreFix = "";
					}
					Current_Complex_Name = "";
					if (Current_PreFix != "")
						Current_Variable = Current_PreFix + " ";
					Current_Variable += MANGLER::IDS.at(Current).second + " ";
				}
				else if (MANGLER::IDS.at(Current).first == MANGLER::POSTFIX) {
					Current_Variable += MANGLER::IDS.at(Current).second + " ";
					Current_Complex_Name = "";
				}
				else if (MANGLER::IDS.at(Current).first == MANGLER::PREFIX) {
					if (Current_Variable != "")
						Parenthesis.push_back(Current_Variable);
					Current_PreFix += MANGLER::IDS.at(Current).second + " ";
					Current_Complex_Name = "";
				}
			}
			else if (MANGLER::IDS.find(Current) != MANGLER::IDS.end()) {
				//for multi char based aliases.
				if (MANGLER::IDS.at(Current_Complex_Name).first == MANGLER::VARIABLE) {
					//when a new variable starts appearing we want to push the previus into the function-
					//parameters string.
					if (Current_Variable != "") {
						Parenthesis.push_back(Current_Variable);
						Current_Variable = "";
					}
					Current = "";
					if (Current_PreFix != "")
						Current_Variable = Current_PreFix + " ";
					Current_Variable += MANGLER::IDS.at(Current_Complex_Name).second + " ";
				}
				else if (MANGLER::IDS.at(Current_Complex_Name).first == MANGLER::POSTFIX) {

					Current = "";
					Current_Variable += MANGLER::IDS.at(Current_Complex_Name).second + " ";
				}
				else if (MANGLER::IDS.at(Current_Complex_Name).first == MANGLER::PREFIX) {
					if (Current_Variable != "") {
						Parenthesis.push_back(Current_Variable);
						Current_Variable = "";
					}

					Current = "";

					Current_PreFix += MANGLER::IDS.at(Current_Complex_Name).second + " ";
				}
			}
			//TODO: add that if the current complex name is bigger than 2(.., current num) then dont do this.
			else if (((raw[i] >= 48) && (raw[i] <= 57))) {
				string tmp = "";
				tmp += raw[i];
				for (int j = i + 1; j < raw.size(); j++) {
					if (((raw[j] >= 48) && (raw[j] <= 57)))
						tmp += (char)raw[j];
					else
						break;
				}
				int size = atoi(tmp.c_str());
				string name = "";
				for (int j = i + tmp.size(); (j < (size + i + tmp.size())) && j < raw.size(); j++) {
					name += (char)raw[j];
				}
				if (Func_Name) {
					Function = name;
					Func_Name = false;
				}
				else {
					//class based parameters.
					if (Current_Variable != "") {
						Parenthesis.push_back(Current_Variable);
						Current_Variable = "";
					}

					Current_Variable = Current_PreFix + " " + name;
				}
				i += size + tmp.size() - 1;
			}
		}
		if (Current_Variable != "") {
			Parenthesis.push_back(Current_Variable);
		}
	}
	//else if (raw[0] == '_' && raw[1] == 'E') {
	//	STD = "evie";
	//}
	//else if (raw[0] == '_' && raw[1] == 'V') {
	//	STD = "vivid";
	//}
	else {
		//this lauches when no call type is identifyed.
		Function = raw;
	}
	string Result = Return_Type + " " + STD + " " + Function + "( ";
	for (int i = 0; i < ((int)Parenthesis.size()) - 1; i++) {
		Result += Parenthesis[i] + ", ";
	}
	if (Parenthesis.size() > 0)
		Result += Parenthesis.back();
	Result += ")";
	return PreFix + Result;
}

vector<string> Classes;

string MANGLER::Mangle(Node* raw)
{
	string Result = "";

	if (raw->is("cpp") != -1) {
		//if the function call uses the C standard.
		//_import_func_cpp_internal_print__char__int to
		//_Z14internal_printPci
		if (raw->is(FUNCTION_NODE) || raw->is(IMPORT) || raw->is(PROTOTYPE)) {
			Classes.clear();
			Result = "_Z";
			if (raw->Parent->is(CLASS_NODE) && raw->Parent->Name != "GLOBAL_SCOPE")
				Result += "n" + raw->Parent->Name.size() + raw->Parent->Name;
			Result += to_string(raw->Name.size()) + raw->Name;
			if (raw->Parent->is(CLASS_NODE) && raw->Parent->Name != "GLOBAL_SCOPE")
				Result += "E";
			if (raw->Parameters.size() < 1)
				Result += "v";
			for (auto i : raw->Parameters) {
				Result += Mangle(i);
			}
		}
		else if (raw->is(CLASS_NODE)) {
			string p = "";
			string r;
			if (raw->is("ptr") != -1) {
				for (auto i : raw->Inheritted) {
					if (i == "ptr")
						p += "P";
				}
				r = p + r;
			}
			if (Is_Base_Type(raw)) {
				return p + string(raw->Name.data(), 1);
			}
			else {
				if (Find(raw->Name) != -1) {
					stringstream stream;
					stream << hex << Find(raw->Name);
					r = "S" + string(stream.str()) + "_";
				}
				else
					r = to_string(raw->Name.size()) + raw->Name;
				return r;
			}
		}
		else if (raw->is(OBJECT_DEFINTION_NODE) || raw->is(OBJECT_NODE)) {
			int I = 0;
			string p = "";
			if (raw->is("ptr") != -1) {
				for (auto i : raw->Inheritted) {
					if (i == "ptr")
						p += "P";
				}
			}
			for (auto i : raw->Inheritted) {
				if (!Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT))
					I++;
				if (I > 1) {
					//PcIic = char int char ptr a
					//Evie engine 3.0.0 cannot export multi inheritted variables yet.
					//TODO: Make that happen.
					throw::exception("Exporting multi inheritted variables is not yet supported.");
				}
			}
			if (Is_Template(raw)) {
				//uugabuuga?
			}
			else if (Is_Based_On_Base_Type(raw)) {
				//int a;
				string Type = "";
				for (auto i : raw->Inheritted)
					if (!Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT))
						Type = i;
				Result = p + string(Type.data(), 1);
			}
			else {
				//banana a;
				string Type = "";
				for (auto i : raw->Inheritted)
					if (!Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT))
						Type = i;
				Result = p + to_string(Type.size()) + Type;
			}
		}
		
	}
	else if (raw->is("vivid") != -1) {
		//if the function call uses the V standard.
	}
	else if (raw->is("evie") != -1){
		//if the function call uses the Evie standard.
	}
	else {
		//generic name labels for normal .
		Result = raw->Name.size();
	}
	return Result;
}

bool MANGLER::Is_Base_Type(Node* n)
{
	bool Result = true;
	for (auto i : n->Childs) {
		if (i->Name == "size" && i->is("const") != -1)
			continue;
		Result = false;	//because base types do not have any other member other than the Size.
	}
	for (auto i : n->Inheritted) {
		if (Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT))
			continue;
		Result = false;	//because base types do not inherit other classes, only features.
	}
	return Result;
}

bool MANGLER::Is_Based_On_Base_Type(Node* n)
{
	bool Result = true;
	//int a;
	for (auto i : n->Inheritted) {
		if (Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT))
			continue;
		if (!Is_Base_Type(n->Find(i, n->Parent)))
			Result = false;
	}
	return Result;
}

bool MANGLER::Is_Template(Node* n)
{
	bool Result = true;
	for (auto i : n->Inheritted)
		if (!Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT)) {
			Result = false;
			break;
		}
	return Result;
}

int MANGLER::Find(string s)
{
	for (int i = 0; i < Classes.size(); i++)
		if (Classes[i] == s)
			return i;
	Classes.push_back(s);
	return -1;
}

void MANGLER::Add_ID(pair<string, pair<int, string>> id) {
	if (IDS.find(id.first) != IDS.end()) {
		cout << "Warning: ID " << id.first << " already exist's" << endl;
		return;
	}
	else
		IDS[id.first] = id.second;
}