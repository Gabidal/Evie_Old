#ifndef _DEBUGGENERATOR_H_
#define _DEBUGGENERATOR_H_

#include "../BackEnd/Selector.h"	//Degub Generator needs the Size identifiers from selector
#include "../Nodes/IR.h"			//Degub Generator needs to generate the sybols as a IR tokens
#include "../Nodes/Token.h"			//Degub Generator needs to generate the sybols as a IR tokens


#include <vector>
#include <string>

using namespace std;

class DebugGenerator
{
public:
	DebugGenerator();
	~DebugGenerator(){}

	void Factory();

	void Construct_Debug_Abbrev();
private:
	vector<IR*> Debug_Abbrev;	//describes all needed debug information about the debuggable code.
	vector<IR*> Debug_Info;		//lists all needed degub information about the debuggable code.
	vector<IR*> Debug_Str;		//lists all string used in the debuggable code.
	vector<IR*> Debug_Line;		//unknown section!
};

#endif