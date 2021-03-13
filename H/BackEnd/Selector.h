#ifndef _SELECTOR_H_
#define _SELECTOR_H_
#include <vector>
#include <string>
#include <iostream>

#include "../Nodes/IR.h"
#include "../Nodes/Token.h"
#include "x86.h"
#include "ARM.h"

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

class Selector {
private:
	void Init();
	//tools
	bool Find(string n, Token* ast);
	bool Find(Token* n, Token* ast);
	//registers
	vector<pair<Register_Descriptor*, Token*>> Registers;
	vector<vector<Token*>> Parameter_Registers;
	vector<Token*> Transform(Token* parent);
	int Current_Parameter_Register_Index = 0;
	bool Previus_Parameter_Type_Decimal = false;
	
	//stack
	Node* Parent = nullptr;
	vector<Token*> Stack;
	int Stack_Size = 0;
	int Start_Offset = 0;

	//Opcodes
	vector<IR*> Opcodes;
	vector<Token*> Size_Identifiers;

public:
	Selector() { Init(); }
	Path* Get_Path_Info(vector<IR*> source, int i, Token* t);
	//REGISTERS:
	//											<Wanted Register description, and the register itself> , <the new user description, the user itself>,  IRs, index
	void Make_Solution_For_Crossed_Register_Usages(pair< Register_Descriptor*, Token*> Current, pair< Register_Descriptor*, Token*> New, vector<IR*>* source, int i);
	Token* Get_New_Reg(vector<IR*> *source, int i, Token* t);
	Token* Get_Right_Parameter_Register(Token* t, int parameter_index);
	void Reset_Parameter_Register_Count(IR* r);
	Token* Get_Register(Token* t);
	Token* Get_Register(long F, Register_Descriptor* user, int i, Token* t);
	int Get_Largest_Register();
	Register_Descriptor* Check_If_Smaller_Register_Is_In_Use(Token* r);
	Register_Descriptor* Check_If_Larger_Register_Is_In_Use(Token* r);
	void Allocate_Register(vector<IR*>* source, int i, Token* t);
	void Pair_Up(Token* r, Register_Descriptor* t);
	void Break_Up(Token* r);
	int Get_Numerical_Parameter_Register_Count(vector<Node*> Parameters);
	int Get_Floating_Parameter_Register_Count(vector<Node*> Parameters);
	void Clean_Register_Holders();
	vector<pair<Register_Descriptor*, Token*>> Get_Register_Type(long f);

	//STACK/HEAP:
	//void Save(Token* id, Token* v, vector<IR*>* list, int i);
	//Token* Load(string id, vector<IR*>* list, int i);
	void DeAllocate_Stack(int Amount, vector<IR*>* list, int i);
	void Allocate_Stack(int Amount, vector<IR*>* list, int i);
	int Update_Stack_Size();
	void Set_Stack_Start_Value(int v) { Start_Offset = v; }
	void Clean_Stack();

	//OPCODES:
	IR* Get_Opcode(IR* i);
	bool Check_Resource_Availability(IR* i, vector<pair<Token*, pair<int, int>>> Order);
	string Get_Size_Identifier(int s);

	//DEBUG 
	int STACK_REPRESENTIVE_REGISTER;
};

#endif