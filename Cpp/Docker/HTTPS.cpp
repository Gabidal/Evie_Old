#include "../../H/Docker/HTTPS.h"

#include "../../H/UI/Usr.h"
#include "../../H/UI/Safe.h"
#define CURL_STATICLIB
#include "../../Dependencies/Curl/curl.h"
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

	//check if the Remote folder exists
	bool Repo_Folder = false;
	for (auto i : DOCKER::Get_File_List(DOCKER::Working_Dir)) {
		if (i == Remote_Dir)
			Repo_Folder = true;
	}

	if (Repo_Folder == false) {
		Report(Observation(ERROR, "folder " + DOCKER::Working_Dir + Remote_Dir + " does not exist!", Position()));
		exit(1);
	}

	bool New_Repo = true;
	//try to see if there is already a git folder for this git repo.
	for (auto i : DOCKER::Get_File_List(DOCKER::Working_Dir + Remote_Dir)) {
		//the i contains the reponame
		if (i == Info[3]) {
			New_Repo = false;
		}
	}

	if (Remote_Dir[Remote_Dir.size()] != '/')
		Remote_Dir += '/';

	string Command = "cd " + DOCKER::Working_Dir + Remote_Dir + Info[3] + Double_Command_Mark + "git pull \"" + URL + "\"";

	if (New_Repo) {
		Command = "cd " + DOCKER::Working_Dir + Remote_Dir + Double_Command_Mark + "git clone \"" + URL + "\"";
	}
	string Repo_Folder_Dest_Path;

	if (system(Command.c_str()) != 0) {
		Report(Observation(INFO, "Given URL is not git based, going into fallback mode.", Position()));
		//this URL is not a git based file repo.
		//use curl
		CURL* curl_handle;
		CURLcode res;

		MemoryStruct chunk;

		curl_handle = curl_easy_init();
		if (curl_handle) {
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
				Report(Observation(1, curl_easy_strerror(res), Position()));
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
					Report(Observation(1, curl_easy_strerror(res), Position()));
				else {
					regex expression("\"positives\": [0-9]+");
					smatch matches;
					string Buffer = chunk.memory;
					if (!regex_search(Buffer, matches, expression)) {
						Report(Observation(1, "Could not get VT report.", Position()));
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

			curl_easy_setopt(curl_handle, CURLOPT_URL, (Path + Name).c_str());
			curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
			curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
			curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

			res = curl_easy_perform(curl_handle);

			if (res != CURLE_OK) {
				Report(Observation(1, curl_easy_strerror(res), Position()));
			}
			else {
				ofstream o(DOCKER::Working_Dir + Remote_Dir + Name.c_str());
				if (!o.is_open()) {
					Report(Observation(1, "Could not save contents of " + Name, Position()));
				}
				o.write(chunk.memory, (unsigned long)chunk.size);
				o.close();
				//printf("Size: %lu\n", (unsigned long)chunk.size);
				//printf("Data: %s\n", chunk.memory);
			}
			curl_easy_cleanup(curl_handle);
			free(chunk.memory);
			Repo_Folder_Dest_Path = Remote_Dir + Name.c_str();
		}
	}
	else {
		//now we have the repo, next we need to know if we want to build the whole folder or just get a single file.
		Repo_Folder_Dest_Path = Remote_Dir;
		for (int i = 3; i < Info.size() - 1; i++) {
			Repo_Folder_Dest_Path += Info[i] + '/';
		}
		Repo_Folder_Dest_Path += Info.back();
	}

	if (DOCKER::Is_Folder(Repo_Folder_Dest_Path)) {
		//here we build it.
	}
	else {
		//char* buffer = DOCKER::Read_Bin_File(Repo_Folder_Dest_Path);
		//string str(buffer);

		//ofstream file(DOCKER::Working_Dir + Repo_Folder_Dest_Path);
		//file.write(str.c_str(), str.size());

		/*for (int i = 0; i < DOCKER::Included_Files.size(); i++) {
			if (DOCKER::Is_Same_File(DOCKER::Included_Files[i], DOCKER::Working_Dir + Repo_Folder_Dest_Path)) {
				cout << "Warnign: " << Repo_Folder_Dest_Path << " already included from \"" << URL << "\"" << endl;
				return;
			}
		}*/

		Docker D(Repo_Folder_Dest_Path);
	}

	return;
}
