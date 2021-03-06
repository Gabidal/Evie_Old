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

class Abbrev_Type {
public:
	bool ID = false;
	int TAG = -1;
	bool HAS_CHILDREN = false;
	bool CALLING_CONVENTION = false;
	bool MEMORY_LOCATION = false;
	bool START = false;
	bool END = false;
	bool STACK_FRAME_LOCATION = false;
	bool STACK_FRAME_REPRESENTIVE_REGISTER = false;
	bool MANGLED_NAME = false;
	bool NAME = false;
	bool ENCODING = false;
	bool BYTE_SIZE = false;
	bool SOURCE_FILE = false;
	bool SOURCE_LINE = false;
	bool TYPE = false;
	bool EXTERNAL = false;

	bool operator==(Abbrev_Type b) {
		return ID == b.ID &&
			TAG == b.TAG &&
			HAS_CHILDREN == b.HAS_CHILDREN &&
			MEMORY_LOCATION == b.MEMORY_LOCATION &&
			START == b.START &&
			END == b.END && 
			STACK_FRAME_LOCATION == b.STACK_FRAME_LOCATION && 
			STACK_FRAME_REPRESENTIVE_REGISTER == b.STACK_FRAME_REPRESENTIVE_REGISTER &&
			MANGLED_NAME == b.MANGLED_NAME &&
			NAME == b.NAME &&
			ENCODING == b.ENCODING &&
			BYTE_SIZE == b.BYTE_SIZE && 
			SOURCE_FILE == b.SOURCE_FILE &&
			SOURCE_LINE == b.SOURCE_LINE &&
			TYPE == b.TYPE && 
			EXTERNAL == b.EXTERNAL
			;
	}

	Abbrev_Type(Node* n);
	Abbrev_Type(){}
};

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
	void Generate_Abbrev(Abbrev_Type abbrev);
	

	void Insert_Start_End_Labels(vector<IR*>& input);
	void Insert_Line_Change_Information(vector<IR*>& input);
	void Insert_Stack_Info(vector<IR*> &Input);
private:
	vector<IR*> Debug_Abbrev;	//describes all needed debug information about the debuggable code.
	vector<IR*> Debug_Info;		//lists all needed degub information about the debuggable code.
	vector<IR*> Debug_Str;		//lists all string used in the debuggable code.
	vector<IR*> Debug_Line;		//unknown section!
	vector<IR*> File_Index;		//defines a index to every used source file
	vector<IR*> Line_Table;
	vector<pair<string, int>> Files;	//File_Name, Index representive
	vector<pair<Abbrev_Type, int>> Abbrovation_IDs;

	int Get_Index_From_File(string s);
	int Get_Abbrovation_Index(Node* n);
};

#endif