#include "../../H/UI/Service.h"
#include "../../H/Parser/Parser.h"
#include "../../H/Docker/Docker.h"
#include "../../H/PreProsessor/PreProsessor.h"
#include "../../H/Parser/PostProsessor.h"

#include <math.h>

double Sensitivity = 50.0 / 100.0; //the higher the value is the lower the sens is.

extern vector<Observation> Notices;
extern string* FileName;
extern vector<Node*> Find_Trace;

Proxy::Proxy(string raw) {
	Notices.clear();

	Clean(raw);

	//this function transforms the raw string data into a Proxy data class.
	vector<Component> Tmp = Lexer::GetComponents(raw);

	Input = Tmp[0].Components;

	//construct the source code
	for (int i = 1; i < Tmp.size(); i++)
		Word += Tmp[i].Value.substr(1, Tmp[i].Value.size() - 2);

	Factory();
}

void Proxy::Factory() {
	for (int i = 0; i < Input.size(); i++) {
		Parse_Num(i);
		Parse_String(i);
		Parse_Position(i);
	}
}

void Proxy::Parse_Num(int i) {
	//"Label name": 123
	if (i + 2 >= Input.size())
		return;

	if (!Input[i + 2].is(Flags::NUMBER_COMPONENT))
		return;

	Type = (Document_Request_Type)atoi(Input[i + 2].Value.c_str());
}

void Proxy::Parse_String(int& i) {
	//"Label name": "ABC"
	if (i + 2 >= Input.size())
		return;

	if (!Input[i].is(Flags::STRING_COMPONENT))
		return;

	if (Input[i].Value != "\"Uri\"")
		return;

	if (!Input[i + 2].is(Flags::STRING_COMPONENT))
		return;

	if (Uri == "") {
		Uri = Input[i + 2].Value;
		Uri = Uri.substr(1, Uri.size() - 2);
		Uri = Find_Location_Of_Uri();
	}

	Input.erase(Input.begin() + i);
	Input.erase(Input.begin() + i);
	Input.erase(Input.begin() + i);

	i -= 3;
}

void Proxy::Parse_Position(int i) {
	//"Label Name": {
	//	"Member1": Value,
	//	"Member2": Value2,
	//	"member3": Value3,
	//}
	if (i + 2 >= Input.size())
		return;

	if (!Input[i + 2].is(Flags::PAREHTHESIS_COMPONENT))
		return;

	for (int j = 0; j < Input[i + 2].Components.size(); j++) {
		if (!Input[i + 2].Components[j].is(Flags::NUMBER_COMPONENT))
			continue;

		if (j - 1 < 1)
			continue;

		if (Input[i + 2].Components[j - 1].Value != "-")
			continue;

		Input[i + 2].Components.erase(Input[i + 2].Components.begin() + j - 1);
		Input[i + 2].Components[j - 1].Value = to_string(atoi(Input[i + 2].Components[j - 1].Value.c_str()) * -1);
	}

	//here we get from the paranthesis that resides in index i + 2
	//the components, every component is same as the ValueX above
	//"Member name": ValueX,
	Location = Position(
		atoi(Input[i + 2].Components[2].Value.c_str()),
		atoi(Input[i + 2].Components[6].Value.c_str()),
		atoi(Input[i + 2].Components[10].Value.c_str()),
		atoi(Input[i + 2].Components[14].Value.c_str())
	);
}

string Proxy::Find_Location_Of_Uri()
{
	vector<string> Exess_Headers = {
		"file://",
		"untitled:",
	};
	
	//we dont like vsc file headers.
	for (auto i : Exess_Headers) {
		if (Uri.starts_with(i))
			Uri = Uri.substr(i.size());
	}

	Uri.erase(Uri.begin());
	Uri[0] = toupper(Uri[0]);

	//letus makus newus replaSUS.
	for (int i = 0; i < Uri.size(); i++) {
		if (strncmp(&Uri[i], "%3A", 3) == 0) {
			Uri.erase(Uri.begin() + i);
			Uri.erase(Uri.begin() + i);

			Uri[i] = ':';
			break;
		}
	}

	return Uri;
}

void Proxy::Clean(string& raw)
{
	for (int i = raw.size() - 1; i > 0; i--) {
		if (raw[i] != 'n' && raw[i] != 'r' && raw[i] != 't' && raw[i] != '\'' && raw[i] != '\"')
			continue;

		if (raw[i - 1] != '\\')
			continue;

		if (i - 2 < 1 || raw[i - 2] == '\\')
			continue;


		switch (raw[i])
		{
		case 'n':
			raw[i - 1] = '\n';
			break;
		case 'r':
			raw[i - 1] = '\r';
			break;
		case 't':
			raw[i - 1] = '\t';
			break;
		case '\'':
			raw[i - 1] = '\'';
			break;
		case '\"':
			raw[i - 1] = '\"';
			break;
		}

		raw.erase(raw.begin() + i);
	}
}

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#define ERROR (MSG_Type)1

Proxy* UDP_Server::Receive() {
	int Error = 0;
	unsigned int Size = 0;
	int Mega_Byte = 1000000;

	//recieve the upcoming file size
	Error = recv(Socket, (char*)&Size, sizeof(Size), 0);

	if (Size < 1 || Size > Mega_Byte * 100)
		Report(Observation(ERROR, "Received message size is incorrect: '" + to_string(Size) + "B'."));

	vector<char> Buffer = vector<char>(Size);

	//this recieves the file content
	Error = recv(Socket, Buffer.data(), Buffer.size(), 0);

	Proxy* Result = new Proxy(string(Buffer.data(), Size));

	if (Error <= 0)
		return nullptr;
	else
		return Result;
}

void UDP_Server::Send(char* Data, int Length) {
	int Error = 0;

	//send the upcoming file size
	//Error = send(Socket, (char*)&Length, sizeof(Length), 0);

	//this sends the file content
	Error = send(Socket, Data, Length, 0);

	if (Error <= 0) {
		//we could stop the service here
	}
}

void UDP_Server::Send(MSG_Type Wellfare, vector<Node*> MSG)
{
	string Result = "{\"Status\": " + to_string(Wellfare) + ",\"Elements\": \"[";

	for (auto i : MSG) {
		Result += "\\\"" +  i->Name + "\\\",";
	}

	Result = Result.substr(0, Result.size() - 1);

	Result += "]\"}";

	Send(Result);
}

UDP_Server::UDP_Server() {
	WSADATA wsadata = WSADATA();
	WSAStartup(MAKEWORD(4, 4), &wsadata);

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
		Report(Observation(ERROR, "Invalid socket" + to_string(WSAGetLastError())));

	sockaddr_in bind_address = { 0 };
	bind_address.sin_family = AF_INET;
	//bind_address.sin_addr.s_addr = inet_addr("127.0.0.1");

	int Error = inet_pton(AF_INET, "localhost", &bind_address.sin_addr.s_addr);

	bind_address.sin_port = htons(Port);

	Error = ::bind(Socket, (sockaddr*)&bind_address, (int)sizeof(sockaddr_in));

	if (Error < 0)
		Report(Observation(ERROR, "Invalid socket" + to_string(WSAGetLastError())));

	int length = sizeof(sockaddr_in);
	if (getsockname(Socket, (sockaddr*)&bind_address, &length) < 0)
		Report(Observation(ERROR, "Invalid socket" + to_string(WSAGetLastError())));

	Port = bind_address.sin_port;

	cout << htons(Port) << endl;

	if (listen(Socket, 5) < 0)
		Report(Observation(ERROR, "Invalid socket" + to_string(WSAGetLastError())));

	sockaddr_in client_address = { 0 };
	length = sizeof(sockaddr);
	auto client = accept(Socket, (sockaddr*)&client_address, (int*)&length);

	closesocket(Socket);

	Socket = client;

	if (client == INVALID_SOCKET)
		Report(Observation(ERROR, "Invalid socket" + to_string(WSAGetLastError())));
}

UDP_Server::~UDP_Server() {
	closesocket(Socket);
}

#else

#endif

void Code_Analyzer(string Working_Dir) {

}

void Service::Factory()
{
	//Let the more complex multifile analysis to compute,
	//meanwhile we do our mundane autocompleting tasks in main thread.
	thread Analyze_Thread = thread(Code_Analyzer, Working_Dir);

	//Letus loopatus infinitus
	while (true) {
		Output.clear();

		//wait for the next instruction from VSC
		Proxy* Handle = Code_Completion_Handle.Receive();

		Handle_Auto_Completion(Handle);

		Code_Completion_Handle.Send(MSG_Type::SUCCESS, Output);
	}
}

void Service::Handle_Auto_Completion(Proxy* proxy)
{
	if (proxy->Type != Document_Request_Type::COMPLETIONS)
		return;
	//try to generate the AST and try to lacte the Position of the cursor from the AST.
	try {

		//this stops from the new source code touching the real AST but it can still find it if needed.
		//It is like a read only
		MANGLER::IDS.clear();
		DOCKER::Working_Dir.clear();
		DOCKER::Included_Files.clear();
		DOCKER::Assembly_Source_File.clear();
		Singlefile_AST->Clean();

		DOCKER::FileName.push_back(proxy->Uri);
		FileName = new string(DOCKER::FileName.back());
		DOCKER::Update_Working_Dir(*FileName);

		vector<Component> Input = Lexer::GetComponents(proxy->Word);

		PreProsessor Preprosessor(Input);
		Preprosessor.Factory();

		Parser parser = Parser(Singlefile_AST);
		parser.Input = Input;
		parser.Factory();

		PostProsessor postprosessor(Singlefile_AST, parser.Input);

		DOCKER::FileName.pop_back();
		//The parser automatically saves the new AST buided into the AST variable.

		//This function chooses which type of completion we must use in this case.
		Determine_Completion_Type(proxy);
	}
	catch (exception) {
		//Report(Observation(ERROR, "Cannot parse the code", proxy->Location));
	}
}

void Service::Determine_Completion_Type(Proxy* cursor)
{
	Cursor* C = Search_Absolute(cursor->Location.GetLine(), cursor->Location.GetCharacter(), cursor->Word, {});
	Node * Location = Find_Cursor_From_AST(C);

	if (Location) {
		if (Location->Has({ OBJECT_NODE, OBJECT_DEFINTION_NODE })) {
			for (auto i : Location->Scope->Defined) {
				Output.push_back(i);
			}
		}
		//a->int
		else if (Location->is(NODE_CASTER)) {
			//find the right side as an class type
			for (auto i : Location->Get_Scope_As(CLASS_NODE, { "static" }, Location)->Defined)
				if (i->is(CLASS_NODE))
					Output.push_back(i);
		}
		//a.x
		else if (Location->Name == ".") {
			for (auto i : Location->Find(Location->Left, Location)->Defined)
				Output.push_back(i);
		}
	}
	//if (C->Current->is(Flags::KEYWORD_COMPONENT)) {
		for (auto i : Lexer::Keywords)
			//if (Percentage_Compare(i, C->Current->Value) > Sensitivity)
				Output.push_back(new Node(KEYWORD_NODE, i, &C->Current->Location));
	//}
}

Node* Service::Find_Cursor_From_AST(Cursor* c)
{
	Node* Result = nullptr;

	Find_Trace.clear();

	Result = Singlefile_AST->Find(c->Current->Location);

	if (!Result && c->Previus.size() > 0) {
		Find_Trace.clear();
		Result = Singlefile_AST->Find(c->Previus.back()->Location);
	}

	if (!Result && c->Next.size() > 0) {
		Find_Trace.clear();
		Result = Singlefile_AST->Find(c->Next.back()->Location);
	}

	return Result;
}

//Returns fixed location of the start of the word that the cursor resides in.
Cursor* Service::Search(int Absolute, vector<Component>* Raw)
{

	Cursor* Result = new Cursor();

	int i = 0;

	vector<Component*> Linearised_Raw = Linearise(*Raw);

	for (i = 0; i < Linearised_Raw.size() && Linearised_Raw[i]->Location.GetAbsolute() < Absolute; i++);

	if (Linearised_Raw[i]->is(Flags::END_COMPONENT))
		i--;

	for (; i > 0 && Linearised_Raw[i]->Value == "\n"; i--);

	try {

		if (i - 1 >= 0)
			Result->Previus.push_back(Linearised_Raw[i - 1]);
		if (i + 1 < Linearised_Raw.size())
			Result->Next.push_back(Linearised_Raw[i + 1]);

		Result->Current = Linearised_Raw[i];

		return Result;
	}
	catch (exception) {
		//now the 'Result' index points to the next word start address.
		//this means that the cursor position is in the 'Result' - 1 location.

		Report(Observation(ERROR, "Cursor out of bouds", Position()));
	}
}

Cursor* Service::Search_Absolute(int Line, int Character, string Source, vector<Component>* Components)
{
	int Absolute = Calculate_Absolute_Position(Line, Character, Source);

	if (Components == nullptr || Components->size() == 0)
		Components = new vector<Component>(Lexer::GetComponents(Source));

	return Search(Absolute, Components);
}

int Service::Calculate_Absolute_Position(int Line, int Character, string Raw)
{
	int Result = 0;

	//make the VSC line and character into friendly types.
	int Current_Line = 1;
	int Current_Character = 1;

	Line++;
	Character++;

	for (Result = 0; Result < Raw.size(); Result++) {
		if (Current_Line == Line && Current_Character == Character)
			return Result;

		if (Raw[Result] == '\n') {
			Current_Line++;
			//new line new character counts
			Current_Character = 1;
		}
		else
			Current_Character++;
	}
}

vector<Component*> Service::Linearise(vector<Component>& Tree)
{
	vector<Component*> Result;

	for (auto &i : Tree) {
		if (i.is(Flags::PAREHTHESIS_COMPONENT)) {
			vector<Component*> Tmp = Linearise(i.Components);
			Result.insert(Result.end(), Tmp.begin(), Tmp.end());
		}
		else {
			Result.push_back(&i);
		}
	}

	return Result;
}

double Service::Percentage_Compare(string X, string Y)
{
	double Result = 0; //0%
	for (int i = 0; i < min(X.size(), Y.size()); i++) {
		if (X[i] == Y[i])
			Result += 1; //+ 1%
	}

	return round(Result / max(X.size(), Y.size()));
}
