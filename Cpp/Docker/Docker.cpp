#include "../../H/Docker/Docker.h"

vector<string> DOCKER::Libs;
vector<string> DOCKER::Assembly_Source_File;
vector<string> DOCKER::FileName;
string DOCKER::Working_Dir = "";
vector<string> DOCKER::Priority_Type; 
map<string, vector<string>> DOCKER::Output;
//map<ID, function ID>
vector<pair<string, void (*)(vector<string>&)>> DOCKER::Translators;
void (*DOCKER::Default)(vector<string>&) = nullptr;

void DOCKER::Start_Analyzer()
{
	//https http ftp ftps 
	if (Default == nullptr) {
		cout << "Error: The default translator is missing!" << endl;
		return;
	}
	
	char Buffer[16];
	//read Max_ID size into a buffer
	for (int i = 0; i < 16; i++) {
		if (!(i > FileName.back().size()))
			Buffer[i] = FileName.back().c_str()[i];
	}
	//for not overlapping wrong file type into lexer
	bool Wrong_Type = false;
	//iterate every map ID in Translators map
	for (auto i : Translators) {
		if (strncmp(Buffer, i.first.c_str(), i.first.size()) == 0) {
			Wrong_Type = false;
			if (Priority_Type.back() == "txt") {
				Wrong_Type = true;
				continue;
			}
			i.second(Output[FileName.back()]);
			//sys->Info.Libs.push_back(Working_Dir + FileName);
			return;
		}
	}
	if (Wrong_Type) {
		//cout << "Warning: No specific header file for " << FileName << "." << endl;
		return;
	}
	bool Try_Local = true;
	for (auto i : Output) {
		if (i.second.size() > 0)
			Try_Local = false;
	}
	if (Try_Local) {
		FileName.back() = DOCKER::Update_Working_Dir(FileName.back());
		//if everything fails to check out it means,
		//that it is a txt file and thus call the lexer for that purpose.
		ifstream file(Working_Dir + FileName.back());
		//safe check
		//read Max_ID size into a buffer
		file.read(Buffer, 16);
		//for not overlapping wrong file type into lexer
		bool Wrong_Type = false;
		//iterate every map ID in Translators map
		for (auto i : Translators) {
			if (strncmp(Buffer, i.first.c_str(), i.first.size()) == 0) {
				Wrong_Type = false;
				if (Priority_Type.back() == "txt") {
					Wrong_Type = true;
					continue;
				}
				i.second(Output[FileName.back()]);
				//sys->Info.Libs.push_back(Working_Dir + FileName);
				return;
			}
		}
		if (Wrong_Type) {
			//cout << "Warning: No specific header file for " << FileName << "." << endl;
			return;
		}
		Default(Output[FileName.back()]);
	}
	return;
}

vector<string> DOCKER::Get_Header(string File_Name)
{
	string Name_No_Extension = "";
	int i = (int)File_Name.find_last_of('.');
	if (i != -1)
		Name_No_Extension = File_Name.substr(0, (size_t)i);
	else
		Name_No_Extension = File_Name;
	vector<string> Files;
	//collect all filenames in the working dir
	for (auto& p : filesystem::directory_iterator(Working_Dir))
	{
		string file_name = p.path().filename().string();
		if (file_name.find(Name_No_Extension) == 0)
			if (file_name != File_Name)
				Files.push_back(file_name);
	}
	//now iterate the files with Docker within the Priority type of txt.
	for (string s : Files) {
		Docker d(s, "txt");
		if (DOCKER::Output[s].size() > 0)
			return DOCKER::Output[s];
	}
	vector<string> null;
	return null;
}

vector<pair<string, string>>  DOCKER::Separate_Identification_Patterns(vector<string> Tokens)
{
	vector<pair<string, string>> Types;
	//try to find operattor that contains rightsided 
	//string for regexing and left side for type info
	for (int i = 0; i < Tokens.size(); i++) {
		if (Tokens[i] == "=" && Tokens[i + 1][0] == '"') {
			Types.push_back({ Tokens[i - 2], Tokens[i + 1].substr(1, Tokens[i + 1].size() - 2) });
			Tokens.erase(Tokens.begin() + i - 2, Tokens.begin() + i + 2);
			i--;
		}
	}
	//gahther the remaining tokens for parser.
	DOCKER::Append(Output[FileName.back()], Tokens);
	return Types;
}

vector<unsigned char> DOCKER::Get_Char_Buffer_From_File(string FN, string WD)
{
	ifstream inFile(WD + FN, ios_base::binary);
	if (!inFile.is_open()) {
		cout << "Error: Cannot open file!" << endl;
		return vector<unsigned char>();
	}
	inFile.seekg(0, ios_base::end);
	size_t length = inFile.tellg();
	inFile.seekg(0, ios_base::beg);

	vector<unsigned char> buffer;
	buffer.reserve(length);
	copy(istreambuf_iterator<char>(inFile),
		istreambuf_iterator<char>(),
		back_inserter(buffer));
	inFile.close();
	return buffer;
}

//		    name, type
vector<string> DOCKER::Get_Names_Of(Section area, vector<pair<string, string>> Types)
{
	for (int i = 0; i < area.size; i++) {
		if (area.start[i] == '\0')
			area.start[i] = '?';
	}
	string Input((char*)area.start, area.size);
	vector<string> Result;
	for (auto i : Types) {
		smatch matches;
		regex Pattern(i.second);
		int Previus_Size = Input.size();
		while (regex_search(Input, matches, Pattern)) {
			Result.push_back(i.first + matches.str());
			Input = matches.prefix().str() + matches.suffix().str();
			if (Previus_Size == Input.size()) {
				cout << "Error: Regex string " << i.second << " looped infinitely!" << endl;
				break;
			}
			Previus_Size = Input.size();
		}
		//if (regex_search(Input, matches, Pattern))
		//	for (auto j: matches)
		//		Result.push_back({ j.str(), i.first });
	}
	return Result;
}

Section DOCKER::Get_Section_From_String(string& text)
{
	return Section{ (uint8_t*)text.c_str(), text.size() };
}

string DOCKER::ReplaceAll(string str, const string& from, const string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

void DOCKER::Add_Translator(string id, void (*f)(vector<string>&)) {
	Translators.push_back({ id, f });
}

void DOCKER::Set_Default_Translator(void (*f)(vector<string>&)) {
	Default = f;
}

string DOCKER::Get_File_Extension(string raw) {
	string Name_No_Extension = "";
	int i = (int)raw.find_last_of('.');
	if (i != -1)
		Name_No_Extension = raw.substr(0, (size_t)i);
	else
		Name_No_Extension = raw;
	return Name_No_Extension;
}

string DOCKER::Update_Working_Dir(string File_Name)
{
	int i = (int)File_Name.find_last_of('/');
	if (i != -1)
	{
		Working_Dir += File_Name.substr(0, (size_t)i + 1);
		return File_Name.substr((size_t)i + 1);
	}
	return File_Name;
}

string DOCKER::Update_Working_Dir(string File_Name, string& dir)
{
	int i = (int)File_Name.find_last_of('/');
	if (i != -1)
	{
		dir += File_Name.substr(0, (size_t)i + 1);
		return File_Name.substr((size_t)i + 1);
	}
	return File_Name;
}