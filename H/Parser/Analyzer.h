#ifndef _ANALYZER_H_
#define _ANALYZER_H_

#include "../Nodes/Node.h"
#include "../UI/Usr.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

extern Node* Global_Scope;
extern Usr* sys;

class Analyzer {
private:
	vector<Node*> Start_Of_Proccesses;
public:
	Analyzer();

	void Factory();

	void Detect_Abnormal_Start_Address();
	void List_All_Exported();

	void Calling_Count_Incrementer(Node* f);
};

#endif