#include "../../H/Docker/Mangler.h"
#include "../../H/Nodes/Node.h"
#include <iomanip>
#include <sstream>

vector<pair<string, vector<pair<string, pair<int, string>>>>> MANGLER::IDS;
bool Functoin_Name_Is_Before_End_Of_Namespace = false;

string MANGLER::Un_Mangle(string raw) {
	//try to find if there are any prefixes and remove them into another string
	string PreFix;
	if ((int)raw.find_last_of(' ') >= 0) {
		int pre_i = (int)raw.find_last_of(' ');
		PreFix = raw.substr(0, (size_t)pre_i + 1);
		raw = raw.substr((size_t)pre_i + 1, raw.size());
	}
	bool Func_Name = true;
	bool Namespace = false;

	string Function = "";
	vector<string> Parenthesis;
	string Return_Type = "";
	string Current;
	string Current_Variable = "";
	string Current_PreFix = "";
	string Current_Complex_Name = "";
	vector<string> Scope_Path;
	string STD = "";
	vector<string> Current_Parameter_Inheritted;
	bool Return_Type_Section = false;
	//type ptr new  type
	if (raw[0] == '_' && raw[1] == 'Z') {
		//C++ unmangler
		//_Z3NEWi3ABC
		STD = "cpp";
		vector<pair<string, pair<int, string>>>& Current_IDS = *Find_STD_List(STD);
		for (int i = 2; i < raw.size(); i++) {
			Current = raw[i];
			Current_Complex_Name += raw[i];
			//for char based aliases.
			if (Find(Current, &Current_IDS) != nullptr) {
				if (Find(Current, &Current_IDS)->first == MANGLER::VARIABLE) {
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
					Current_Variable += Find(Current, &Current_IDS)->second + " ";
				}
				else if (Find(Current, &Current_IDS)->first == MANGLER::POSTFIX) {
					Current_Variable += Find(Current, &Current_IDS)->second + " ";
					Current_Complex_Name = "";
				}
				else if (Find(Current, &Current_IDS)->first == MANGLER::PREFIX) {
					if (Current_Variable != "")
						Parenthesis.push_back(Current_Variable);
					Current_PreFix += Find(Current, &Current_IDS)->second + " ";
					Current_Complex_Name = "";
				}
				else if (Find(Current, &Current_IDS)->first == MANGLER::CLASS && Current_Complex_Name.size() == 1) {
					Namespace = true;
					if (Functoin_Name_Is_Before_End_Of_Namespace)
						Func_Name = false;
				}
				else if (Find(Current, &Current_IDS)->first == MANGLER::END_CLASS && Current_Complex_Name.size() == 1) {
					Namespace = false;
				}
			}
			else if (Find(Current, &Current_IDS) != nullptr) {
				//for multi char based aliases.
				if (Find(Current_Complex_Name, &Current_IDS)->first == MANGLER::VARIABLE) {
					//when a new variable starts appearing we want to push the previus into the function-
					//parameters string.
					if (Current_Variable != "") {
						Parenthesis.push_back(Current_Variable);
						Current_Variable = "";
					}
					Current = "";
					if (Current_PreFix != "")
						Current_Variable = Current_PreFix + " ";
					Current_Variable += Find(Current_Complex_Name, &Current_IDS)->second + " ";
				}
				else if (Find(Current_Complex_Name, &Current_IDS)->first == MANGLER::POSTFIX) {

					Current = "";
					Current_Variable += Find(Current_Complex_Name, &Current_IDS)->second + " ";
				}
				else if (Find(Current_Complex_Name, &Current_IDS)->first == MANGLER::PREFIX) {
					if (Current_Variable != "") {
						Parenthesis.push_back(Current_Variable);
						Current_Variable = "";
					}

					Current = "";

					Current_PreFix += Find(Current_Complex_Name, &Current_IDS)->second + " ";
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
				for (int j = i + (int)tmp.size(); (j < (size + i + (int)tmp.size())) && j < (int)raw.size(); j++) {
					name += (char)raw[j];
				}
				if (Namespace) {
					Scope_Path.push_back(name);
				}
				else if (Func_Name) {
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
				i += size + (int)tmp.size() - 1;
			}
		}
		if (Current_Variable != "") {
			Parenthesis.push_back(Current_Variable);
		}
	}
	//else if (raw[0] == '_' && raw[1] == 'E') {
	//	STD = "evie";
	//}
	else if (raw[0] == '_' && raw[1] == 'V') {
		STD = "vivid";
		vector<pair<string, pair<int, string>>>& Current_IDS = *Find_STD_List(STD);
		for (int i = 2; i < raw.size(); i++) {
			Current = raw[i];
			Current_Complex_Name += raw[i];
			//for char based aliases.
			if (Find(Current, &Current_IDS) != nullptr) {
				if (Find(Current, &Current_IDS)->first == MANGLER::VARIABLE) {
					//when a new variable starts appearing we want to push the previus into the function-
					//parameters string.
					if (Current_Variable != "") {
						if (Return_Type_Section) {
							Return_Type += " " + Current_Variable;
							Current_Variable = "";
							Current_PreFix = "";
						}
						else {
							Parenthesis.push_back(Current_Variable);
							Current_Variable = "";
							Current_PreFix = "";
						}
					}
					Current_Complex_Name = "";
					if (Current_PreFix != "")
						Current_Variable = Current_PreFix + " ";
					Current_Variable += Find(Current, &Current_IDS)->second + " ";
				}
				else if (Find(Current, &Current_IDS)->first == MANGLER::POSTFIX) {
					Current_Variable += Find(Current, &Current_IDS)->second + " ";
					Current_Complex_Name = "";
				}
				else if (Find(Current, &Current_IDS)->first == MANGLER::PREFIX) {
					if (Current_Variable != "")
						Parenthesis.push_back(Current_Variable);
					Current_PreFix += Find(Current, &Current_IDS)->second + " ";
					Current_Complex_Name = "";
					Current_Variable = "";
				}
				else if (Find(Current, &Current_IDS)->first == MANGLER::CLASS && Current_Complex_Name.size() == 1) {
					Namespace = true;
					if (Functoin_Name_Is_Before_End_Of_Namespace)
						Func_Name = false;
				}
				else if (Find(Current, &Current_IDS)->first == MANGLER::END_CLASS && Current_Complex_Name.size() == 1) {
					Namespace = false;
				}
			}
			else if (Find(Current, &Current_IDS) == nullptr && Current_Complex_Name.size() > 1 && Find(Current_Complex_Name, &Current_IDS) != nullptr) {
				//for multi char based aliases.
				if (Find(Current_Complex_Name, &Current_IDS)->first == MANGLER::VARIABLE) {
					//when a new variable starts appearing we want to push the previus into the function-
					//parameters string.
					if (Current_Variable != "") {
						Parenthesis.push_back(Current_Variable);
						Current_Variable = "";
					}
					Current = "";
					if (Current_PreFix != "")
						Current_Variable = Current_PreFix + " ";
					Current_Variable += Find(Current_Complex_Name, &Current_IDS)->second + " ";
				}
				else if (Find(Current_Complex_Name, &Current_IDS)->first == MANGLER::POSTFIX) {

					Current = "";
					Current_Variable += Find(Current_Complex_Name, &Current_IDS)->second + " ";
				}
				else if (Find(Current_Complex_Name, &Current_IDS)->first == MANGLER::PREFIX) {
					if (Current_Variable != "") {
						Parenthesis.push_back(Current_Variable);
						Current_Variable = "";
					}

					Current = "";

					Current_PreFix += Find(Current_Complex_Name, &Current_IDS)->second + " ";
				}
				else if (Find(Current_Complex_Name, &Current_IDS)->first == MANGLER::RETURN) {
					//_rPh -> ptr char xxxx(xxxx)
					Return_Type_Section = true;
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
				for (int j = i + (int)tmp.size(); (j < (size + i + (int)tmp.size())) && j < (int)raw.size(); j++) {
					name += (char)raw[j];
				}
				if (Namespace) {
					Scope_Path.push_back(name);
				}
				else if (Func_Name) {
					Function = name;
					Func_Name = false;
				}
				else if (Return_Type_Section) {
					Return_Type += " " + name;
				}
				else {
					//class based parameters.
					if (Current_Variable != "") {
						Parenthesis.push_back(Current_Variable);
						Current_Variable = "";
					}

					Current_Variable = Current_PreFix + " " + name;
				}
				i += size + (int)tmp.size() - 1;
			}
			//else if (Current_Variable != "") {
			//	Parenthesis.push_back(Current_Variable);
			//}
		}
		if (Current_Variable != "") {
			if (Return_Type_Section)
				Return_Type += " " + Current_Variable;
			else
				Parenthesis.push_back(Current_Variable);
		}
		if (Return_Type != "")
			PreFix = "";
	}
	else {
		//this lauches when no call type is identifyed.
		Function = raw;
	}

	//if the return type only has ptr then add 'type' keyword for template returning
	if (Return_Type == "ptr")
		Return_Type = "type ptr";


	string Result = Return_Type + " " + STD + " ";

	if (Scope_Path.size() > 0 && Functoin_Name_Is_Before_End_Of_Namespace) {
		Function = Scope_Path.back();
		Scope_Path.pop_back();
	}

	for (auto s : Scope_Path)
		Result += s + ".";
	
	Result += Function + "( ";


	for (int i = 0; i < ((int)Parenthesis.size()) - 1; i++) {
		Result += Parenthesis[i] + ", ";
	}
	if (Parenthesis.size() > 0)
		Result += Parenthesis.back();
	Result += ")";
	return PreFix + Result;
}

vector<string> Classes;

string MANGLER::Mangle(Node* raw, string Force_Complex)
{
	string Result = "";

	if ((raw->is("vivid") != -1) || (raw->Scope->is("vivid") != -1) || Force_Complex == "vivid") {

		string STD = "vivid";
		if (raw->is(FUNCTION_NODE) || raw->is(IMPORT) || raw->is(PROTOTYPE)) {
			Classes.clear();
			Result = "_V";

			if (raw->Scope->is(CLASS_NODE) && raw->Scope->Name != "GLOBAL_SCOPE") {
				Result += "N";

				for (auto i : raw->Get_Scope_Path())
					Result += to_string(i->Name.size()) + i->Name;

				Result += to_string(raw->Name.size()) + raw->Name;

				Result += "E";
			}
			else if (raw->Fetcher != nullptr) {
				Result += "N";

				for (auto i : raw->Get_All_Fetchers())
					Result += to_string(i->Name.size()) + i->Name;


				Result += to_string(raw->Name.size()) + raw->Name;

				Result += "E";
			}
			else
				Result += to_string(raw->Name.size()) + raw->Name;


			if (raw->Parameters.size() < 1)
				Result += "v";

			for (auto i : raw->Parameters) {
				Result += Mangle(i, "vivid");
			}

			bool Mark_Return_Type = false;
			if (raw->Inheritted.size() > 0)
				for (auto i : raw->Inheritted) {
					if (Lexer::GetComponent(i).is(Flags::KEYWORD_COMPONENT)) {
						if (i == "ptr")
							Mark_Return_Type = true;
					}
					else
						Mark_Return_Type = true;
				}

			if (Mark_Return_Type)
				Result += "_r";

			for (auto i : raw->Inheritted) {
				if (Lexer::GetComponent(i).is(Flags::KEYWORD_COMPONENT)) {
					if (i == "ptr")
						Result += Get_Key(i, STD);
				}
				else if (Get_Key(i, STD) != "")
					Result += Get_Key(i, STD);
				else
					Result += to_string(i.size()) + i;
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
				return p + Get_Key(raw->Name, STD);
			}
			else {
				if (Find_Classes(raw->Name) != -1) {
					stringstream stream;
					stream << hex << Find_Classes(raw->Name);
					r = "S" + string(stream.str()) + "_";
				}
				else
					r = to_string(raw->Name.size()) + raw->Name;
				return r;
			}
		}
		else if (raw->is(OBJECT_DEFINTION_NODE) || raw->is(OBJECT_NODE) || raw->is(PARAMETER_NODE)) {
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
					throw::runtime_error("Exporting multi inheritted variables is not yet supported.");
				}
			}
			if (Is_Template(raw)) {
				//uugabuuga?
				Result = p + "t";
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
	else if ((raw->is("evie") != -1) || (raw->Scope->is("evie") != -1)){
		//if the function call uses the Evie standard.
	}
	else if ((raw->is("plain") != -1) || (raw->Scope->is("plain") != -1)) {
		//generic name labels for normal .
		Result = raw->Name;
	}
	else /*((raw->is("cpp") != -1) || (raw->Scope->is("cpp") != -1) || Force_Complex == "cpp")*/ {
		//if the function call uses the C standard.
		//_import_func_cpp_internal_print__char__int to
		//_Z14internal_printPci
		if (raw->is(FUNCTION_NODE) || raw->is(IMPORT) || raw->is(PROTOTYPE)) {
			Classes.clear();
			Result = "_Z";

			if (raw->Scope->is(CLASS_NODE) && raw->Scope->Name != "GLOBAL_SCOPE") {
				Result += "N";

				for (auto i : raw->Get_Scope_Path())
					Result += to_string(i->Name.size()) + i->Name;

				Result += to_string(raw->Name.size()) + raw->Name;

				Result += "E";
			}
			else if (raw->Fetcher != nullptr) {
				Result += "N";

				for (auto i : raw->Get_All_Fetchers())
					Result += to_string(i->Name.size()) + i->Name;


				Result += to_string(raw->Name.size()) + raw->Name;

				Result += "E";
			}
			else
				Result += to_string(raw->Name.size()) + raw->Name;


			if (raw->Parameters.size() < 1)
				Result += "v";

			for (auto i : raw->Parameters) {
				Result += Mangle(i, "cpp");
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
				if (Find_Classes(raw->Name) != -1) {
					stringstream stream;
					stream << hex << Find_Classes(raw->Name);
					r = "S" + string(stream.str()) + "_";
				}
				else
					r = to_string(raw->Name.size()) + raw->Name;
				return r;
			}
		}
		else if (raw->is(OBJECT_DEFINTION_NODE) || raw->is(OBJECT_NODE) || raw->is(PARAMETER_NODE)) {
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
					throw::runtime_error("Exporting multi inheritted variables is not yet supported.");
				}
			}
			if (Is_Template(raw)) {
				//uugabuuga?
				Result = p + "t";
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
	return Result;
}

string MANGLER::Get_Function_Name(string func)
{	//int ptr Start_Test()
	int Paranthesis_Index = func.find_first_of('(');
	int Name_Index = func.substr(0, Paranthesis_Index).find_last_of(" ") + 1;
	return func.substr(Name_Index, Paranthesis_Index - Name_Index);
}

bool MANGLER::Is_Base_Type(Node* n)
{
	if (n->is(NUMBER_NODE) || n->is(OPERATOR_NODE) || n->is(ASSIGN_OPERATOR_NODE) || n->is(CONDITION_OPERATOR_NODE) || n->is(BIT_OPERATOR_NODE) || n->is(ARRAY_NODE) || n->is(CALL_NODE))
		return false;
	bool Result = true;
	for (auto i : n->Childs) {
		if (i->Name == "size" && i->is("const") != -1)
			continue;
		else if (i->Name == "format" && i->is("const") != -1)
			continue;
		Result = false;	//because base types do not have any other member other than the Size.
		break;
	}
	
	for (auto i : n->Inheritted) {
		if (Lexer::GetComponents(i)[0].is(Flags::KEYWORD_COMPONENT))
			continue;
		Result = false;	//because base types do not inherit other classes, only features.
		break;
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
		if (!Is_Base_Type(n->Find(i, n->Scope)))
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

int MANGLER::Find_Classes(string s)
{
	for (int i = 0; i < Classes.size(); i++)
		if (Classes[i] == s)
			return i;
	Classes.push_back(s);
	return -1;
}

void MANGLER::Add_ID(string Lang, pair<string, pair<int, string>> id) {
	if (Find_STD_List(Lang) == nullptr) {
		IDS.push_back(pair<string, vector<pair<string, pair<int, string>>>>());
		IDS.back().first = Lang;
	}

	if (Find(id.first, Find_STD_List(Lang)) != nullptr) {
		cout << "Warning: ID " << id.first << " already exist's" << endl;
		return;
	}
	else
		Find_STD_List(Lang)->push_back(id);
}

string MANGLER::Get_Key(string Val, string Lang)
{
	if (!Lexer::GetComponent(Val).is(Flags::KEYWORD_COMPONENT))
		if (Is_Base_Type(Global_Scope->Find(Val))) {
			string New_Val = to_string(Global_Scope->Find(Val)->Size) + " " + Global_Scope->Find(Val)->Format;
			Val = New_Val;
		}

	for (auto i : *Find_STD_List(Lang)) {
		if (i.second.second == Val)
			return i.first;
	}
	return "";
}

vector<pair<string, pair<int, string>>>* MANGLER::Find_STD_List(string Lang)
{
	for (auto& i : IDS) {
		if (i.first == Lang)
			return &i.second;
	}
	return nullptr;
}

pair<int, string>* MANGLER::Find(string Key, vector<pair<string, pair<int, string>>>* Current_IDS)
{
	for (auto& i : *Current_IDS)
		if (i.first == Key)
			return &i.second;

	return nullptr;
}


