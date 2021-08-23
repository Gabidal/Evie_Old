#include "../../H/UI/Service.h"
#include "../../H/Parser/Parser.h"

int Sensitivity = 50; //the higher the value is the lower the sens is.

extern vector<Observation> Notices;

Proxy::Proxy(string raw) {
	Notices.clear();

	//this function transforms the raw string data into a Proxy data class.
	Input = Lexer::GetComponents(raw);

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

void Proxy::Parse_String(int i) {
	//"Label name": "ABC"
	if (i + 2 >= Input.size())
		return;

	if (!Input[i + 2].is(Flags::STRING_COMPONENT))
		return;

	if (Word == "")
		Word = Input[i + 2].Value;
	else
		Uri = Input[i + 2].Value;
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

	//letus makus newus replaSUS.
	for (int i = 0; i < Uri.size(); i++) {
		if (strncmp(&Uri[i], "%3A", 3)) {
			Uri.erase(Uri.begin() + i);
			Uri.erase(Uri.begin() + i);

			Uri[i] = ':';
		}
	}

	return Uri;
}

#ifdef _WIN32
#include <WinSock2.h>
#define ERROR (MSG_Type)1

Proxy* UDP_Server::Receive() {
	int Error = 0;
	unsigned int Size = 0;

	sockaddr Sender;

	int Size_Of_Sender = sizeof(Sender);

	//recieve the upcoming file size
	Error = recvfrom(Socket, (char*)&Size, sizeof(Size), 0, &Sender, &Size_Of_Sender);

	vector<char> Buffer = vector<char>(Size);

	//this recieves the file content
	Error = recvfrom(Socket, Buffer.data(), Buffer.size(), 0, &Sender, &Size_Of_Sender);

	Proxy* Result = new Proxy(string(Buffer.data()));

	if (Error <= 0)
		return nullptr;
	else
		return Result;
}

void UDP_Server::Send(char* Data, int Length) {
	int Error = 0;

	//send the upcoming file size
	Error = send(Socket, (char*)&Length, sizeof(Length), 0);

	//this sends the file content
	Error = send(Socket, Data, Length, 0);

	if (Error <= 0) {
		//we could stop the service here
	}
}

void UDP_Server::Send(MSG_Type Wellfare, vector<Node*> MSG)
{
	string Result = "Wellfare: " + to_string(Wellfare) + "\n[";

	for (auto i : MSG) {
		Result += i->Name + ",\n";
	}

	Result += "\n]";

	Send(Result);
}

UDP_Server::UDP_Server() {
	sockaddr_in local;

	//Start the socket interface from windows
	WSAData data;
	WSAStartup(MAKEWORD(2, 2), &data);

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr("127.0.0.1");
	local.sin_port = 1111; // let OS decide

	// create the socket
	Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	int Result = bind(Socket, (sockaddr*)&local, sizeof(local));

	int Length = sizeof(local);

	getsockname(Socket, (sockaddr*)&local, &Length);

	int Error = WSAGetLastError();

	Port = local.sin_port;
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
		//Remove the \" from start and end of the string Word.
		string Source_Code = proxy->Word.substr(1, proxy->Word.size() - 2);

		proxy->Word = Source_Code;

		vector<Component> Components = Lexer::GetComponents(Source_Code);

		//this stops from the new source code touching the real AST but it can still find it if needed.
		//It is like a read only
		Singlefile_AST->Clean();

		Parser parser = Parser(Singlefile_AST);
		parser.Input = Components;
		parser.Factory();
		//The parser automatically saves the new AST buided into the AST variable.
	
		//Add new definitions to the real AST
		for (auto i : Singlefile_AST->Defined) {
			bool Is_Defined = false;

			for (auto j : Multifile_AST->Defined) {
				if (j->Name == i->Name)
					if (j->Get_Inheritted() == i->Get_Inheritted()) {

						if (i->is(FUNCTION_NODE) && j->is(FUNCTION_NODE)) {
							if (i->Parameters.size() == j->Parameters.size()) {

								for (int p = 0; p < i->Parameters.size(); p++)
									if (i->Parameters[p]->Get_Inheritted() != j->Parameters[p]->Get_Inheritted())
										goto Next;
								Is_Defined = true;
							}
							else
								goto Next;
						}
						else
							Is_Defined = true;
					}
			Next:;
			}
			if (!Is_Defined) {
				Multifile_AST->Defined.push_back(i);
			}
		}

		//This function chooses which type of completion we must use in this case.
		Determine_Completion_Type(proxy);
	}
	catch (exception) {
		Report(Observation(ERROR, "Cannot parse the code", proxy->Location));
	}
}

void Service::Determine_Completion_Type(Proxy* cursor)
{
	Cursor* C = Search_Absolute(cursor->Location.GetLine(), cursor->Location.GetCharacter(), cursor->Word);
	Node * Location = Find_Cursor_From_AST(C);

	if (Location) {
		for (auto i : Location->Find(Location, Location->Scope)->Defined) {
			Output.push_back(i);
		}
	}
	else if (C->Current->is(Flags::KEYWORD_COMPONENT)) {
		for (auto i : Lexer::Keywords)
			if (Percentage_Compare(i, C->Current->Value) > Sensitivity)
				Output.push_back(new Node(KEYWORD_NODE, i, &C->Current->Location));
	}
}

Node* Service::Find_Cursor_From_AST(Cursor* c)
{
	Node* Result = nullptr;

	Result = Singlefile_AST->Find(c->Current->Location);

	if (!Result && c->Previus.size() > 0)
		Result = Singlefile_AST->Find(c->Previus.back()->Location);

	if (!Result && c->Next.size() > 0)
		Result = Singlefile_AST->Find(c->Next.back()->Location);

	return Result;
}

//Returns fixed location of the start of the word that the cursor resides in.
Cursor* Service::Search(int Absolute, vector<Component> Raw)
{

	Cursor* Result = new Cursor();

	int i = 0;

	vector<Component*> Linearised_Raw = Linearise(Raw);

	for (i = 0; i < Linearised_Raw.size() && Linearised_Raw[i]->Location.GetAbsolute() <= Absolute; i++);

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

Cursor* Service::Search_Absolute(int Line, int Character, string Raw)
{
	string Source_Code = Raw.substr(1, Raw.size() - 2);
	int Absolute = Calculate_Absolute_Position(Line, Character, Raw);


	return Search(Absolute, Lexer::GetComponents(Source_Code));
}

int Service::Calculate_Absolute_Position(int Line, int Character, string Raw)
{
	int Result = 0;

	if (Raw[Result] == '\"')
		Result++;

	int Current_Line = 0;
	int Current_Character = 0;

	for (Result = 0; Result < Raw.size(); Result++) {
		if (Current_Line == Line && Current_Character == Character)
			return Result;

		if (Raw[Result] == '\n') {
			Current_Line++;
			//new line new character counts
			Current_Character = 0;
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

int Service::Percentage_Compare(string X, string Y)
{
	int Result = 0; //0%
	for (int i = 0; i < min(X.size(), Y.size()); i++) {
		if (X[i] == Y[i])
			Result++; //+ 1%
	}

	return Result;
}
