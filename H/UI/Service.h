#include <string>
#include <vector>
#include <thread>
#include <mutex>

#include "Usr.h"
#include "../../H/Lexer/Position.h"
#include "../../H/Lexer/Lexer.h"
#include "../../H/Lexer/Component.h"
#include "../../H/Nodes/Node.h"
#include "../../H/UI/Safe.h"

using namespace std;
extern Usr* sys;
extern double Sensitivity;
extern Node* Global_Scope;
//extern enum MSG_Type;

class Cursor {
public:
	vector<Component*> Previus;
	Component* Current;
	vector<Component*> Next;
};

enum class Document_Request_Type
{
	NONE,
	COMPLETIONS,
	SIGNATURES,
	DIAGNOSE,
	OPEN,
	DEFINITION,
	INFORMATION,
	FIND_REFERENCES
};

enum CompletionItemKind {
	Text,
	Method,
	Function,
	Constructor,
	Field,
	Variable,
	Class,
	Interface,
	Module,
	Property,
	Unit,
	Value,
	Enum,
	Keyword,
	Snippet,
	Color,
	Reference,
	File,
	Folder,
	EnumMember,
	Constant,
	Struct,
	Event,
	Operator,
	TypeParameter,
};

class Proxy {
public:
	vector<Component> Input;

	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
	//Packet variables
	Document_Request_Type Type = Document_Request_Type::NONE;
	string Word = "";
	string Uri = "";
	Position Location = Position();
	//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

	Proxy(string raw);
	void Factory();

	void Parse_Num(int i);
	void Parse_String(int& i);
	void Parse_Position(int i);

	string Find_Location_Of_Uri();
	void Clean(string& raw);
};

class UDP_Server {
public:
	int Port = 0;
	int Socket = 0;


	Proxy* Receive();

	void Send(char* Data, int Length);

	void Send(string Data) {
		Send(Data.data(), Data.size());
	}

	void Send(MSG_Type Wellfare, vector<Node*> MSG);

	UDP_Server();
	~UDP_Server();
};

class Service
{
public:
	UDP_Server Code_Completion_Handle = UDP_Server();
	string Working_Dir = "";
	mutex Multifile_Lock; 
	Node* Singlefile_AST;// = new Node(CLASS_NODE, new Position());
	vector<Node*> Output;

	vector<Node*> Cache;

	Service() {
		Singlefile_AST = Global_Scope;

		//Recieve the working dir from the VSC
		Working_Dir = Code_Completion_Handle.Receive()->Uri;
		
		Factory();
	}

	void Factory();

	void Handle_Auto_Completion(Proxy* i);
	void Determine_Completion_Type(Proxy* cursor);
	Node* Find_Cursor_From_AST(Cursor* c);

	Cursor* Search(int Absolute, vector<Component>* Raw);
	Cursor* Search_Absolute(int Line, int Character, string Source, vector<Component>* Components);
	int Calculate_Absolute_Position(int Line, int Character, string Source);

	vector<Component*> Linearise(vector<Component>& Tree);
	double Percentage_Compare(string X, string Y);
};