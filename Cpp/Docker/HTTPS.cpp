#include "../../H/Docker/HTTPS.h"
#include "../../H/UI/Usr.h"

extern Usr* sys;

string HTTPS::File_Name;

void HTTPS::HTTPS_Analyser(vector<string>& output)
{
	//we need to set all those remotely included libs into a subfolder
	//idk maybe Remote/??
	string URL;
	string Repo = DOCKER::Update_Working_Dir(DOCKER::FileName.back(), URL);
	string Remote_Dir = sys->Info.Repo_Dir;

	//try to see if there is already a git folder for this git repo.

}
