#include "../../H/Docker/Docker.h"
#include "../../H/Parser/Parser.h"

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
	//iterate every map ID in Translators map
	for (auto i : Translators) {
		if (Priority_Type == "txt")
			break;
		if (strncmp(Buffer, i.first.c_str(), i.first.size()) == 0) {
			i.second();
			return;
		}
	}
	TXT_Analyzer();
	return;
}

vector<Component> Docker::Get_Header()
{
	string Name_No_Extension = "";
	int i = (int)FileName.find_last_of('.');
	if (i != -1)
		Name_No_Extension = FileName.substr(0, (size_t)i);;
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
		Docker d(s, Working_Dir, "txt", Defined_Types);
		if (d.Output.size() > 0)
			return d.Output;
	}
	cout << "Error: Cannot open Header for " << FileName << ". Make shure your header file is same name as the lib/dll/obj." << endl;
	vector<Component> null;
	return null;
}

vector<Token*> Docker::Get_Parsed_Include_File(vector<Component> In)
{
	Parser P;
	P.Input = In;
	P.Defined_Keywords = Defined_Types;
	P.Factory();
	if (!(P.Output.size() > 0))
		cout << "Warning: Header File is empty!" << endl;
	return P.Output;
}

void Docker::Separate_Identification_Patterns(vector<Token*> Tokens)
{
	//try to find operattor that contains rightsided 
	//string for regexing and left side for type info
	for (Token* i : Tokens) {
		if (i->is(_Operator_) && i->Right_Side_Token->is(_String_) && (i->Left_Side_Token->is("generic") || i->Left_Side_Token->is("loyal"))) {
			Types.push_back({ i->Left_Side_Token->Types.at(0), i->Right_Side_Token->Name.substr(1, i->Right_Side_Token->Name.size() - 2) });
		}
	}
}

vector<string> Docker::Get_Elements(Section s, uint8_t* buffer)
{

	return vector<string>();
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
	for (auto i : symbols) {

	}
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
}

void Docker::ELF_Analyzer()
{
	Separate_Identification_Patterns(Get_Parsed_Include_File(Get_Header()));
	//open & read the bin file
	vector<unsigned char> File_Buffer = Get_Char_Buffer_From_File(FileName, Working_Dir);
	Section Function_Section = ELF::Find_Section(File_Buffer.data(), ".dynstr");
	vector<pair<string, string>> Result = Get_Names_Of(Function_Section);
	return;
}
