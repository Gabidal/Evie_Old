#include <string>
#include <vector>

#include "Usr.h"
#include "../../H/Lexer/Position.h"
#include "../../H/Lexer/Lexer.h"
#include "../../H/Lexer/Component.h"

using namespace std;
extern Usr* sys;

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

class Proxy {
public:
	vector<Component> Input;

	Document_Request_Type Type = Document_Request_Type::NONE;
	string Word = "";
	string Uri = "";
	Position Location = Position();

	Proxy(string raw) {
		//this function transforms the raw string data into a Proxy data class.
		Input = Lexer::GetComponents(raw);

		Factory();
	}
	void Factory();

	int Parse_Num(int i);
	string Parse_String(int i);
	Position Parse_Position(int i);
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

#ifdef _WIN32
#include <WinSock2.h>

Proxy* UDP_Server::Receive() {
	int Error = 0;
	unsigned int Size = 0;

	//recieve the upcoming file size
	Error = recv(Socket, (char*)&Size, sizeof(Size), 0);

	vector<char> Buffer = vector<char>(Size);

	//this recieves the file content
	Error = recv(Socket, Buffer.data(), Buffer.size(), 0);

	Proxy* Result = new Proxy(string(Buffer.data()));

	if (Error <= 0)
		return nullptr;
	else
		return Result;
}
	
void UDP_Server::Send(char* Data, int Length) {

}

UDP_Server::UDP_Server() {
	sockaddr_in local;

	//Start the socket interface from windows
	WSAData data;
	WSAStartup(MAKEWORD(2, 2), &data);

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr("localhost");
	local.sin_port = 0; // let OS decide

	// create the socket
	Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

UDP_Server::~UDP_Server() {
	closesocket(Socket); 
}

#else

#endif


class Service
{
public:
	Document_Request_Type Type;
	string Uri = "";
	string Document = "";
	Position Location = Position();

	Service() {

	}
};