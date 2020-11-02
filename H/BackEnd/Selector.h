#ifndef _SELECTOR_H_
#define _SELECTOR_H_
#include <vector>
#include <string>

#include "../Nodes/IR.h"
#include "../Nodes/Token.h"
#include "../BackEnd/x86.h"

using namespace std;

class Register_Descriptor {
public:
	int First_Usage_Index = 0;
	int Last_Usage_Index = 0;

	string User = "";

	Register_Descriptor(int first, int last, string usr) : First_Usage_Index(first), Last_Usage_Index(last), User(usr){}
};

class Path {
	//Path is a package class containing critical information about the path of specified value.
public:
	vector<int> Intersects_Calls;
	int Parameter_Place = -1;
	int Last_Usage = 0;
};

class Variable {
public:
	string ID;
	int Size;
	Variable(string id, int s) : ID(id), Size(s){}
};

class Selector {
private:
	void Init();
	//registers
	vector<pair<Register_Descriptor*, Token*>> Registers;
	vector<vector<Token*>> Parameter_Registers;
	vector<Token*> Transform(Token* parent);

	//stack
	Node* Parent = nullptr;
	vector<Variable*> Stack;
	int Stack_Size = 0;

	//Opcodes
	vector<IR*> Opcodes;
public:
	Selector() { Init(); }
	Path* Get_Path_Info(vector<IR*> source, int i, Token* t);
	//REGISTERS:
	//											<Wanted Register description, and the register itself> , <the new user description, the user itself>,  IRs, index
	void Make_Solution_For_Crossed_Register_Usages(pair< Register_Descriptor*, Token*> Current, pair< Register_Descriptor*, Token*> New, vector<IR*>* source, int i);
	Token* Get_New_Reg(vector<IR*> *source, int i, Token* t);
	Token* Get_Register(Token* t);
	Token* Get_Register(long F, Register_Descriptor* user);
	void Allocate_Register(vector<IR*>* source, int i, Token* t);
	void Pair_Up(Token* r, Register_Descriptor* t);
	void Break_Up(Token* r);
	int Get_Numerical_Parameter_Register_Count();
	int Get_Floating_Parameter_Register_Count();

	//STACK/HEAP:
	void PUSH(Node* n);
	void PUSH(Variable* v);
	void POP(string id);
	void POP(int size);
	void POP();
	int Update_Stack_Size();


	//OPCODES:
	IR* Get_Opcode(IR* i);
	bool Check_Resource_Availability(IR* i, vector<pair<Token*, pair<int, int>>> Order);
};

#endif