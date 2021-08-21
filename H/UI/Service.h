#include <string>
#include <vector>
#include <thread>

#include "Usr.h"
#include "../../H/Lexer/Position.h"
#include "../../H/Lexer/Lexer.h"
#include "../../H/Lexer/Component.h"
#include "../../H/Nodes/Node.h"
#include "../../H/UI/Safe.h"

using namespace std;
extern Usr* sys;
extern vector<Observation> Notices;

int Sensitivity = 50; //the higher the value is the lower the sens is.

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

enum class Completion_Type {
	NAME,
	PARAMETERS,
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

	Proxy(string raw) {
		Notices.clear();

		//this function transforms the raw string data into a Proxy data class.
		Input = Lexer::GetComponents(raw);

		Factory();
	}
	void Factory();

	int Parse_Num(int i);
	string Parse_String(int i);
	Position Parse_Position(int i);

	string Find_Location_Of_Uri();
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

	UDP_Server();
	~UDP_Server();
};

class Service
{
public:
	UDP_Server Code_Completion_Handle = UDP_Server();
	string Working_Dir = "";
	Node* Multifile_AST = new Node(CLASS_NODE, new Position());
	Node* Singlefile_AST = new Node(CLASS_NODE, new Position());
	vector<Node*> Output;

	vector<Node*> Cache;

	Service() {
		Singlefile_AST->Scope = Multifile_AST;

		//Recieve the 
		Working_Dir = Code_Completion_Handle.Receive()->Find_Location_Of_Uri();
		
		//send the system generated port number to stdout, for VSC to read it.
		cout << Code_Completion_Handle.Port << endl;
	}

	void Factory();

	void Handle_Auto_Completion(Proxy* i);
	void Determine_Completion_Type(Proxy* cursor);
	Node* Find_Cursor_From_AST(Cursor* c);

	Cursor* Search(int Absolute, vector<Component> Raw);
	Cursor* Search_Absolute(int Line, int Character, string Raw);
	int Calculate_Absolute_Position(int Line, int Character, string Raw);

	vector<Component*> Linearise(vector<Component>& Tree);
	int Percentage_Compare(string X, string Y);
};