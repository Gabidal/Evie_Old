#ifndef _X86_H_
#define _X86_H_

#include <vector>
#include <string>
#include <map>

using namespace std;

#include "../Nodes/Token.h"
#include "../Nodes/IR.h"
#include "../Flags.h"
#include "../Assembler/Assembler_Types.h"

class x86_64 {
public:
	int size;
	vector<Token*> Registers;
	vector<Token*> Parameter_Registers;
	vector<IR*> Opcodes;
	vector<Token*> Utility;
	vector<Token*> Size_Identifiers;

	string Seperator;
	string Register_Pre_Fix;
	string Number_Pre_Fix;
	string Label_Post_Fix;

	unsigned short OBJ_Machine_ID;
	static inline map<unsigned char, unsigned char> MODRMS;
	void Init();

	//DEBUG
	int STACK_REPRESENTIVE_REGISTER; //RSP

	//Assembler
	static class Byte_Map* Build(IR* ir);
	static int Get_Size(class Byte_Map* input);
	static void Arrange_Encoding(vector<Token*>& Args, OPCODE_ENCODING encoding);
	static void Modify_OpCode(class Byte_Map* b);
	static vector<unsigned char> Assemble(class Byte_Map* Input);

	static bool is(unsigned char value, unsigned char mask) {
		return (value & mask) == mask;
	}
};

static constexpr unsigned char REX_DEFAULT = 0b01000000;
static constexpr unsigned char REX_W = 0b00001000;
static constexpr unsigned char REX_R = 0b00000100;
static constexpr unsigned char REX_X = 0b00000010;
static constexpr unsigned char REX_B = 0b00000001;

static constexpr unsigned char OPERAND_SIZE_OVERRIDE = 0b01100110; //0x66

static constexpr unsigned char REX_BIT_SETTED = 0b1000;

#endif