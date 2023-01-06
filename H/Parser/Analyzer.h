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

	void Factory();

	void Detect_Abnormal_Start_Address();
	void List_All_Exported();

	//class tools
	void Analyze_Class(Node* c);

	//Function tools
	void Calling_Count_Incrementer(Node* f, vector<Node*>& Callin_Trace);
	void Call_Algebra(Node* n);
	void Analyze_Variable_Address_Pointing(Node* v, Node* n);
	int Get_Amount(string t, Node* n);
	void Define_Sizes(Node* p);

	void Dependency_Injector(vector<Node*>& nodes);

	void Give_Global_Scope_All_Used_Functions();

	void Calculate_Address_Givers_For_Functions(Node* f);

};

#endif