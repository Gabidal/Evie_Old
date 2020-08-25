#include "../../H/Docker/Mangler.h"

map<string, pair<int, string>> MANGLER::IDS;

string MANGLER::Un_Mangle(string raw) {
	string Function = "";
	vector<string> Parenthesis;
	string Return_Type = "";
	bool Func_Name = true;
	string Current;
	string Current_Variable = "";
	string Current_PreFix = "";
	string Current_Complex_Name = "";
	vector<string> Current_Parameter_Inheritted;
	//type ptr new  type
	if (raw[0] == '_' && raw[1] == 'Z') {
		//C++ unmangler
		//_Z3NEWi3ABC
		for (int i = 2; i < raw.size(); i++) {
			Current = "" + raw[i];
			Current_Complex_Name += raw[i];
			//for char based aliases.
			if (MANGLER::IDS[Current].first == MANGLER::VARIABLE) {
				//when a new variable starts appearing we want to push the previus into the function-
				//parameters string.
				if (Current_Variable != "") {
					Parenthesis.push_back(Current_Variable);
					Current_Variable = "";
				}
				Current_Complex_Name = "";
				Current_Variable = Current_PreFix + " " + MANGLER::IDS[Current].second + " ";
			}
			else if (MANGLER::IDS[Current].first == MANGLER::POSTFIX) {
				Current_Variable += MANGLER::IDS[Current].second + " ";
				Current_Complex_Name = "";
			}
			else if (MANGLER::IDS[Current].first == MANGLER::PREFIX) {
				if (Current_Variable != "")
					Parenthesis.push_back(Current_Variable);
				Current_PreFix += MANGLER::IDS[Current].second + " ";
				Current_Complex_Name = "";
			}
			//for multi char based aliases.
			else if (MANGLER::IDS[Current_Complex_Name].first == MANGLER::VARIABLE) {
				//when a new variable starts appearing we want to push the previus into the function-
				//parameters string.
				if (Current_Variable != "") {
					Parenthesis.push_back(Current_Variable);
					Current_Variable = "";
				}
				Current = "";

				Current_Variable = Current_PreFix + " " + MANGLER::IDS[Current_Complex_Name].second + " ";
			}
			else if (MANGLER::IDS[Current_Complex_Name].first == MANGLER::POSTFIX) {

				Current = "";
				Current_Variable += MANGLER::IDS[Current_Complex_Name].second + " ";
			}
			else if (MANGLER::IDS[Current_Complex_Name].first == MANGLER::PREFIX) {
				if (Current_Variable != "") {
					Parenthesis.push_back(Current_Variable);
					Current_Variable = "";
				}

				Current = "";

				Current_PreFix += MANGLER::IDS[Current_Complex_Name].second + " ";
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
				for (int j = i + tmp.size(); (j < (size + i + 1)) && j < raw.size(); j++) {
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
				i += size;
			}
		}
	}
	//else if (raw[0] == '_' && raw[1] == 'E') {

	//}
	else {
		//this lauches when no call type is identifyed.
		Function = raw;
	}
	string Result = Return_Type + " " + Function + "( ";
	for (int i = 0; i < Parenthesis.size() - 1; i++) {
		Result += Parenthesis[i] + ", ";
	}
	Result += Parenthesis.back() + ")";
	return Result;
}

void MANGLER::Add_ID(pair<string, pair<int, string>> id) {
	if (IDS.find(id.first) != IDS.end()) {
		cout << "Warning: ID " << id.first << " already exist's" << endl;
		return;
	}
	else
		IDS[id.first] = id.second;
}