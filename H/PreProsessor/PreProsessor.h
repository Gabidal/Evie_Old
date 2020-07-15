#ifndef _PREPROSESSOR_H_
#define _PREPROSESSOR_H_

#include "../Flags.h"
#include "../Lexer/Component.h"

#include "../Docker/Docker.h"

#include <vector>

using namespace std;

class PreProsessor
{
public:
	PreProsessor(vector<Component> &list) : Input(list){}
	~PreProsessor(){}
	void Factory();
	void Include(int i);
	string Update_Working_Dir(string file_and_dir);
	vector<string> Included_Files;
private:
	vector<Component> &Input;
	string Working_Dir = "";
};

#endif