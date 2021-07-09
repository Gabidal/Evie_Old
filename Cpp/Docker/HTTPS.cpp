#include "../../H/Docker/HTTPS.h"
#include "../../H/UI/Usr.h"
#define CURL_STATICLIB
#include "../../Dependencies/Curl/curl.h"
#include "../../H/UI/Safe.h"
#include <regex>

extern Usr* sys;

string HTTPS::File_Name;

size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)userp;

	void* ptr = realloc(mem->memory, mem->size + realsize + 1);
	if (ptr == NULL) {
		printf("error: not enough memory\n");
		return 0;
	}

	mem->memory = (char*)ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

void HTTPS::HTTPS_Analyser(vector<string>& output)
{
	//we need to set all those remotely included libs into a subfolder
	//idk maybe Remote/??
	string Path;
	string Name = DOCKER::Update_Working_Dir(DOCKER::FileName.back(), Path);
	string Remote_Dir = sys->Info.Repo_Dir;
	vector<string> Info = DOCKER::Chop_Chop(DOCKER::FileName.back(), '/');
	//[0] = https:			--method //
	//[1] = github			--interface /
	//[2] = Gabidal			--author /
	//[3] = Evie			--repo name /
	//[x > 3] = subfolders	--sub folders ../
	//[last] = cstd.e		--file/folder name
	//get URL
	string URL = DOCKER::Remove(Path, '/', 5);

	string Double_Command_Mark = " ; ";

	if (sys->Info.HOST_OS == "win") {
		Double_Command_Mark = " && ";
	}

	string Seperator = "";
	if (Remote_Dir[0] != '/' && DOCKER::Working_Dir.back().second.back() != '/')
		Seperator = '/' + Seperator;
	string Remote_Dir_Location = DOCKER::Working_Dir.back().second + Seperator + Remote_Dir;

	//check if the Remote folder exists
	bool Repo_Folder = false;
	if (DOCKER::Is_Folder(Remote_Dir_Location))
		Repo_Folder = true;

	/*for (auto i : DOCKER::Get_File_List(DOCKER::Working_Dir.back().second)) {
		if (i == Remote_Dir)
			Repo_Folder = true;
	}*/

	if (Repo_Folder == false) {
		//This could also mean that the repo folder is given as a absolute path.
		if (DOCKER::Is_Folder(Remote_Dir)) {
			Remote_Dir_Location = Remote_Dir;
			Repo_Folder = true;
			DOCKER::WORKING_DIR_IS_ABSOLUTE = true;
		}
	}

	if (Repo_Folder == false) {
		Report(Observation(WARNING, "folder " + Remote_Dir_Location + " does not exist, making a new one.", Position()));
		system(("mkdir \"" + Remote_Dir_Location + "\"").c_str());
	}

	bool New_Repo = true;
	//try to see if there is already a git folder for this git repo.
	for (auto i : DOCKER::Get_File_List(Remote_Dir_Location)) {
		//the i contains the reponame
		if (i == Info[3]) {
			New_Repo = false;
			break;
		}
	}

	if (Remote_Dir_Location[Remote_Dir_Location.size()-1] != '/')
		Remote_Dir_Location += '/';

	string Command = "cd " + Remote_Dir_Location + Info[3] + Double_Command_Mark + "git pull --quiet \"" + URL + "\"";

	if (New_Repo) {
		Command = "cd " + Remote_Dir_Location + Double_Command_Mark + "git clone --quiet \"" + URL + "\"";
	}
	string Repo_Folder_Dest_Path;

	if (system(Command.c_str()) != 0) {

		//try git stash to fix git merge.
		string Stash = "cd " + Remote_Dir_Location + Info[3] + Double_Command_Mark + "git stash --quiet ";
		system(Stash.c_str());
		
		if (system(Command.c_str()) == 0)
			goto Git_Merge_Error_Fixed;

		Report(Observation(INFO, "Given URL is not git based, going into fallback mode.", Position()));
		//this URL is not a git based file repo.
		//use curl
		CURL* curl_handle;
		CURLcode res;

		MemoryStruct chunk;

		curl_handle = curl_easy_init();
		if (curl_handle) {
			if (sys->Info.VT_API != "") {
				//use virustotal to check the url
				curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.virustotal.com/vtapi/v2/url/scan");
				curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
				curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
				curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
				curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
				string Data = "apikey=" + sys->Info.VT_API + "&url=" + (Path + Name);
				curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, Data.c_str());

				res = curl_easy_perform(curl_handle);

				if (res != CURLE_OK)
					Report(Observation(ERROR, curl_easy_strerror(res), Position()));
				else {
					curl_easy_cleanup(curl_handle);
					curl_handle = curl_easy_init();
					free(chunk.memory);
					chunk = MemoryStruct();

					curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.virustotal.com/vtapi/v2/url/report");
					curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
					curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
					curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
					curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
					string Data = "apikey=" + sys->Info.VT_API + "&resource=" + (Path + Name);
					curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, Data.c_str());

					res = curl_easy_perform(curl_handle);
					if (res != CURLE_OK)
						Report(Observation(ERROR, curl_easy_strerror(res), Position()));
					else {
						regex expression("\"positives\": [0-9]+");
						smatch matches;
						string Buffer = chunk.memory;
						if (!regex_search(Buffer, matches, expression)) {
							Report(Observation(ERROR, "Could not get VT report.", Position()));
						}

						int Positives = atoi(matches.str().substr(12).c_str());
						if (Positives > 0) {
							Report(Observation(WARNING, "Suspicious URL " + Path + Name, Position()));
						}
						//printf("Size: %lu\n", (unsigned long)chunk.size);
						//printf("Data: %s\n", chunk.memory);
					}
				}
				curl_easy_cleanup(curl_handle);
				curl_handle = curl_easy_init();
				free(chunk.memory);
				chunk = MemoryStruct();
			}
			curl_easy_setopt(curl_handle, CURLOPT_URL, (Path + Name).c_str());
			curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
			curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
			curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

			res = curl_easy_perform(curl_handle);

			if (res != CURLE_OK) {
				Report(Observation(ERROR, curl_easy_strerror(res), Position()));
			}
			else {
				ofstream o(Remote_Dir_Location + Name.c_str());
				if (!o.is_open()) {
					Report(Observation(ERROR, "Could not save contents of " + Name, Position()));
				}
				o.write(chunk.memory, (unsigned long)chunk.size);
				o.close();
				//printf("Size: %lu\n", (unsigned long)chunk.size);
				//printf("Data: %s\n", chunk.memory);
			}
			curl_easy_cleanup(curl_handle);
			free(chunk.memory);
			Repo_Folder_Dest_Path = Remote_Dir_Location + Name.c_str();
		}
	}
	else {
	Git_Merge_Error_Fixed:;
		if (Remote_Dir[Remote_Dir.size()-1] != '/')
			Remote_Dir += '/';
		//now we have the repo, next we need to know if we want to build the whole folder or just get a single file.
		Repo_Folder_Dest_Path = Remote_Dir;
		for (int i = 3; i < Info.size() - 1; i++) {
			Repo_Folder_Dest_Path += Info[i] + '/';
		}
		Repo_Folder_Dest_Path += Info.back();
	}


	bool Need_Make_Build = true;
	string File_Path = "";
	for (int i = 3; i < Info.size() - 1; i++) {
		File_Path += Info[i] + "/";
	}
	File_Path += Info[Info.size() - 1];

	string Dir = "";
	string File = DOCKER::Update_Working_Dir(File_Path, Dir);
	for (auto f : DOCKER::Get_File_List(Remote_Dir_Location + Dir))
		if (f == File)
			Need_Make_Build = false;

	if (DOCKER::Is_Folder(Repo_Folder_Dest_Path) || Need_Make_Build) {
		//we build it here.
		string Make = "";
		if (sys->Info.HOST_OS == "unix") {
			if (system("which make") != 0)
				Report(Observation((MSG_Type)1, "Is make-utility installed and visible to this program?", Position()));
			Make = "make";
		}
		else {
			if (system(".\\Dependencies\\Mingw\\make.exe -v") != 0) {
				Report(Observation((MSG_Type)1, "nmake-utility is needed to be in the same folder or in environment varibles", Position()));
			}
			Make = ".\\Dependencies\\Mingw\\make.exe";
		}
		int error = system((Make + " all").c_str());

		bool All_Argument_Made_It = false;
		if (error != 0) {
			Report(Observation((MSG_Type)1, to_string(error) + " Could not build with default argument, going into fallback mode.", Position()));
		}
		else
			for (auto f : DOCKER::Get_File_List(Remote_Dir_Location + Dir))
				if (f == File)
					All_Argument_Made_It = true;

		if (!All_Argument_Made_It)
			if (system((Make + " -B").c_str()) != 0) {
				Report(Observation((MSG_Type)1, "Make-utility build error, please fix the problems first.", Position()));
			}
		DOCKER::FileName.back() = Remote_Dir_Location + Dir + File;
		DOCKER::Output.erase(DOCKER::Output.rbegin()->first);
		Docker D(Remote_Dir_Location + Dir + File);
	}
	else {
		DOCKER::FileName.back() = Repo_Folder_Dest_Path;
		DOCKER::Output.erase(DOCKER::Output.rbegin()->first);
		Docker D(Repo_Folder_Dest_Path);
	}
	DOCKER::WORKING_DIR_IS_ABSOLUTE = false;
	return;
}
