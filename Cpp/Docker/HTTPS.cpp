#include "../../H/Docker/HTTPS.h"
#include "../../H/UI/Usr.h"

extern Usr* sys;

string HTTPS::File_Name;

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

	if (sys->Info.HOST_OS == "win32") {
		Double_Command_Mark = " && ";
	}

	//check if the Remote folder exists
	bool Repo_Folder = false;
	for (auto i : DOCKER::Get_File_List(DOCKER::Working_Dir)) {
		if (i == Remote_Dir)
			Repo_Folder = true;
	}

	if (Repo_Folder == false) {
		cout << "Error: folder " << DOCKER::Working_Dir << Remote_Dir << " does not exist!" << endl;
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

	string Command = "cd " + DOCKER::Working_Dir + Remote_Dir + Info[4] + Double_Command_Mark + "git pull \"" + URL + "\"";

	if (New_Repo) {
		Command = "cd " + DOCKER::Working_Dir + Remote_Dir + Double_Command_Mark + "git clone \"" + URL + "\"";
	}
	system(Command.c_str());

	//now we have the repo, next we need to know if we want to build the whole folder or just get a single file.


	return;
}
