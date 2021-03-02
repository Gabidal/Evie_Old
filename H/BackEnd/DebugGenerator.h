#ifndef _DEBUGGENERATOR_H_
#define _DEBUGGENERATOR_H_

#include "../BackEnd/Selector.h"	//Degub Generator needs the Size identifiers from selector
#include "../Nodes/IR.h"			//Degub Generator needs to generate the sybols as a IR tokens
#include "../Nodes/Token.h"			//Degub Generator needs to generate the sybols as a IR tokens
#include "../Nodes/Node.h"			//Debug info for functions and variable generation.
#include "../Docker/Docker.h"		//Debug info for all used source files.
#include "../Docker/Mangler.h"

#include <vector>
#include <string>

using namespace std;

extern Node* Global_Scope;
extern Selector* selector;

class DebugGenerator
{
public:
	DebugGenerator(vector<IR*> &input);
	~DebugGenerator(){}

	void Construct_Debug_Abbrev();
	void Construct_Debug_Info();
	void Construct_Debug_String();
	void Construct_Line_Table();
	void Define_File_Index();


	void Function_Info(Node* n, int i);
	void Local_Variable_Info(Node* n);
	void Type_Info();

	void Insert_Start_End_Labels(vector<IR*>& input);
private:
	vector<IR*> Debug_Abbrev;	//describes all needed debug information about the debuggable code.
	vector<IR*> Debug_Info;		//lists all needed degub information about the debuggable code.
	vector<IR*> Debug_Str;		//lists all string used in the debuggable code.
	vector<IR*> Debug_Line;		//unknown section!
	vector<IR*> File_Index;		//defines a index to every used source file
	vector<IR*> Line_Table;
	vector<pair<string, int>> Files;	//File_Name, Index representive

	int Get_Index_From_File(string s);
};

#endif