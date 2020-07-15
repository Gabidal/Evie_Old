#include "../../H/PreProsessor/PreProsessor.h"

void PreProsessor::Factory() {
	for (int i = 0; i < Input.size(); i++)
		Include(i);
}

void PreProsessor::Include(int i)
{
	//use "file.x"
	//<summary>
	//Give it to Docker. it can handle many files
	//</summary>
	if (Input[i].Value != "use")
		return;
	if (!Input[(size_t)i+1].is(Flags::STRING_COMPONENT))
		return;

	string File_Name = Update_Working_Dir(Input[(size_t)i + 1].Value.substr(1, Input[(size_t)i + 1].Value.size() - 2));

	for (string s : Included_Files)
		if (File_Name == s)
		{
			cout << "Warning: " << Input.at((size_t)i + 1).Value << " is already included." << endl;
			Input.erase(Input.begin() + i + 1);
			Input.erase(Input.begin() + i);
			return;
		}

	Docker D(File_Name, Working_Dir);

	Input.erase(Input.begin() + i + 1);
	Input.erase(Input.begin() + i);

	Input.insert(Input.begin() + i, D.Output.begin(), D.Output.end());

	Included_Files.push_back(File_Name);
	if (i == Input.size())
		return;
	if (Input.at(i).Value == "use")
		Include(i);
}


string PreProsessor::Update_Working_Dir(string File_Name)
{
	int i = (int)File_Name.find_last_of('/');
	if (i != -1)
	{
		Working_Dir += File_Name.substr(0, (size_t)i + 1);
		return File_Name.substr((size_t)i + 1);
	}
	return File_Name;
}