#include "../../H/UI/Satellite.h"
#include "../../H/UI/Usr.h"
#include "../../H/UI/Safe.h"
#include "../../H/Docker/Docker.h"
#include "../../H/Docker/Mangler.h"
#include "../../H/Parser/Parser.h"

#include <filesystem>
#include <unordered_map>

extern Usr* sys;

void Satellite::Init_Wanted_Dependencies()
{
	if (Installation_Type == INSTALL::DEFAULT) {
		Dependecies = {
			{OS::UNIX, INTRODUCE::CONSOLE, nullptr, "git"},
			//{OS::UNIX, INTRODUCE::CONSOLE, nullptr, "libcurl4-openssl-dev"},
			{OS::UNIX, INTRODUCE::CONSOLE, &sys->Info.Assembler_Location, "as"},
			{OS::UNIX, INTRODUCE::CONSOLE, &sys->Info.Linker_Location, "ld"},

			{OS::WIN, INTRODUCE::CONSOLE, nullptr, "git"},
			//{OS::WIN, INTRODUCE::LOCAL,   nullptr, "libcurl.lib"},
		};

		if (sys->Info.Architecture == ARCHITECTURE::X86) {
			Dependecies.push_back({ OS::WIN, INTRODUCE::LOCAL, &sys->Info.Linker_Location, "x86_ld.exe" });
			Dependecies.push_back({ OS::WIN, INTRODUCE::LOCAL, &sys->Info.Assembler_Location, "x86_as.exe" });
		}
		if (sys->Info.Architecture == ARCHITECTURE::ARM) {
			Dependecies.push_back({ OS::WIN, INTRODUCE::LOCAL, &sys->Info.Linker_Location, "arm_ld.exe" });
			Dependecies.push_back({ OS::WIN, INTRODUCE::LOCAL, &sys->Info.Assembler_Location, "arm_as.exe" });
		}
	}
}

void Satellite::Factory()
{
	for (auto Medium : Dependecies) {
		//HOST_OS because in host we need to compile the source
		if (Medium.Platform == sys->Info.HOST_OS) {
			Process_Local_Dependencies(Medium);
			Process_Console_Dependencies(Medium);
		}
	}
}

// Usual location for SSS.e is: sys->Info.Repo_Dir + "/" + "SSS.e"
vector<Medium> Satellite::Read_Symbol_Source_Service(string file_name){

	// Example input: 
	/*
	"Kernel32.dll"{
    "Source"[
        "C:/"
    ]
    "Symbols"[
        "VirtualAlloc"
        "VirtualFree"
    ]
	}*/

	const string SOURCE = "Source";
	const string SYMBOLS = "Symbols";
	const string PLATFORM = "Platform";

	if (!filesystem::exists(file_name)){
		return {};
	}

	vector<Component> components = Lexer::GetComponentsFromFile(file_name);

	Node* SSS = new Node("Symbol Source Service", nullptr);
	Parser p(SSS);
	p.Input = components;
	p.Factory_SSS();

	vector<Medium> Result;

	for (auto i : SSS->Childs){
		Medium current_medium;
		current_medium.Product_ID = i->Name;
		
		if (i->Find(SOURCE))
			current_medium.Dependency_Location = new string(i->Find(SOURCE)->Name);
		if (i->Find(PLATFORM))
			current_medium.Platform = i->Find(PLATFORM)->Name;
		
		if (i->Find(SYMBOLS)){
			for (auto j : i->Find(SYMBOLS)->Childs){
				current_medium.Symbols.push_back(j->Name);
			}
		}

		Result.push_back(current_medium);
	}

}

void Satellite::Write_Symbol_Source_Service_Cache(vector<Medium> data, string file_name){
	string Result = "";

	for (auto i : data){
		Result += Quote(i.Product_ID) + "{\n";

		if (i.Dependency_Location != nullptr){
			Result += Ident(Quote("Source"), 1) + "[\n";
			Result += Ident(Quote(*i.Dependency_Location), 2) + "\n";
			Result += Ident("]\n", 1);
		}

		if (i.Platform != ""){
			Result += Ident(Quote("Platform"), 1) + "[\n";
			Result += Ident(Quote(i.Platform), 2) + "\n";
			Result += Ident("]\n", 1);
		}

		if (i.Symbols.size() > 0){
			Result += Ident(Quote("Symbols"), 1) + "[\n";

			for (auto j : i.Symbols){
				Result += Ident(Quote(j), 2) + "\n";
			}

			Result += Ident("]\n", 1);
		}

		Result += "}\n";
	}

	ofstream o(file_name);
	o << Result;
	o.close();
}

string Satellite::Ident(string src, int count){
	string Result = "";

	for (int i = 0; i < count; i++)
		Result += "\t";

	return Result + src;
}

string Satellite::Quote(string src){
	return "\"" + src + "\"";
}

void Satellite::Scraper(){
	if (!sys->Info.Use_Scraper)
		return;

	vector<Node*> Imported_Symbol_Nodes = Global_Scope->Get_all(Node_Type::IMPORT);

	if (Imported_Symbol_Nodes.size() == 0)
		return;

	bool Current_SSS_Contains_All_Needed = true;

	vector<Medium> SSS_Libs = Read_Symbol_Source_Service(sys->Info.Repo_Dir + "/" + "SSS.e");

	for (auto imported_symbols : Imported_Symbol_Nodes){
		for (auto medium : SSS_Libs){
			for (auto symbol : medium.Symbols){
				if (imported_symbols->Name == symbol)
					goto NEXT;
			}
		}

		Current_SSS_Contains_All_Needed = false;

		NEXT:;
	}

	for (auto i : SSS_Libs){
		sys->Info.Libs.push_back(i.Product_ID);
	}

	if (Current_SSS_Contains_All_Needed)
		return;

	// Since header section can contain similar functions to the childs section and namespaced inline them on use.
	// We need to remove identical functions from the imported functions list.

	std::unordered_map<string, Node*> Imported_Symbols;

	for (auto* i : Imported_Symbol_Nodes){
		Imported_Symbols[MANGLER::Mangle(i, "")] = i;
	}

	vector<string> Linkable_File_Types;

	// Now that we have only the single instance for all identical functions and the mangled names, we can just try to find the files which contains these function implementations.
	if (sys->Info.OS == "win"){
		// DLL, OBJ, LIB
		Linkable_File_Types = { "dll", "obj", "lib" };
	}
	else if (sys->Info.OS == "unix"){
		// ELF, Mach-O, PE
		Linkable_File_Types = { "elf", "mach-o", "pe" };
	}

	// Prioritize the local location and then start searching on env paths.
	vector<string> Paths = DOCKER::Get_System_Paths();
	Paths.push_back(DOCKER::Get_File_Path(sys->Info.Source_File));	// Add the current location to the list too.

	// Now put the order so that the Evie location is in priority
	reverse(Paths.begin(), Paths.end());

	vector<string> File_Names;

	for (auto dir : Paths){
		vector<string> tmp = DOCKER::Get_File_List(dir, true);
		File_Names.insert(File_Names.end(), tmp.begin(), tmp.end());
	}

	// Now remove all the files which don't end in the correct file ending.
	for (int i = 0; i < File_Names.size(); i++){
		string File_Type = File_Names[i].substr(File_Names[i].find_last_of(".") + 1);
		if (find(Linkable_File_Types.begin(), Linkable_File_Types.end(), File_Type) == Linkable_File_Types.end()){
			File_Names.erase(File_Names.begin() + i);
			i--;
		}
	}

	// Extract the function implementations from the files.
	// <File_name, Exported_Symbols>
	std::map<std::string, std::vector<std::string>> Function_Implementations;

	for (auto file_name : File_Names){
		Docker D(file_name);

		Function_Implementations.insert(DOCKER::Output.begin(), DOCKER::Output.end());

		DOCKER::Output.clear();
		DOCKER::Working_Dir.clear();
	}

	vector<string> Link_File;
	std::unordered_map<std::string, Node *> Imported_Symbols_Tmp = Imported_Symbols;

	// Now check if the exported symbols match on any of the imported functions.
	for (auto Linkable_File : Function_Implementations){
		for (auto Exported : Linkable_File.second)
			for (auto Imported : Imported_Symbols){
				if (Exported == Imported.first){

					Link_File.push_back(Linkable_File.first);

					// Also remove the imported symbol from the tmp map, so that other DLL's with same function exports wont get "mangled" heheheeee.
					Imported_Symbols_Tmp.erase(Imported.first);

					goto Skip_File;
				}
			}

		Skip_File:;
	}

	vector<Medium> New_Mediums;

	// update SSS file
	for (auto file : Link_File){
		vector<string> Symbols = Function_Implementations.at(file);

		// transform the file information into Mediums
		Medium Current;
		Current.Product_ID = file;
		Current.Symbols = Symbols;
		
		DOCKER::Header_Summary tmp = DOCKER::File_History.at(file);

		Current.Platform = tmp.OS;

		for (auto dir : DOCKER::Working_Dir){
			string tmp = "";

			if (DOCKER::Update_Working_Dir(dir.first, tmp) == file){
				Current.Dependency_Location = new string(tmp);
			}
		}

		New_Mediums.push_back(Current);
	}

	// write the Mediums into file:
	Write_Symbol_Source_Service_Cache(New_Mediums, sys->Info.Repo_Dir + "/" + "SSS.e");
		
	// Check if the link files are already added into the sys libs by the SSS
	for (auto i : Link_File){
		bool contained = false;
		for (auto j : sys->Info.Libs){
			if (j == i)
				contained = true;
		}

		if (!contained)
			sys->Info.Libs.push_back(i);
	}

	return;
}

void Satellite::Process_Local_Dependencies(Medium Medium)
{
	if (Medium.Introducer != INTRODUCE::LOCAL)
		return;

	//start the search for the dependency from Evie eecutable and downwards.
	string Path_To_Medium = DOCKER::Find(Medium.Product_ID);
	if (Path_To_Medium != "") {
		if (Medium.Dependency_Location != nullptr) {
			*Medium.Dependency_Location = Path_To_Medium;
		}
		return;	//the dependecy is there
	}

	Report(Observation(ERROR, "Dependency '" + Medium.Product_ID + "' is missing or unreachable to Evie!"));
}

void Satellite::Process_Console_Dependencies(Medium Medium)
{
	if (Medium.Introducer != INTRODUCE::CONSOLE)
		return;

	string Command;

	if (Medium.Platform == OS::WIN) {
		Command = Medium.Product_ID + " --version > $null";
	}
	else if (Medium.Platform == OS::UNIX) {
		Command = "which " + Medium.Product_ID + " > /dev/null";
	}

	int Success = system(Command.c_str());

	if (Success == 0)
		return;

	Report(Observation(ERROR, "Dependency '" + Medium.Product_ID + "' is missing or unreachable to Evie!"));
}
