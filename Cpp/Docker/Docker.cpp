#include "../../H/Docker/Docker.h"
#include "../../H/UI/Safe.h"
#include "../../H/UI/Usr.h"

vector<string> DOCKER::Libs;
vector<string> DOCKER::Assembly_Source_File;
vector<string> DOCKER::FileName;
//			Directive changing FileName, directive.
vector<pair<string, string>> DOCKER::Working_Dir;
vector<string> DOCKER::Priority_Type; 
//TODO: make own implemitation of STD::MAP for vivid
map<string, vector<string>> DOCKER::Output;
//vector<ID, function ID>
vector<pair<Location, pair<string, void (*)(vector<string>&)>>> DOCKER::Translators;
void (*DOCKER::Default)(vector<string>&) = nullptr;
vector<string> DOCKER::Included_Files;
vector<bool> DOCKER::Is_Local;
vector<string>(*DOCKER::Slicer)(string);
bool DOCKER::WORKING_DIR_IS_ABSOLUTE = false;
char* DOCKER::Buffer = nullptr;
long DOCKER::Buffer_Size = 0;

extern Usr* sys;

vector<string> DOCKER::Default_ASM_Header_Data = {
	"func local = \"global\\ +([A-Za-z0-9_@]+)\"",
	"func local = \".global\\ +([A-Za-z0-9_@]+)\"",
	"func local = \"export\\ +([A-Za-z0-9_@]+)\"",
	//func local = "global\ +([A-Za-z0-9_@]+)"
};

vector<string> DOCKER::Default_Header_Data = {
	"loyal std = \"_(\\w * @*) * \"\n",
	"func Generic = \"[a-zA-Z0-9]+\""
};

void DOCKER::Start_Analyzer(char* buffer, long Buffer_Size)
{
	//no need to if this.
	DOCKER::Buffer = buffer;
	DOCKER::Buffer_Size = Buffer_Size;

	Is_Local.push_back(false);
	//https http ftp ftps 
	if (Default == nullptr) {
		Report(Observation(ERROR, "The default translator is missing!", Position()));
		return;
	}

	//file type  calculation.
	int Dot_Location = FileName.back().find_last_of('.');
	string File_Type = FileName.back().substr(Dot_Location + 1);
	
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
		if (i.first == Location::Header) {
			if (strncmp(Buffer, i.second.first.c_str(), i.second.first.size()) == 0) {
				Wrong_Type = false;
				if (Priority_Type.back() == "txt") {
					Wrong_Type = true;
					continue;
				}
				i.second.second(Output[FileName.back()]);
				//sys->Info.Libs.push_back(Working_Dir + FileName);
				return;
			}
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
		Is_Local.back() = true;
		FileName.back() = DOCKER::Update_Working_Dir(FileName.back());
		//if everything fails to check out it means,
		//that it is a txt file and thus call the lexer for that purpose.
		ifstream file(Working_Dir.back().second + FileName.back());
		//safe check
		//read Max_ID size into a buffer
		file.read(Buffer, 16);

		//for not overlapping wrong file type into lexer
		Wrong_Type = false;

		//iterate every map ID in Translators map
		for (auto i : Translators) {
			if (i.first == Location::Header) {
				if (strncmp(Buffer, i.second.first.c_str(), i.second.first.size()) == 0) {
					Wrong_Type = false;
					if (Priority_Type.back() == "txt") {
						Wrong_Type = true;
						continue;
					}
					i.second.second(Output[FileName.back()]);
					//sys->Info.Libs.push_back(Working_Dir + FileName);
					return;
				}
			}
			//check if the file name type is same as the translator filter
			else if (i.second.first == File_Type) {
				i.second.second(Output[FileName.back()]);

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
	vector<string> Result;
	string Name_No_Extension = "";
	int i = (int)File_Name.find_last_of('.');
	if (i != -1)
		Name_No_Extension = File_Name.substr(0, (size_t)i);
	else
		Name_No_Extension = File_Name;
	vector<string> Files;
	//collect all filenames in the working dir
	for (auto& p : filesystem::directory_iterator(Working_Dir.back().second))
	{
		string file_name = p.path().filename().string();
		if (file_name.find(Name_No_Extension) == 0)
			if (file_name != File_Name)
				Files.push_back(file_name);
	}
	//now iterate the files with Docker within the Priority type of txt.
	for (string s : Files) {
		Docker d(s, "txt");
		if (DOCKER::Output[s].size() > 0) {
			Result = DOCKER::Output[s];
			DOCKER::Output.erase(s);
		}
	}
	return Result;
}

vector<pair<string, string>>  DOCKER::Separate_Identification_Patterns(vector<string> list)
{
	vector<pair<string, string>> Types;
	vector<string> Tokens;
	for (auto i : list)
		DOCKER::Append(Tokens, DOCKER::Slicer(i));
	//try to find operattor that contains rightsided 
	//string for regexing and left side for type info
	for (int i = 0; i < Tokens.size(); i++) {
		if (Tokens[i] == "=" && Tokens[(size_t)i + 1][0] == '"') {
			Types.push_back({ Tokens[(size_t)i - 2], Tokens[(size_t)i + 1].substr(1, Tokens[(size_t)i + 1].size() - 2) });
			Tokens.erase(Tokens.begin() + i - 2, Tokens.begin() + i + 2);
			i--;
		}
	}
	Tokens.erase(remove_if(Tokens.begin(), Tokens.end(), [](string s) {return s == "\n"; }), Tokens.end());
	//gahther the remaining tokens for parser.
	//DOCKER::Append(Output[FileName.back()], Tokens);
	return Types;
}

vector<unsigned char> DOCKER::Get_Char_Buffer_From_File(string FN, string WD)
{
	ifstream inFile(WD + FN, ios_base::binary);
	if (!inFile.is_open()) {
		Report(Observation(ERROR, "Cannot open file!", Position()));
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
vector<pair<string, string>> DOCKER::Get_Names_Of(string Input, vector<pair<string, string>> Types)
{
	vector<pair<string, string>> Result;
	for (auto i : Types) {
		smatch matches;
		regex Pattern(i.second);
		int Previus_Size = (int)Input.size();
		while (regex_search(Input, matches, Pattern)) {
			Result.push_back({ i.first, matches.str() });
			Input = matches.prefix().str() + matches.suffix().str();
			if (Previus_Size == (int)Input.size()) {
				Report(Observation(ERROR, "Regex string " + i.second + " looped infinitely!", Position()));
				break;
			}
			Previus_Size = (int)Input.size();
		}
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

void DOCKER::Add_Translator(Location filter_location, string id, void (*f)(vector<string>&)) {
	Translators.push_back({ filter_location, { id, f } });
}

void DOCKER::Set_Default_Translator(void (*f)(vector<string>&)) {
	Default = f;
}

string DOCKER::Get_File_Extension(string raw) {
	string Name_No_Extension = "";
	int i = (int)raw.find_last_of('.');
	if (i != -1)
		Name_No_Extension = raw.substr((size_t)i + 1, raw.size());
	else
		Name_No_Extension = raw;
	return Name_No_Extension;
}

string DOCKER::Update_Working_Dir(string File_Name)
{
	//Main.e
	//int i = (int)File_Name.find_last_of('/');
	string Previous_Dir = "";

	if (!Working_Dir.empty())
		Previous_Dir = Working_Dir.back().second;

	if (WORKING_DIR_IS_ABSOLUTE)
		Previous_Dir = "";

	bool Is_Absolute_Path = false;

	// Check if the file path if absolute
	if (sys->Info.OS == "win"){
		if (File_Name.size() > 1)
			if (File_Name[1] == ':')
				Is_Absolute_Path = true;
	}
	else {
		// uses unix
		if (File_Name.size() > 0)
			if (File_Name[0] == '/')
				Is_Absolute_Path = true;
	}

	string New_Dir = "";
	string remainder = "";

	if (Is_Absolute_Path){
		Previous_Dir = "";
	}

	remainder = Update_Working_Dir(File_Name, New_Dir);


	Working_Dir.push_back({Previous_Dir + File_Name , Previous_Dir + New_Dir });

	return remainder;
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

vector<string> DOCKER::Get_File_List(string Dir, bool Contain_Dir_Names)
{
	vector<string> Files;
	//collect all filenames in the working dir

	string Add_Dir = "";

	if (Contain_Dir_Names){
		string Ends_With_Slash = Dir.substr(Dir.size() - 1, 1) == "/" ? "" : "/";
		
		Add_Dir = Dir + Ends_With_Slash;
	}

	for (auto& p : filesystem::directory_iterator(Dir)){

		try{
			// Check if the p is a dir or a file
			if (filesystem::is_directory(p.path()))
				continue;
		}
		catch(...){ continue; }

		string file_name = p.path().filename().string();
		Files.push_back(Add_Dir + file_name);
	}
	return Files;
}

vector<string> DOCKER::Chop_Chop(string raw, char skip)
{
	vector<string> Result;
	string Current = "";
	for (auto i : raw) {
		if (i == skip) {
			if (Current.size() > 0)
				Result.push_back(Current);
			Current = "";
		}
		else
			Current += i;
	}
	if (Current != "")
		Result.push_back(Current);
	return Result;
}

string DOCKER::Remove(string raw, char id, int cut)
{
	string Result = "";
	int current = 0;
	for (auto i : raw) {
		if (cut == current)
			break;
		if (i == id)
			current++;
		Result += i;
	}

	return Result;
}

bool DOCKER::Is_Folder(string path)
{
	vector<string> Files;
	//collect all filenames in the working dir
	if (filesystem::is_directory(path)) {
		return true;
	}
	return false;
}

bool DOCKER::Is_Same_File(string first, string second)
{
	string tmp = "";
	string JustNameF = DOCKER::Update_Working_Dir(first, tmp);
	char* BufferF = Read_Bin_File(JustNameF).first;
	string JustNameS = DOCKER::Update_Working_Dir(second, tmp);
	char* BufferS = Read_Bin_File(JustNameS).first;

	if (JustNameF != JustNameS)
		return false;


	string F(BufferF);
	string S(BufferS);

	if (F.size() != S.size())
		return false;


	if (memcmp(BufferF, BufferS, S.size()) != 0)
		return false;

	return true;
}

pair<char*, long long> DOCKER::Read_Bin_File(string fileName)
{
	ifstream file(DOCKER::Working_Dir.back().second + fileName, std::ios::binary);
	file.seekg(0, ios_base::end);
	long long size = file.tellg();
	char* Buffer = new char[size+1];
	file.seekg(0, ios_base::beg);
	file.read(Buffer, size);
	Buffer[size] = '\0';
	file.close();
	return {Buffer, size};
}

string DOCKER::Find(string File_Name)
{
	string Result = "";

	vector<string> Locations;

	//try check if the env are already cached for us.
	string Cache = Open_File(sys->Info.Evie_Location + ".Chached_Env_Paths.txt");
	//transform into a vector of paths.
	//"abc//",
	//"cbd//",
	//...
	vector<string> Chached_Paths;
	for (auto i : Lexer::GetComponents(Cache)) {
		Locations.push_back(i.Value.substr(1, i.Value.size() - 2));
		Chached_Paths.push_back(i.Value.substr(1, i.Value.size() - 2));
	}

	Locations.push_back(sys->Info.Evie_Location);

	for (auto i : DOCKER::Get_System_Paths())
		Locations.push_back(i);

	for (auto i : Locations) {
		try {
			for (auto p : filesystem::directory_iterator(i))
			{
				filesystem::path File_Path = p.path();
				if (!DOCKER::Is_Folder(File_Path.string()))
					if (File_Path.filename().string() == File_Name) {
						//find recursively in the Evie folder location
						//return sys->Info.Evie_Location;
						bool Found = false;
						for (auto j : Chached_Paths)
							if (j == File_Path.remove_filename().string())
								Found = true;
						if (!Found)
							Write_File(sys->Info.Evie_Location + ".Chached_Env_Paths.txt", "\"" + File_Path.remove_filename().string() + "\"\n");
						return File_Path.string();
					}
					else
						continue;

				string Folder = DOCKER::Find(File_Name, p);
				if (Folder != "")
					return Folder;
			}
		}
		catch (...) {
			continue;
		}
	}
	return "";
}

string DOCKER::Find(string File_Name, filesystem::directory_entry Folder)
{
	for (auto p : filesystem::directory_iterator(Folder))
	{
		filesystem::path File_Path = p.path();
		if (!DOCKER::Is_Folder(File_Path.string()))
			if (File_Path.filename().string() == File_Name)
				return Folder.path().string();
			else
				continue;

		string Folder = DOCKER::Find(File_Name, p);
		if (Folder != "")
			return Folder;
	}
	return "";
}

vector<string> DOCKER::Get_System_Paths()
{
	char Path_Seperator = ';';
	if (sys->Info.OS == "unix")
		Path_Seperator = ':';

	string Result = "";

	const char* Path_Type = "Path";
	if (sys->Info.OS == "unix")
		Path_Type = "PATH";

	char* Path = getenv(Path_Type);
	if (Path == nullptr) {
		throw::runtime_error("Cannot get environment variable '" + (string)Path_Type + "'!");
	}
	string List = string(Path);

	vector<string> Paths;
	string tmp = "";
	for (auto i : List) {
		if (i == '\\')
			i = '/';
		if (i == Path_Seperator) {
			if (tmp == "")
				continue;
			Paths.push_back(tmp);
			tmp = "";
		}
		else
			tmp += i;
	}
	if (tmp != "")
		Paths.push_back(tmp);

	return Paths;
}

string DOCKER::Get_File_Path(string file_name){
	// extracts the file path from the file name, and returns the path.
	string Result = "";

	int i = (int)file_name.find_last_of('/');

	if (i != -1)
		Result = file_name.substr(0, (size_t)i + 1);

	return DOCKER::Sanitize_File_Path(Result);
}

string DOCKER::Open_File(string File_Name)
{
	fstream file(File_Name, std::ios::in | std::ios::out | std::ios::app | std::ios::binary);

	file.seekg(0, ios_base::end);
	long long size = file.tellg();
	char* Buffer = new char[size];
	file.seekg(0, ios_base::beg);
	file.read(Buffer, size);
	file.close();

	return string(Buffer, size);
}

void DOCKER::Write_File(string File_Name, string Buffer)
{
	string File_Remains = Open_File(File_Name);

	std::ofstream ofs(File_Name, ios::binary);
	ofs << File_Remains + Buffer;
	ofs.close();
}

void DOCKER::Clear_File(string File_Name)
{
	std::ofstream ofs(File_Name, ios::binary);
	ofs << "";
	ofs.close();
}

int DOCKER::Initialize_Number(string raw)
{
	int Actual_Size = 0;
	for (; Actual_Size < raw.size(); Actual_Size++)
		if (raw[Actual_Size] == ' ')
			break;

	char* Result = new char[Actual_Size];

	memcpy(Result, raw.c_str(), Actual_Size);

	return atoi(Result);
}

vector<string>& DOCKER::Append(vector<string>& d, vector<pair<string, string>> s) {
	for (int i = 0; i < s.size(); i++) {
		string r = s[i].first + " " + s[i].second;
		d.push_back(r);
	}
	return d;
}

DOCKER::Function_Pointter DOCKER::Get_Translator(vector<unsigned char>& Buffer){
	//iterate every map ID in Translators map
	for (auto i : Translators) {
		if (i.first == Location::Header) {
			if (strncmp((char*)Buffer.data(), i.second.first.c_str(), i.second.first.size()) == 0) {
				return i.second.second;
			}
		}
	}
	
	return nullptr;
}

string DOCKER::Sanitize_File_Path(string path){
	// Here we will sanitize the string with various checks and replacements.
	string Result = path;

	// First check is to turn the windows style \\ to /.
	for (int i = 0; i < Result.size(); i++) {
		if (Result[i] == '\\')
			Result[i] = '/';
	}


	return Result;
}
