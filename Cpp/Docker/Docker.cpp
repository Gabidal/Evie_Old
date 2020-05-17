#include "../../H/Docker/Docker.h"

void Docker::Start_Analyzer()
{
	//if everything fails to check out it means,
	//that it is a txt file and thus call the lexer for that purpose.
	//function<void()> analyzer = bind(&Docker::TXT_Analyzer, this);//[this]() {TXT_Analyzer(); };
	//function<void()> analyzer = this->TXT_Analyzer;		//!!!
	ifstream file(Working_Dir + FileName);
	//safe check
	if (!file.is_open()) {
		cout << "Error: Unable to open file " << Working_Dir + FileName << endl;
		return;
	}
	//read Max_ID size into a buffer
	char Buffer[16];
	file.read(Buffer, 16);
	//for not overlapping wrong file type into lexer
	bool Wrong_Type = false;
	//iterate every map ID in Translators map
	for (auto i : Translators) {
		Wrong_Type = false;
		if (strncmp(Buffer, i.first.c_str(), i.first.size()) == 0) {
			if (Priority_Type == "txt") {
				Wrong_Type = true;
				continue;
			}
			i.second();
			return;
		}
	}
	if (Wrong_Type) {
		//cout << "Warning: No specific header file for " << FileName << "." << endl;
		return;
	}
	TXT_Analyzer();
	return;
}

vector<Component> Docker::Get_Header(string File_Name)
{
	string Name_No_Extension = "";
	int i = (int)File_Name.find_last_of('.');
	if (i != -1)
		Name_No_Extension = File_Name.substr(0, (size_t)i);;
	vector<string> Files;
	//collect all filenames in the working dir
	for (auto& p : filesystem::directory_iterator(Working_Dir))
	{
		string file_name = p.path().filename().string();
		if (file_name.find(Name_No_Extension) == 0)
			Files.push_back(file_name);
	}
	//now iterate the files with Docker within the Priority type of txt.
	for (string s : Files) {
		Docker d(s, Working_Dir, "txt");
		if (d.Output.size() > 0)
			return d.Output;
	}
	cout << "Warning: Docker didn't find suitable Header file for " << FileName << endl;
	cout << "Docker: Fallback to general header." << endl;
	vector<Component> null;
	return null;
}

void Docker::Separate_Identification_Patterns(vector<Component> Tokens)
{
	//try to find operattor that contains rightsided 
	//string for regexing and left side for type info
	for (int i = 0; i < Tokens.size(); i++) {
		if (Tokens.at(i).Value == "=" && (Tokens.at(i + 1).is(STRING_COMPONENT))) {
			Types.push_back({ Tokens.at(i - 2).Value, Tokens.at(i + 1).Value.substr(1, Tokens.at(i + 1).Value.size() - 2) });
			Tokens.erase(Tokens.begin() + i - 2, Tokens.begin() + i + 2);
			i--;
		}
	}
	//gahther the remaining tokens for parser.
	Append(Output, Tokens);
}

vector<unsigned char> Docker::Get_Char_Buffer_From_File(string FN, string WD)
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
vector<pair<string, string>> Docker::Get_Names_Of(Section area)
{
	for (int i = 0; i < area.size; i++) {
		if (area.start[i] == '\0')
			area.start[i] = '?';
	}
	string Input((char*)area.start, area.size);
	vector<pair<string, string>> Result;
	for (auto i : Types) {
		smatch matches;
		regex Pattern(i.second);
		int Previus_Size = Input.size();
		while (regex_search(Input, matches, Pattern)) {
			Result.push_back({ matches.str(), i.first });
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

void Docker::Syntax_Correcter(vector<pair<string, string>> symbols)
{
	//import loyal func [name]()()
	//import generic func [name]()()
	for (auto i : symbols) {
		Append(Output, Lexer::GetComponents("import " + i.second + " func " + i.first + "()() \n"));
	}
}

void Docker::Append(vector<Component>& Dest, vector<Component> Source)
{
	for (Component i : Source)
		Dest.push_back(i);
	return;
}

void Docker::TXT_Analyzer()
{
	Output = Lexer::GetComponentsFromFile(Working_Dir + FileName);
}

void Docker::DLL_Analyzer()
{
}

void Docker::LIB_Analyzer()
{
	vector<ObjectFile> result = LIB::ExtractAllObjectFiles(Get_Char_Buffer_From_File(FileName, Working_Dir));
}

void Docker::ELF_Analyzer()
{
	vector<Component> Header_Data = Get_Header(FileName);
	if (Header_Data.size() < 1)
		Header_Data = Get_Header("general.e");
	Separate_Identification_Patterns(Header_Data);
	//open & read the bin file
	vector<unsigned char> File_Buffer = Get_Char_Buffer_From_File(FileName, Working_Dir);
	Section Function_Section = ELF::Find_Section(File_Buffer.data(), ".dynstr");
	Syntax_Correcter(Get_Names_Of(Function_Section));
	return;
}
