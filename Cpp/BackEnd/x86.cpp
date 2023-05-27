#include "../../H/BackEnd/x86.h"
#include "../../H/UI/Usr.h"

#include "../../H/Assembler/Assembler_Types.h"
#include "../../H/Assembler/Assembler.h"

#include "../../H/UI/Safe.h"
#include "../../H/BackEnd/Selector.h"

#include <string>

using namespace std;

extern Usr* sys;
extern Selector* selector;
extern Assembler* assembler;
extern x86_64 X86_64;

void x86_64::Init()
{
	size = 8;	//64 bit arch

	long long OS_DEPENDENT_FLAG = TOKEN::NONVOLATILE;
	STACK_REPRESENTIVE_REGISTER = 87;

	OBJ_Machine_ID = 0x8664;

	if (sys->Info.OS == "unix")
		OS_DEPENDENT_FLAG = TOKEN::VOLATILE;

	Seperator = ",";
	Register_Pre_Fix = "";
	Number_Pre_Fix = "";
	Label_Post_Fix = ":";

	MODRMS = {
		{0, -1},	//NULL

		{MODRM_FLAGS::RM | MODRM_FLAGS::MEMORY, 0b00},
		{MODRM_FLAGS::RM | MODRM_FLAGS::MEMORY | MODRM_FLAGS::DISP32, 0b10},
		{MODRM_FLAGS::RM, 0b11},

		{MODRM_FLAGS::RM | MODRM_FLAGS::SIB | MODRM_FLAGS::MEMORY, 0b00},
		{MODRM_FLAGS::RM | MODRM_FLAGS::SIB | MODRM_FLAGS::MEMORY | MODRM_FLAGS::DISP32, 0b10},
		{MODRM_FLAGS::RM | MODRM_FLAGS::SIB, 0b11},
	};

	Token* AL = new Token(TOKEN::RETURNING | TOKEN::QUOTIENT, "al", 1, {}, 0b0000);
	Token* AH = new Token(TOKEN::RETURNING, "ah", 1, {}, 0b0100);
	Token* AX = new Token(TOKEN::RETURNING | TOKEN::QUOTIENT, "ax", 2, { AH, AL }, 0b0000);
	Token* EAX = new Token(TOKEN::RETURNING | TOKEN::QUOTIENT, "eax", 4, { AX }, 0b0000);
	Token* RAX = new Token(TOKEN::RETURNING | TOKEN::QUOTIENT, "rax", 8, { EAX }, 0b0000);

	Token* BL = new Token(TOKEN::NONVOLATILE, "bl", 1, {}, 0b0011);
	Token* BH = new Token(TOKEN::NONVOLATILE, "bh", 1, {}, 0b0111);
	Token* BX = new Token(TOKEN::NONVOLATILE, "bx", 2, { BH, BL }, 0b0011);
	Token* EBX = new Token(TOKEN::NONVOLATILE, "ebx", 4, { BX }, 0b0011);
	Token* RBX = new Token(TOKEN::NONVOLATILE, "rbx", 8, { EBX }, 0b0011);

	Token* CL = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "cl", 1, {}, 0b0001);
	Token* CH = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "ch", 1, {}, 0b0101);
	Token* CX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "cx", 2, { CH, CL }, 0b0001);
	Token* ECX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "ecx", 4, { CX }, 0b0001);
	Token* RCX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "rcx", 8, { ECX}, 0b0001);

	Token* DL = new Token( TOKEN::PARAMETER, "dl", 1, {}, 0b0010);
	Token* DH = new Token( TOKEN::PARAMETER, "dh", 1, {}, 0b0110);
	Token* DX = new Token( TOKEN::PARAMETER  | TOKEN::REMAINDER, "dx", 2, { DH, DL }, 0b0010);
	Token* EDX = new Token( TOKEN::PARAMETER | TOKEN::REMAINDER, "edx", 4, { DX }, 0b0010);
	Token* RDX = new Token( TOKEN::PARAMETER | TOKEN::REMAINDER, "rdx", 8, { EDX }, 0b0010);

	Token* DIL = new Token(OS_DEPENDENT_FLAG | TOKEN::UNIFORM_REGISTER, "dil", 1, {}, 0b0111);
	//Token* DIH = new Token(TOKEN::NONVOLATILE, "dih", 1, {});
	Token* DI = new Token(OS_DEPENDENT_FLAG, "di", 2, {DIL }, 0b0111);
	Token* EDI = new Token(OS_DEPENDENT_FLAG, "edi", 4, { DI }, 0b0111);
	Token* RDI = new Token(OS_DEPENDENT_FLAG, "rdi", 8, { EDI }, 0b0111);

	Token* SIL = new Token(OS_DEPENDENT_FLAG | TOKEN::UNIFORM_REGISTER, "sil", 1, {}, 0b0110);
	//Token* SIH = new Token(TOKEN::NONVOLATILE, "sih", 1, {});
	Token* SI = new Token(OS_DEPENDENT_FLAG, "si", 2, {SIL }, 0b0110);
	Token* ESI = new Token(OS_DEPENDENT_FLAG, "esi", 4, { SI }, 0b0110);
	Token* RSI = new Token(OS_DEPENDENT_FLAG, "rsi", 8, { ESI }, 0b0110);


	Token* BPL = new Token(TOKEN::NONVOLATILE | TOKEN::UNIFORM_REGISTER, "bpl", 1, {}, 0b0101);
	Token* BP = new Token(TOKEN::NONVOLATILE, "bp", 2, { BPL }, 0b0101);
	Token* EBP = new Token(TOKEN::NONVOLATILE, "ebp", 4, { BP }, 0b0101);
	Token* RBP = new Token(TOKEN::NONVOLATILE, "rbp", 8, { EBP }, 0b0101);

	Token* SPL = new Token(TOKEN::STACK_POINTTER | TOKEN::UNIFORM_REGISTER, "spl", 1, {}, 0b0100);
	Token* SP = new Token(TOKEN::STACK_POINTTER, "sp", 2, { SPL }, 0b0100);
	Token* ESP = new Token(TOKEN::STACK_POINTTER, "esp", 4, { SP }, 0b0100);
	Token* RSP = new Token(TOKEN::STACK_POINTTER, "rsp", 8, { ESP }, 0b0100);

	Token* IPL = new Token(TOKEN::POSITION_INDEPENDENT_REGISTER, "ipl", 1, {}, 0b0101);
	Token* IP = new Token(TOKEN::POSITION_INDEPENDENT_REGISTER, "ip", 2, {IPL}, 0b0101);
	Token* EIP = new Token(TOKEN::POSITION_INDEPENDENT_REGISTER, "eip", 4, { IP }, 0b0101);
	Token* RIP = new Token(TOKEN::POSITION_INDEPENDENT_REGISTER, "rip", 8, { EIP }, 0b0101);

	Token* XMM0D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::RETURNING | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm0", 4, {}, 0b0000);
	Token* XMM1D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm1", 4, {}, 0b0001);
	Token* XMM2D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm2", 4, {}, 0b0010);
	Token* XMM3D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm3", 4, {}, 0b0011);
	Token* XMM4D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm4", 4, {}, 0b0100);
	Token* XMM5D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm5", 4, {}, 0b0101);
	Token* XMM6D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm6", 4, {}, 0b0110);
	Token* XMM7D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm7", 4, {}, 0b0111);
	Token* XMM8D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm8", 4, {}, 0b1000);
	Token* XMM9D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm9", 4, {}, 0b1001);
	Token* XMM10D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xm10", 4, {}, 0b1010);
	Token* XMM11D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm11", 4, {}, 0b1011);
	Token* XMM12D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm12", 4, {}, 0b1100);
	Token* XMM13D = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm13", 4, {}, 0b1101);
	Token* XMM14D = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm14", 4, {}, 0b1110);
	Token* XMM15D = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm15", 4, {}, 0b1111);

	Token* XMM0Q = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::RETURNING | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm0", 8, {XMM0D}, 0b0000);
	Token* XMM1Q = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm1", 8, {XMM1D}, 0b0001);
	Token* XMM2Q = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm2", 8, { XMM2D }, 0b0010);
	Token* XMM3Q = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm3", 8, { XMM3D }, 0b0011);
	Token* XMM4Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm4", 8, { XMM4D }, 0b0100);
	Token* XMM5Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm5", 8, { XMM5D }, 0b0101);
	Token* XMM6Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm6", 8, { XMM6D }, 0b0110);
	Token* XMM7Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm7", 8, { XMM7D }, 0b0111);
	Token* XMM8Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm8", 8, { XMM8D }, 0b1000);
	Token* XMM9Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm9", 8, { XMM9D }, 0b1001);
	Token* XMM10Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xm10", 8, { XMM10D }, 0b1010);
	Token* XMM11Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm11", 8, { XMM11D }, 0b1011);
	Token* XMM12Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm12", 8, { XMM12D }, 0b1100);
	Token* XMM13Q = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm13", 8, { XMM13D }, 0b1101);
	Token* XMM14Q = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm14", 8, { XMM14D }, 0b1110);
	Token* XMM15Q = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm15", 8, { XMM15D }, 0b1111);

	Token* XMM0 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::RETURNING | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm0", 12, { XMM0Q }, 0b0000);
	Token* XMM1 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm1", 12, { XMM1Q }, 0b0001);
	Token* XMM2 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm2", 12, { XMM2Q }, 0b0010);
	Token* XMM3 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm3", 12, { XMM3Q }, 0b0011);
	Token* XMM4 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm4", 12, { XMM4Q }, 0b0100);
	Token* XMM5 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm5", 12, { XMM5Q }, 0b0101);
	Token* XMM6 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm6", 12, { XMM6Q }, 0b0110);
	Token* XMM7 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm7", 12, { XMM7Q }, 0b0111);
	Token* XMM8 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm8", 12, { XMM8Q }, 0b1000);
	Token* XMM9 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm9", 12, { XMM9Q }, 0b1001);
	Token* XMM10 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xm10", 12, { XMM10Q }, 0b1010);
	Token* XMM11 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm11", 12, { XMM11Q }, 0b1011);
	Token* XMM12 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm12", 12, { XMM12Q }, 0b1100);
	Token* XMM13 = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm13", 12, { XMM13Q }, 0b1101);
	Token* XMM14 = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm14", 12, { XMM14Q }, 0b1110);
	Token* XMM15 = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL | TOKEN::EXTENDED_REGISTER, "xmm15", 12, { XMM15Q }, 0b1111);

	Token* R8B = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::EXTENDED_REGISTER, "r8b", 1, {}, 0b1000);
	Token* R8W = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::EXTENDED_REGISTER, "r8w", 2, { R8B }, 0b1000);
	Token* R8D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::EXTENDED_REGISTER, "r8d", 4, { R8W }, 0b1000);
	Token* R8 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::EXTENDED_REGISTER, "r8", 8, { R8D }, 0b1000);

	Token* R9B = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::EXTENDED_REGISTER, "r9b", 1, {}, 0b1001);
	Token* R9W = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::EXTENDED_REGISTER, "r9w", 2, { R9B }, 0b1001);
	Token* R9D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::EXTENDED_REGISTER, "r9d", 4, { R9W }, 0b1001);
	Token* R9 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::EXTENDED_REGISTER, "r9", 8, { R9D }, 0b1001);

	Token* R10B = new Token(TOKEN::VOLATILE | TOKEN::EXTENDED_REGISTER, "r10b", 1, {}, 0b1010);
	Token* R10W = new Token(TOKEN::VOLATILE | TOKEN::EXTENDED_REGISTER, "r10w", 2, { R10B }, 0b1010);
	Token* R10D = new Token(TOKEN::VOLATILE | TOKEN::EXTENDED_REGISTER, "r10d", 4, { R10W }, 0b1010);
	Token* R10 = new Token(TOKEN::VOLATILE | TOKEN::EXTENDED_REGISTER , "r10", 8, { R10D }, 0b1010);

	Token* R11B = new Token(TOKEN::VOLATILE | TOKEN::EXTENDED_REGISTER, "r11b", 1, {}, 0b1011);
	Token* R11W = new Token(TOKEN::VOLATILE | TOKEN::EXTENDED_REGISTER, "r11w", 2, { R11B }, 0b1011);
	Token* R11D = new Token(TOKEN::VOLATILE | TOKEN::EXTENDED_REGISTER, "r11d", 4, { R11W }, 0b1011);
	Token* R11 = new Token(TOKEN::VOLATILE | TOKEN::EXTENDED_REGISTER , "r11", 8, { R11D }, 0b1011);

	Token* R12B = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r12b", 1, {}, 0b1100);
	Token* R12W = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r12w", 2, { R12B }, 0b1100);
	Token* R12D = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r12d", 4, { R12W }, 0b1100);
	Token* R12 = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER , "r12", 8, { R12D }, 0b1100);

	Token* R13B = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r13b", 1, {}, 0b1101);
	Token* R13W = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r13w", 2, { R13B }, 0b1101);
	Token* R13D = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r13d", 4, { R13W }, 0b1101);
	Token* R13 = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER , "r13", 8, { R13D }, 0b1101);

	Token* R14B = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r14b", 1, {}, 0b1110);
	Token* R14W = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r14w", 2, { R14B }, 0b1110);
	Token* R14D = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r14d", 4, { R14W }, 0b1110);
	Token* R14 = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER , "r14", 8, { R14D }, 0b1110);

	Token* R15B = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r15b", 1, {}, 0b1111);
	Token* R15W = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r15w", 2, { R15B }, 0b1111);
	Token* R15D = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER, "r15d", 4, { R15W }, 0b1111);
	Token* R15 = new Token(TOKEN::NONVOLATILE | TOKEN::EXTENDED_REGISTER , "r15", 8, { R15D }, 0b1111);

	if (sys->Info.OS == "win")
		Parameter_Registers = { RCX, RDX, R8, R9, XMM0, XMM1, XMM2, XMM3 };
	else
		Parameter_Registers = { RDI, RSI, RDX, RCX, R8, R9, XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6 };
	Registers = { 
		RAX, EAX, AX, AL, AH,
		RBX, EBX, BX, BL, BH,
		RCX, ECX, CX, CL, CH,
		RDX, EDX, DX, DL, DH,
		RDI, EDI, DI, DIL,
		RSI, ESI, SI, SIL,
		RBP, EBP, BP, BPL,
		RSP, ESP, SP, SPL,
		RIP, EIP, IP, IPL,
		XMM0D, XMM1D, XMM2D, XMM3D, XMM4D, XMM5D, XMM6D, XMM7D, XMM8D, XMM9D, XMM10D, XMM11D, XMM12D, XMM13D, XMM14D, XMM15D,
		XMM0Q, XMM1Q, XMM2Q, XMM3Q, XMM4Q, XMM5Q, XMM6Q, XMM7Q, XMM8Q, XMM9Q, XMM10Q, XMM11Q, XMM12Q, XMM13Q, XMM14Q, XMM15Q,
		XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7, XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15,
		R8, R8B, R8D, R8W,
		R9, R9B, R9D, R9W,
		R10, R10B, R10D, R10W,
		R11, R11B, R11D, R11W,
		R12, R12B, R12D, R12W,
		R13, R13B, R13D, R13W,
		R14, R14B, R14D, R14W,
		R15, R15B, R15D, R15W,
	};
	using namespace TOKEN;
	Token* Register = new Token(REGISTER | NONVOLATILE | VOLATILE | RETURNING | QUOTIENT | REMAINDER | PARAMETER | STACK_POINTTER | EXTENDED_REGISTER | UNIFORM_REGISTER, "Reg");
	Token* Register_Float = new Token(REGISTER | NONVOLATILE | VOLATILE | RETURNING | DECIMAL | PARAMETER | EXTENDED_REGISTER, "Float_Reg");
	Token* Scalar = new Token(NUM, {
		new Token(NUM, "1"),
		new Token(NUM, "2"),
		new Token(NUM, "4"),
		new Token(NUM, "8")
		}, "Scaler");
	Token* Const = new Token(NUM | STACK_ALLOCATION_CONSTANT, "Const");
	Token* Decimal = new Token(DECIMAL | NUM, "Const");

	long long Additional_Memory_Info = CALL_PARAMETER_SPACE | PARAMETER_SPACE | PUSH_SPACE | REGISTER_SAVE_SPACE | LOCAL_VARIABLE_SCOPE;

	Token* Memory = new Token(MEMORY | Additional_Memory_Info, {
			{ new Token(REGISTER), 2},
			{ new Token(SCALER | ALL_ARGS_SAME_SIZE, {
				{{Register, {1, 8}}, {Scalar, {1, 8}}},
				{{Scalar, {1, 8}}, {Register, {1, 8}}},
				{{Scalar, {1, 8}}, {Scalar, {1, 8}}}
				}), 1},
			{ new Token(OFFSETTER | ALL_ARGS_SAME_SIZE, {
				{{Register, {1, 8}}, {Register, {1, 8}}},
				{{Register, {1, 8}}, {Const, {1, 8}}},
				{{Const, {1, 8}}, {Register, {1, 8}}},
				{{Const, {1, 8}}, {Const, {1, 8}}},
				}), INT32_MAX},
			{ new Token(DEOFFSETTER | ALL_ARGS_SAME_SIZE, {
				{{Register, {1, 8}}, {Register, {1, 8}}},
				{{Register, {1, 8}}, {Const, {1, 8}}},
				{{Const, {1, 8}}, {Register, {1, 8}}},
				{{Const, {1, 8}}, {Const, {1, 8}}},
				}), INT32_MAX}
		}, "memory");
	Token* Memory_Float = new Token(MEMORY | DECIMAL | Additional_Memory_Info, {
			{ new Token(REGISTER), 2},
			{ new Token(SCALER | ALL_ARGS_SAME_SIZE, {
				{{Register, {1, 8}}, {Scalar, {1, 8}}},
				{{Scalar, {1, 8}}, {Register, {1, 8}}},
				{{Scalar, {1, 8}}, {Scalar, {1, 8}}}
				}), 1},
			{ new Token(OFFSETTER | ALL_ARGS_SAME_SIZE, {
				{{Register, {1, 8}}, {Register, {1, 8}}},
				{{Register, {1, 8}}, {Const, {1, 8}}},
				{{Const, {1, 8}}, {Register, {1, 8}}},
				{{Const, {1, 8}}, {Const, {1, 8}}},
				}), INT32_MAX},
			{ new Token(DEOFFSETTER | ALL_ARGS_SAME_SIZE, {
				{{Register, {1, 8}}, {Register, {1, 8}}},
				{{Register, {1, 8}}, {Const, {1, 8}}},
				{{Const, {1, 8}}, {Register, {1, 8}}},
				{{Const, {1, 8}}, {Const, {1, 8}}},
				}), INT32_MAX}
		}, "memory");
	Token* Label = new Token(LABEL | GLOBAL_VARIABLE, "label");
	Token* Data = new Token(NUM | STRING | LABEL);
	Token* Float = new Token(DECIMAL | NUM);

	Utility = {
		Register,
		Scalar,
		Const,
		Memory,
		Label,
		Data
	};

	Token* BYTE = new Token(SIZE_INDENTIFIER, "byte ptr", 1);
	Token* WORD = new Token(SIZE_INDENTIFIER, "word ptr", 2);
	Token* DWORD = new Token(SIZE_INDENTIFIER, "dword ptr", 4);
	Token* QWORD = new Token(SIZE_INDENTIFIER, "qword ptr", 8);

	Size_Identifiers = {
		BYTE,
		WORD,
		DWORD,
		QWORD
	};

	//2reg, 1mul, inf*const, inf*operator
	//*(reg, const) | *(const, const) | *(const, reg)
	//+-(reg, reg) | +-(reg, const) | +-(const, reg) | +-(const, const)

	IR* SET = new IR("=", new Token(OPERATOR, "mov"), {
		{{{ Register, 1, 8 },{Memory, 1, 8}}, 0x8A, OPCODE_ENCODING::RM},
		{{{Memory, 1, 8}, {Register, 1, 8}}, 0x88, OPCODE_ENCODING::MR},
		{{{Register, 1, 8}, {Register, 1, 8}}, 0x88, OPCODE_ENCODING::MR },

		// c6 extends from (1, 1) to (1, 1)
		{{{Register, 1, 1}, {Const, 1, 1}}, 0xC6, OPCODE_ENCODING::MI },
		{{{Memory, 1, 1}, {Const, 1, 1}}, 0xC6, OPCODE_ENCODING::MI },

		// c7 extends from (2, 2) to (2, 2)
		{{{Register, 2, 2}, {Const, 2, 2}}, 0xC7, OPCODE_ENCODING::MI },
		{{{Memory, 2, 2}, {Const, 2, 2}}, 0xC7, OPCODE_ENCODING::MI },

		// c7 extends from (4, 4) to (4, 4)
		{{{Register, 4, 4}, {Const, 4, 4}}, 0xC7, OPCODE_ENCODING::MI },
		{{{Memory, 4, 4}, {Const, 4, 4}}, 0xC7, OPCODE_ENCODING::MI },

		// c7 extends from (4, 8) to (4, 4)
		{{{Register, 4, 8}, {Const, 4, 4}}, 0xC7, OPCODE_ENCODING::MI, 0, 0, false },
		{{{Memory, 4, 8}, {Const, 4, 4}}, 0xC7, OPCODE_ENCODING::MI, 0, 0, false },

		

		{{{Memory_Float, 4, 4}, {Register, 4, 4}}, 0x88, OPCODE_ENCODING::MR}
	});

	IR* XOR = new IR("�", new Token(OPERATOR, "xor"), {
		{{{Register, 1, 8}, {Memory, 1, 8}}, 0x32, OPCODE_ENCODING::RM },
		{{{Register, 1, 8}, {Label, 1, 4}} , 0x80, OPCODE_ENCODING::MI},
		{{{Memory, 1, 8}, {Register, 1, 8}}, 0x30, OPCODE_ENCODING::MR },
		{{{Register, 1, 8}, {Register, 1, 8}}, 0x32, OPCODE_ENCODING::RM },
		{{{Register, 1, 8}, {Const, 1, 4}}, 0x80, OPCODE_ENCODING::MI },
		{{{Memory, 1, 8}, {Const, 1, 4}}, 0x80, OPCODE_ENCODING::MI }
	});

	IR* LEA = new IR("evaluate", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "lea"), {
		{ {{Register, 2, 8 }, { Memory, 2, 8 }}, 0x8D, OPCODE_ENCODING::RM }
	});

	IR* ADD = new IR("+", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "add"), {
		{{{Register, 1, 8}, {Memory, 1, 8}}, 0x02, OPCODE_ENCODING::RM},
		{{{Memory, 1, 8}, {Register, 1, 8}}, 0x00, OPCODE_ENCODING::MR},
		{{{Register, 1, 8}, {Register, 1, 8}}, 0x00, OPCODE_ENCODING::MR},

		{{{Register, 1, 1}, {Const, 1, 1}}, 0x80, OPCODE_ENCODING::MI},
		{{{Register, 2, 2}, {Const, 2, 2}}, 0x81, OPCODE_ENCODING::MI},
		{{{Register, 4, 4}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI},
		{{{Register, 8, 8}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI},

		{{{Memory, 1, 1}, {Const, 1, 1}}, 0x80, OPCODE_ENCODING::MI},
		{{{Memory, 2, 2}, {Const, 2, 2}}, 0x81, OPCODE_ENCODING::MI},
		{{{Memory, 4, 4}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI},
		{{{Memory, 8, 8}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI},
	});

	IR* SUB = new IR("-", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "sub"), {
		{{{Register, 1, 8}, {Memory, 1, 8}}, 0x2A, OPCODE_ENCODING::RM},
		{{{Memory, 1, 8}, {Register, 1, 8}}, 0x28, OPCODE_ENCODING::MR},
		{{{Register, 1, 8}, {Register, 1, 8}}, 0x2A, OPCODE_ENCODING::RM},

		{{{Register, 1, 1}, {Const, 1, 1}}, 0x80, OPCODE_ENCODING::MI, 5},	
		{{{Register, 2, 2}, {Const, 2, 2}}, 0x81, OPCODE_ENCODING::MI, 5},	
		{{{Register, 4, 4}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI, 5},	
		{{{Register, 8, 8}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI, 5},	

		{{{Memory, 1, 1}, {Const, 1, 1}}, 0x80, OPCODE_ENCODING::MI, 5},	
		{{{Memory, 2, 2}, {Const, 2, 2}}, 0x81, OPCODE_ENCODING::MI, 5},	
		{{{Memory, 4, 4}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI, 5},	
		{{{Memory, 8, 8}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI, 5},	
	});	

	IR* MUL = new IR("Internal_MUL", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "imul"), {
		{{{Register, 2, 8}, {Memory, 2, 8}}, 0x0F, OPCODE_ENCODING::RM},
		{{{Register, 2, 8}, {Register, 2, 8}}, 0x0F, OPCODE_ENCODING::RM},
		{{{Register, 2, 8}, {Register, 2, 8}, {Const, 1, 4}}, 0x6B, OPCODE_ENCODING::RMI},
		{{{Register, 2, 8}, {Memory, 2, 8}, {Const, 1, 4}}, 0x6B, OPCODE_ENCODING::RMI},
	});	

	IR* DIV = new IR("Internal_DIV", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "idiv"), {
		{{{Register, 1, 8}}, 0xF6, OPCODE_ENCODING::R},
		{{{Memory, 1, 8}}, 0xF6, OPCODE_ENCODING::M},
	});
	
	IR* C_MUL = new IR("*", new Token(OPERATOR), {
		//accepted arguments
		{{{Register, 1, 8}, {Memory, 1, 8}} },
		{{{Memory, 1, 8}, {Register, 1, 8}} },
		{{{Register, 1, 8}, {Register, 1, 8} }},
		{{{Register, 1, 8}, {Const, 1, 8}} },
		{{{Memory, 1, 8}, {Const, 1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;

			vector<Token*> Args;

			if (args[1]->is(NUM)) {
				if (args[1]->Size > 4){
					args[1]->Size = 4;
				}
				Args = { args[0], args[0], args[1] };
			}
			else {
				Args = { args[0], args[1] };
			}

			Result.push_back(new IR(new Token(OPERATOR, "Internal_MUL"), Args, nullptr));
			
			/*
			//save the rdx if it has some valuable value inside of it.
			//this can occur when a multiplication has been done
			Token* Save_Hold_Remainder = new Token(TOKEN::REGISTER, mul->Get_Name() + "_REMAINDER" + to_string(rand()), _SYSTEM_BIT_SIZE_);
			Token* Remainder = new Token(TOKEN::REMAINDER | TOKEN::REGISTER, "REMAINDER_" + to_string(rand()), _SYSTEM_BIT_SIZE_);
			Result.push_back(new IR(new Token(OPERATOR, "="), { Save_Hold_Remainder, Remainder }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { quotient, eax }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "Internal_MUL"), { mul }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { args[0], quotient }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { Remainder, Save_Hold_Remainder }, nullptr));*/
			return Result;
		}
	);

	IR* C_MOD = new IR("%", new Token(OPERATOR), {
		//accepted arguments
		{{{Register, 1, 8}, {Memory, 1, 8}} },
		{{{Memory, 1, 8}, {Register, 1, 8}}},
		{{{Register, 1, 8}, {Register, 1, 8}}},
		{{{Register, 1, 8}, {Const, 1, 8 }}},
		{{{Memory, 1, 8}, {Const, 1, 8}}},
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Arg1 = nullptr;
			Token* Arg2 = nullptr;
			if (args[1]->is(NUM)) {
				Arg1 = args[1];
				Arg2 = args[0];
			}
			else {
				Arg1 = args[0];
				Arg2 = args[1];
			}
			Token* RAX = new Token(QUOTIENT | REGISTER, Arg1->Get_Name() + "_QUOTIENT" + to_string(rand()), Arg1->Get_Size());
			Token* RDX = new Token(REMAINDER | REGISTER, Arg2->Get_Name() + "_REMAINDER" + to_string(rand()), Arg2->Get_Size());
			if (Arg2->is(NUM)) {
				//you cant give mul a num as a arg so move it to a register.
				Token* tmp = Arg2;
				Arg2 = new Token(REGISTER, Arg2->Get_Name() + "_REG" + to_string(rand()), Arg2->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { Arg2, tmp }, nullptr));
			}

			//\u00a4 <- Pesukone

			Token* Tmp = new Token(REGISTER, RDX->Get_Name() + "_SAVE" + to_string(rand()), RDX->Get_Size());

			Result.push_back(new IR(new Token(OPERATOR, "="), { Tmp, RDX }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "�"), { RDX, RDX }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { RAX, Arg1 }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "Internal_DIV"), { Arg2 }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { args[0], RDX }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { RDX, Tmp }, nullptr));

			return Result;
		}
	);

	IR* C_DIV = new IR("/", new Token(OPERATOR), {
		//accepted arguments
		{{{Register, 1, 8}, {Memory, 1, 8}} },
		{{{Memory, 1, 8}, {Register, 1, 8}}},
		{{{Register, 1, 8}, {Register, 1, 8}}},
		{{{Register, 1, 8}, {Const, 1, 8 }}},
		{{{Memory, 1, 8}, {Const, 1, 8}}},
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Arg1 = nullptr;
			Token* Arg2 = nullptr;
			if (args[1]->is(NUM)) {
				Arg1 = args[1];
				Arg2 = args[0];
			}
			else {
				Arg1 = args[0];
				Arg2 = args[1];
			}
			Token* RAX = new Token(QUOTIENT | REGISTER, Arg1->Get_Name() + "_QUOTIENT" + to_string(rand()), Arg1->Get_Size());
			Token* RDX = new Token(REMAINDER | REGISTER, Arg2->Get_Name() + "_REMAINDER" + to_string(rand()), Arg2->Get_Size());
			if (Arg2->is(NUM)) {
				//you cant give mul a num as a arg so move it to a register.
				Token* tmp = Arg2;
				Arg2 = new Token(REGISTER, Arg2->Get_Name() + "_REG" + to_string(rand()), Arg2->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { Arg2, tmp }, nullptr));
			}

			//\u00a4 <- Pesukone

			Token* Tmp = new Token(REGISTER, RDX->Get_Name() + "_SAVE" + to_string(rand()), RDX->Get_Size());

			Result.push_back(new IR(new Token(OPERATOR, "="), { Tmp, RDX }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "�"), { RDX, RDX }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { RAX, Arg1 }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "Internal_DIV"), { Arg2 }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { args[0], RAX }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { RDX, Tmp }, nullptr));

			return Result;
		}
	);

	IR* MOVQ = new IR("=", new Token(OPERATOR, "movq"), {
		{{{Register_Float, 8, 12}, {Register, 8, 8}}, 0x6E0F, OPCODE_ENCODING::A, 0, 0x66},
		{{{Register, 8, 8} , {Register_Float, 8, 12}}, 0x7E0F, OPCODE_ENCODING::B, 0, 0x66},
	});	

	IR* MOVD = new IR("=", new Token(OPERATOR, "movd"), {
		{{{Register_Float, 4, 4}, {Register, 4, 4}}, 0x6E0F, OPCODE_ENCODING::A},
		{{{Register, 4, 4} , {Register_Float, 4, 4}}, 0x7E0F, OPCODE_ENCODING::A},
		{{{Register_Float, 8, 12}, {Register, 4, 4}}, 0x6E0F, OPCODE_ENCODING::A, 0, 0x66},
		{{{Register, 4, 4} , {Register_Float, 8, 12}}, 0x7E0F, OPCODE_ENCODING::B, 0, 0x66},
	});

	IR* MOVSS = new IR("=", new Token(OPERATOR, "movss"), {
		{{{Register_Float, 4, 4}, {Register_Float, 4, 4}}, 0x100FF3, OPCODE_ENCODING::A},
		{{{Register_Float, 4, 4} , {Memory_Float, 4, 4}}, 0x100FF3, OPCODE_ENCODING::A},
		{{{Memory_Float, 4, 4} , {Register_Float, 4, 4}}, 0x110FF3, OPCODE_ENCODING::C},
	});

	IR* MOVSD = new IR("=", new Token(OPERATOR, "movsd"), {
		{{{Register_Float, 8, 8}, {Register_Float, 8, 8}}, 0x100FF2, OPCODE_ENCODING::A},
		{{{Register_Float, 8, 8} , {Memory_Float, 8, 8}}, 0x100FF2, OPCODE_ENCODING::A},
		{{{Memory_Float, 8, 8} , {Register_Float, 8, 8}}, 0x110FF2, OPCODE_ENCODING::C},
	});

	IR* CONVERTI2F = new IR("convert", new Token(OPERATOR, "cvtsi2ss"), {
		{{{Register_Float, 4, 4}, {Memory, 4, 4}}, 0x2A0F, OPCODE_ENCODING::A, 0, 0xF3},
		{{{Register_Float, 4, 4}, {Register, 4, 4}}, 0x2A0F, OPCODE_ENCODING::A, 0, 0xF3},
	});

	IR* CONVERTI2D = new IR("convert", new Token(OPERATOR, "cvtsi2sd"), {
		{{{Register_Float, 8, 12}, {Memory, 4, 8}}, 0x2A0F, OPCODE_ENCODING::A, 0, 0xF2},
		{{{Register_Float, 8, 12}, {Register, 4, 8}}, 0x2A0F, OPCODE_ENCODING::A, 0, 0xF2},
	});

	IR* CONVERTF2I = new IR("convert", new Token(OPERATOR, "cvttss2si"), {
		{{{Register, 4, 8}, {Register_Float, 4, 4}}, 0x2C0F, OPCODE_ENCODING::A, 0, 0xF3},
		{{{Register, 4, 8}, {Memory_Float, 4, 4}}, 0x2C0F, OPCODE_ENCODING::A, 0, 0xF3},
	});

	IR* CONVERTD2I = new IR("convert", new Token(OPERATOR, "cvttsd2si"), {
		{{{Register, 4, 8}, {Register_Float, 8, 12}}, 0x2C0F, OPCODE_ENCODING::A, 0, 0xF2},
		{{{Register, 4, 8}, {Memory_Float, 8, 12}}, 0x2C0F, OPCODE_ENCODING::A, 0, 0xF2},
	});

	IR* CONVERTD2F = new IR("convert", new Token(OPERATOR, "cvtsd2ss"), {
		{{{Register_Float, 4, 4}, {Register_Float, 8, 12}},  0x5A0F, OPCODE_ENCODING::A, 0, 0xF2},
		{{{Register_Float, 4, 4}, {Memory_Float, 8, 12}},  0x5A0F, OPCODE_ENCODING::A, 0, 0xF2},
	});

	IR* CONVERTF2D = new IR("convert", new Token(OPERATOR, "cvtss2sd"), {
		{{{Register_Float, 8, 12}, {Register_Float, 4, 4}}, 0x5A0F, OPCODE_ENCODING::A, 0, 0xF3},
		{{{Register_Float, 8, 12}, {Memory_Float, 4, 4}}, 0x5A0F, OPCODE_ENCODING::A, 0, 0xF3},
	});


	IR* F_MOV = new IR("=", new Token(OPERATOR), {
		//accepted arguments
		{{{Register_Float, 4, 12}, {Memory, 4, 8}} },
		{{{Memory, 4, 8}, {Register_Float, 4, 12}} },
		{{{Register_Float, 4, 12}, {Memory_Float, 4, 8} }},
		{{{Memory_Float, 4, 8}, {Register_Float, 4, 12}} },
		{{{Memory_Float, 4, 8}, {Decimal, 4, 12}} },
		{{{Register_Float, 4, 12}, {Register_Float, 4, 12}} },
		{{{Register_Float, 4, 12}, {Const, 4, 8} }},
		{{{Memory, 4, 8}, {Const, 4, 8} }},
		{{{Register_Float, 4, 12}, {Decimal, 4, 8}} },
		{{{Memory, 4, 8}, {Decimal, 4, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];
			//transform right side into xmm0
			if (Right->is(NUM)) {
				long long Name;
				if (Right->Get_Size() == 8) {
					double tmp = atof(Right->Get_Name().c_str());
					Name = *(long long*)&tmp;
				}
				else {
					float tmp = atof(Right->Get_Name().c_str());
					Name = *(long*)&tmp;
				}
				Token* R = new Token(TOKEN::REGISTER, "REG_" + to_string(Name + rand()), Right->Get_Size());
				//mov the number into 
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					R,
					new Token(TOKEN::NUM, to_string(Name), Right->Get_Size())
					}, nullptr));

				if (!Left->is(MEMORY)) {
					Token* R2 = new Token(TOKEN::REGISTER | TOKEN::DECIMAL, "MEDIA_" + to_string(Name + rand()), Right->Get_Size());
					Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
						R2, R
						}, nullptr));
					Right = R2;
				}
				else
					Right = R;
			}
			else if (Right->is(DECIMAL) && Left->is(DECIMAL) && Right->Get_Size() != Left->Get_Size()) {
				Token* R = new Token(REGISTER | DECIMAL, "MEDIA_" + Right->Get_Name() + to_string(rand()), Left->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "convert"), { R, Right }, nullptr));
				Right = R;
			}
			else if (Right->is(MEMORY | DECIMAL)) {
				Token* R = new Token(REGISTER | DECIMAL, "REG_" + Right->Get_Name() + to_string(rand()), Right->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), {
					R, Right
					}, nullptr));
				Right = R;
			}
			else if (Right->is(MEMORY)) {
				Token* R = new Token(REGISTER | DECIMAL, "MEDIA_" + Right->Get_Name() + to_string(rand()), Right->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "convert"), {
					R, Right
					}, nullptr));
				Right = R;
			}
			else if (!Right->is(DECIMAL) && Right->is(REGISTER)) {
				Token* R = new Token(REGISTER | DECIMAL, "MEDIA_" + Right->Get_Name() + to_string(rand()), Right->Get_Size());
				string Type = "convert";
				if (Right->is(DECIMAL))
					Type = "=";
				Result.push_back(new IR(new Token(OPERATOR, Type), { R, Right }, nullptr));
				Right = R;
			}
			else
				return vector<IR*>();

			Result.push_back(new IR(new Token(OPERATOR, "="), {
				Left, Right
			}, nullptr));

			return Result;
		}
	);

	IR* F_ADD = new IR("+", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		//accepted arguments		
		{{{Register_Float, 4, 8}, {Memory_Float, 4, 8}} },
		{{{Memory_Float, 4, 8}, {Register_Float, 4, 8}} },
		{{{Register_Float, 4, 8}, {Register_Float, 4, 8}} },
		{{{Register_Float, 4, 8}, {Decimal, 4, 8}} },
		{{{Memory_Float, 4, 8}, {Decimal, 4, 8}} },
		{{{Decimal, 4, 8}, {Register_Float, 4, 8}} },
		{{{Decimal, 4, 8}, {Memory_Float, 4, 8}} }
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];
			if (Right->is(NUM)) {
				double tmp = atof(Right->Get_Name().c_str());
				long long Name = *(long long*)&tmp;
				Token* R = new Token(TOKEN::REGISTER, "REG_" + to_string(Name + rand()), Right->Get_Size());
				//mov the number into 
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					R,
					new Token(TOKEN::NUM, to_string(Name), Right->Get_Size())
					}, nullptr));

				Token* R2 = new Token(TOKEN::REGISTER | TOKEN::DECIMAL, "MEDIA_" + to_string(Name + rand()), Left->Get_Size());
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					R2, R
				}, nullptr));
				Right = R2;
			}
			if (Left->is(MEMORY)) {
				Token* L = new Token(REGISTER | DECIMAL, "MEDIA_" + Left->Get_Name(), Left->Get_Size());
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					L, Left
				}, nullptr));
				Left = L;
			}

			Result.push_back(new IR(new Token(OPERATOR, "addF"), {
				Left, Right
				}, nullptr));

			return Result;
		}
	);

	IR* F_SUB = new IR("-", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		//accepted arguments		
		{{{Register_Float, 4, 8}, {Memory_Float, 4, 8}} },
		{{{Memory_Float, 4, 8}, {Register_Float, 4, 8}} },
		{{{Register_Float, 4, 8}, {Register_Float, 4, 8}} },
		{{{Register_Float, 4, 8}, {Decimal, 4, 8}} },
		{{{Memory_Float, 4, 8}, {Decimal, 4, 8}} },
		{{{Decimal, 4, 8}, {Register_Float, 4, 8}} },
		{{{Decimal, 4, 8}, {Memory_Float, 4, 8}} }
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];
			if (Right->is(NUM)) {
				double tmp = atof(Right->Get_Name().c_str());
				long long Name = *(long long*)&tmp;
				Token* R = new Token(TOKEN::REGISTER, "REG_" + to_string(Name + rand()), Right->Get_Size());
				//mov the number into 
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					R,
					new Token(TOKEN::NUM, to_string(Name), Right->Get_Size())
					}, nullptr));

				Token* R2 = new Token(TOKEN::REGISTER | TOKEN::DECIMAL, "MEDIA_" + to_string(Name + rand()), Left->Get_Size());
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					R2, R
					}, nullptr));
				Right = R2;
			}
			if (Left->is(MEMORY)) {
				Token* L = new Token(REGISTER | DECIMAL, "MEDIA_" + Left->Get_Name(), Left->Get_Size());
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					L, Left
					}, nullptr));
				Left = L;
			}

			Result.push_back(new IR(new Token(OPERATOR, "subF"), {
				Left, Right
				}, nullptr));

			return Result;
		}
	);

	IR* F_MUL = new IR("*", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		//accepted arguments		
		{{{Register_Float, 4, 8}, {Memory_Float, 4, 8}} },
		{{{Memory_Float, 4, 8}, {Register_Float, 4, 8}} },
		{{{Register_Float, 4, 8}, {Register_Float, 4, 8}} },
		{{{Register_Float, 4, 8}, {Decimal, 4, 8}} },
		{{{Memory_Float, 4, 8}, {Decimal, 4, 8}} },
		{{{Decimal, 4, 8}, {Register_Float, 4, 8}} },
		{{{Decimal, 4, 8}, {Memory_Float, 4, 8}} }
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];
			if (Right->is(NUM)) {
				double tmp = atof(Right->Get_Name().c_str());
				long long Name = *(long long*)&tmp;
				Token* R = new Token(TOKEN::REGISTER, "REG_" + to_string(Name + rand()), Right->Get_Size());
				//mov the number into 
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					R,
					new Token(TOKEN::NUM, to_string(Name), Right->Get_Size())
					}, nullptr));

				Token* R2 = new Token(TOKEN::REGISTER | TOKEN::DECIMAL, "MEDIA_" + to_string(Name + rand()), Left->Get_Size());
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					R2, R
					}, nullptr));
				Right = R2;
			}
			if (Left->is(MEMORY)) {
				Token* L = new Token(REGISTER | DECIMAL, "MEDIA_" + Left->Get_Name(), Left->Get_Size());
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					L, Left
					}, nullptr));
				Left = L;
			}

			Result.push_back(new IR(new Token(OPERATOR, "mulF"), {
				Left, Right
				}, nullptr));

			return Result;
		}
	);

	IR* F_DIV = new IR("/", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		//accepted arguments		
		{{{Register_Float, 4, 8}, {Memory_Float, 4, 8}} },
		{{{Memory_Float, 4, 8}, {Register_Float, 4, 8}} },
		{{{Register_Float, 4, 8}, {Register_Float, 4, 8}} },
		{{{Register_Float, 4, 8}, {Decimal, 4, 8}} },
		{{{Memory_Float, 4, 8}, {Decimal, 4, 8}} },
		{{{Decimal, 4, 8}, {Register_Float, 4, 8}} },
		{{{Decimal, 4, 8}, {Memory_Float, 4, 8}} }
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];
			if (Right->is(NUM)) {
				double tmp = atof(Right->Get_Name().c_str());
				long long Name = *(long long*)&tmp;
				Token* R = new Token(TOKEN::REGISTER, "REG_" + to_string(Name + rand()), Right->Get_Size());
				//mov the number into 
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					R,
					new Token(TOKEN::NUM, to_string(Name), Right->Get_Size())
					}, nullptr));

				Token* R2 = new Token(TOKEN::REGISTER | TOKEN::DECIMAL, "MEDIA_" + to_string(Name + rand()), Left->Get_Size());
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					R2, R
					}, nullptr));
				Right = R2;
			}
			if (Left->is(MEMORY)) {
				Token* L = new Token(REGISTER | DECIMAL, "MEDIA_" + Left->Get_Name(), Left->Get_Size());
				Result.push_back(new IR(new Token(TOKEN::OPERATOR, "="), {
					L, Left
					}, nullptr));
				Left = L;
			}

			Result.push_back(new IR(new Token(OPERATOR, "divF"), {
				Left, Right
				}, nullptr));

			return Result;
		}
	);

	IR* F_ADDSS = new IR("addF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "addss"), {
		{{{Register_Float, 4, 4}, {Memory_Float, 4, 4}}, 0x580F, OPCODE_ENCODING::A, 0, 0xF3 },
		{{{Register_Float, 4, 4}, {Register_Float, 4, 4}}, 0x580F, OPCODE_ENCODING::A, 0, 0xF3 },
	});

	IR* F_ADDSD = new IR("addF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "addsd"), {
		{{{Register_Float, 8, 8}, {Memory_Float, 8, 8}}, 0x580F, OPCODE_ENCODING::A, 0, 0xF2 },
		{{{Register_Float, 8, 8}, {Register_Float, 8, 8}}, 0x580F, OPCODE_ENCODING::A, 0, 0xF2 },
	});

	IR* F_SUBSS = new IR("subF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "subss"), {
		{{{Register_Float, 4, 4}, {Memory_Float, 4, 4}}, 0x5C0F, OPCODE_ENCODING::A, 0, 0xF3 },
		{{{Register_Float, 4, 4}, {Register_Float, 4, 4}}, 0x5C0F, OPCODE_ENCODING::A, 0, 0xF3 }
	});

	IR* F_SUBSD = new IR("subF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "subsd"), {
		{{{Register_Float, 8, 8}, {Memory_Float, 8, 8}}, 0x5C0F, OPCODE_ENCODING::A, 0, 0xF2 },
		{{{Register_Float, 8, 8}, {Register_Float, 8, 8}}, 0x5C0F, OPCODE_ENCODING::A, 0, 0xF2 }
	});

	IR* F_MULSS = new IR("mulF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mulss"), {
		{{{Register_Float, 4, 4}, {Memory_Float, 4, 4}}, 0x590F, OPCODE_ENCODING::A, 0, 0xF3 },
		{{{Register_Float, 4, 4}, {Register_Float, 4, 4}}, 0x590F, OPCODE_ENCODING::A, 0, 0xF3 }
	});

	IR* F_MULSD = new IR("mulF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mulsd"), {
		{{{Register_Float, 8, 8}, {Memory_Float, 8, 8}}, 0x590F, OPCODE_ENCODING::A, 0, 0xF2 },
		{{{Register_Float, 8, 8}, {Register_Float, 8, 8}}, 0x590F, OPCODE_ENCODING::A, 0, 0xF2 }
	});

	IR* F_DIVSS = new IR("divF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "divss"), {
		{{{Register_Float, 4, 4}, {Memory_Float, 4, 4}}, 0x5E0F, OPCODE_ENCODING::A, 0, 0xF3 },
		{{{Register_Float, 4, 4}, {Register_Float, 4, 4}}, 0x5E0F, OPCODE_ENCODING::A, 0, 0xF3 }
	});

	IR* F_DIVSD = new IR("divF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "divsd"), {
		{{{Register_Float, 4, 4}, {Memory_Float, 4, 4}}, 0x5E0F, OPCODE_ENCODING::A, 0, 0xF2 },
		{{{Register_Float, 4, 4}, {Register_Float, 4, 4}}, 0x5E0F, OPCODE_ENCODING::A, 0, 0xF2 }
	});

	IR* CMP = new IR("compare", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "cmp"), {
		{{{Register, 1, 8}, {Register, 1, 8}}, 0x38, OPCODE_ENCODING::MR},
		{{{Register, 1, 8}, {Memory, 1, 8}}, 0x3A, OPCODE_ENCODING::RM},
		{{{Memory, 1, 8}, {Register, 1, 8}}, 0x38, OPCODE_ENCODING::MR},
	});

	IR* CMP_CONSTANTS = new IR("compare", new Token(OPERATOR, "cmp"), {
		// 0x80 extends from (1, 1) to (1, 1)
		{{{Register, 1, 1}, {Const, 1, 1}}, 0x80, OPCODE_ENCODING::MI, 7 },
		{{{Memory, 1, 1}, {Const, 1, 1}}, 0x80, OPCODE_ENCODING::MI, 7 },

		// 0x81 extends from (2, 2) to (2, 2)
		{{{Register, 2, 2}, {Const, 2, 2}}, 0x81, OPCODE_ENCODING::MI, 7 },
		{{{Memory, 2, 2}, {Const, 2, 2}}, 0x81, OPCODE_ENCODING::MI, 7 },

		// 0x81 extends from (4, 4) to (4, 4)
		{{{Register, 4, 4}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI, 7 },
		{{{Memory, 4, 4}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI, 7 },

		// 0x81 extends from (4, 8) to (4, 4)
		{{{Register, 4, 8}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI, 7 },
		{{{Memory, 4, 8}, {Const, 4, 4}}, 0x81, OPCODE_ENCODING::MI, 7 },
	});

	IR* JMP = new IR("jump", new Token(FLOW, "jmp"), { 
		{{{Label, 0, 0}}, 0xE9, OPCODE_ENCODING::D, 0xCD},	
		{{{Register, 2, 8}}, 0xFF, OPCODE_ENCODING::M, 4},
	});
	IR* JE = new IR("==", new Token(FLOW, "je"), {
		{{{Label, 0, 0}}, 0x84, OPCODE_ENCODING::D, 0xCD, 0x0F},
	});
	IR* JNE = new IR("!=", new Token(FLOW, "jne"), {
		{{{Label, 0, 0}}, 0x85, OPCODE_ENCODING::D, 0xCD, 0x0F},
	});
	IR* JL = new IR("<", new Token(FLOW, "jl"), {
		{{{Label, 0, 0}}, 0x8C, OPCODE_ENCODING::D, 0xCD, 0x0F},
	});
	IR* JLE = new IR("<=", new Token(FLOW, "jle"), {
		{{{Label, 0, 0}}, 0x8E, OPCODE_ENCODING::D, 0xCD, 0x0F},
	});
	IR* JNL = new IR("!<", new Token(FLOW, "jnl"), {
		{{{Label, 0, 0}}, 0x8D, OPCODE_ENCODING::D, 0xCD, 0x0F},
	});
	IR* JG = new IR(">", new Token(FLOW, "jg"), {
		{{{Label, 0, 0}}, 0x8F, OPCODE_ENCODING::D, 0xCD, 0x0F},
	});
	IR* JGE = new IR(">=", new Token(FLOW, "jge"), {
		{{{Label, 0, 0}}, 0x8D, OPCODE_ENCODING::D, 0xCD, 0x0F},
	});
	IR* JNG = new IR("!>", new Token(FLOW, "jng"), {
		{{{Label, 0, 0}}, 0x8E, OPCODE_ENCODING::D, 0xCD, 0x0F},
	});

	IR* AND = new IR("&", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "and"), {
		{{{Register, 1, 8}, {Register, 1, 8}}, 0x21, OPCODE_ENCODING::MR},
		{{{Register, 1, 8}, {Memory, 1, 8}}, 0x23, OPCODE_ENCODING::RM},
		{{{Memory, 1, 8}, {Register, 1, 8}}, 0x21, OPCODE_ENCODING::MR},
		{{{Register, 1, 8}, {Const, 1, 8}}, 0x81, OPCODE_ENCODING::MI, 4},
		{{{Memory, 1, 8}, {Const, 1, 8}}, 0x81, OPCODE_ENCODING::MI, 4}
	});

	IR* OR = new IR("|", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "or"), {
		{{{Register, 1, 8}, {Register, 1, 8}}, 0x09, OPCODE_ENCODING::MR},
		{{{Register, 1, 8}, {Memory, 1, 8}}, 0x0B, OPCODE_ENCODING::RM},
		{{{Memory, 1, 8}, {Register, 1, 8}}, 0x09, OPCODE_ENCODING::MR},
		{{{Register, 1, 8}, {Const, 1, 8}}, 0x81, OPCODE_ENCODING::MI, 1},
		{{{Memory, 1, 8}, {Const, 1, 8}}, 0x81, OPCODE_ENCODING::MI, 1}
	});

	IR* RET = new IR("return", new Token(FLOW, "ret"), {
		{{}, 0xC3, OPCODE_ENCODING::ZO},
	});

	IR* PUSH = new IR("push", new Token(OPERATOR, "push"), {
		{{{Memory, 2, 8}}, 0xFF, OPCODE_ENCODING::M, 6},
		{{{Register, 2, 8}}, 0x50, OPCODE_ENCODING::O},
		{{{Const, 1, 4}}, 0x6A, OPCODE_ENCODING::I},
	});

	IR* POP = new IR("pop", new Token(OPERATOR, "pop"), {
		{{{Memory, 2, 8}}, 0x8F, OPCODE_ENCODING::M},
		{{{Register, 2, 8}}, 0x8F, OPCODE_ENCODING::M},
	});

	IR* CALL = new IR("call", new Token(TOKEN::CALL, "call"), {
		{{{Label, 0, 0}}, 0xE8, OPCODE_ENCODING::D},
		{{{Register, 2, 8}}, 0xFF, OPCODE_ENCODING::M, 2},
		{{{Memory, 2, 8}}, 0xFF, OPCODE_ENCODING::M, 2},
	});	

	IR* GLOBAL = new IR("global", new Token(TOKEN::GLOBAL_LABEL, ".global"), {
		{{{Label, 0, 0}}},
	}); 

	IR* EXTERN = new IR("extern", new Token(TOKEN::GLOBAL_LABEL, ".extern"), {
		{{{Label, 0, 0}}},
	});

	IR* SECTION = new IR("section", new Token(TOKEN::OPERATOR | TOKEN::SECTION, ".section"), {
		{{{Label, 0, 0}}},
	});

	IR* FILE = new IR("file", new Token(TOKEN::OPERATOR, ".file"), {
		{{{Label, 0, 1}}},
	});

	IR* DB = new IR("init", new Token(TOKEN::SET_DATA, ".byte"), {
		{{{Data, 1, 1}}},
	}); 

	IR* ASCII = new IR("ascii", new Token(TOKEN::SET_DATA, ".asciz"), {
		{{{Data, 0, 1}}},
	});

	IR* DW = new IR("init", new Token(TOKEN::SET_DATA, ".word"), {
		{{{Data, 2, 2}}},
	});

	IR* DD = new IR("init", new Token(TOKEN::SET_DATA, ".long"), {
		{{{Data, 4, 4}}},
	});

	IR* DQ = new IR("init", new Token(TOKEN::SET_DATA, ".quad"), {
		{{{Data, 8, 8}}},
	});

	IR* DDF = new IR("init", new Token(TOKEN::SET_DATA, ".long"), {
		{{{Float, 4, 4}}},
	});

	IR* DQF = new IR("init", new Token(TOKEN::SET_DATA, ".quad"), {
		{{{Float, 8, 8}}},
	});

	IR* SECREL32 = new IR("secrel32", new Token(TOKEN::SET_DATA, ".secrel32"), {
		{{{Data, 4, 8}}},
	});

	IR* LOCATOIN = new IR("location", new Token(TOKEN::SET_DATA, ".loc"), {
		{{{Data, 0, 0}}},
	});

	IR* CFI_START = new IR("cfi_start", new Token(TOKEN::SET_DATA, ".cfi_startproc"), {});
	IR* CFI_END = new IR("cfi_end", new Token(TOKEN::SET_DATA, ".cfi_endproc"), {});
	IR* CFI_OFFSET = new IR("cfi_offset", new Token(TOKEN::SET_DATA, ".cfi_def_cfa_offset"), {
		{{{Data, 0, 4}}},
	});


	Opcodes = {
		LEA,
		ADD,
		SUB,
		MUL,
		C_MUL,
		DIV,
		C_DIV,
		C_MOD,
		CMP,
		CMP_CONSTANTS,
		XOR,
		JMP,
		JE,
		JNE,
		JL,
		JLE,
		JNL,
		JG,
		JGE,
		JNG,
		AND,
		OR,
		RET,
		SET,
		PUSH,
		POP,
		CALL,
		GLOBAL,
		EXTERN,
		SECTION,
		FILE,
		DB,
		DW,
		DD,
		DQ,
		DDF,
		DQF,
		SECREL32,
		LOCATOIN,
		CFI_START,
		CFI_END,
		CFI_OFFSET,
		ASCII,
		MOVQ,
		MOVD,
		MOVSS,
		MOVSD,
		CONVERTI2F,
		CONVERTI2D,
		CONVERTF2D,
		CONVERTF2I,
		CONVERTD2I,
		CONVERTD2F,
		F_MOV,
		F_ADD,
		F_ADDSS,
		F_ADDSD,
		F_SUB,
		F_SUBSS,
		F_SUBSD,
		F_MUL,
		F_DIV,
		F_MULSS,
		F_MULSD,
		F_DIVSS,
		F_DIVSD
	};
}

//References https://wiki.osdev.org/X86-64_Instruction_Encoding
Byte_Map* x86_64::Build(IR* ir){

	Arrange_Encoding(ir->Arguments, ir->Order[0].Encoding);

	Byte_Map* Result = new Byte_Map();

	// Detect Label usage in the IR, if found: put label store it.
	vector<Token*> Detected_Labels = ir->Get_All({TOKEN::LABEL, TOKEN::GLOBAL_VARIABLE});

	// Unconventional for a IR to have more than 1 label in it.
	if (Detected_Labels.size() > 0)
		Result->Label = Detected_Labels[0]->Name;

	Result->Ir = ir;

	Result->Opcode = ir->Order[0].ID;	
	
	Token* Left = ir->Arguments.size() > 0 ? ir->Arguments[0] : nullptr;
	Token* Right = ir->Arguments.size() > 1 ? ir->Arguments[1] : nullptr;

	if (Left && Left->Encoding == MODRM_ENCODING::MOD_RM){
		Token* tmp = Right;
		Right = Left;
		Left = tmp;
	}

	//So no bitches, no args.
	if (Left == nullptr && Right == nullptr){
		//Single byte opcodes like 'ret' dont need even REX_DEFAULTS.

		return Result;

	}
	
	bool Defaults_To_64 = ir->Order[0].Defaults_To_64;

	bool Opcode_Uses_64 = (ir->Arguments.size() > 0 && ir->Arguments[0]->Size == 8) || (ir->Arguments.size() > 1 && ir->Arguments[1]->Size == 8);

	bool Uniform_Or_Extended_Registers_In_Use = Left && Left->ID && Left->ID->Has({TOKEN::UNIFORM_REGISTER, TOKEN::EXTENDED_REGISTER}) || 
												Right && Right->ID && Right->ID->Has({TOKEN::UNIFORM_REGISTER, TOKEN::EXTENDED_REGISTER});

	bool Memory_Has_Uniform_Or_Extended_In_Use = Right && Right->is(TOKEN::MEMORY) && Right->Has({TOKEN::UNIFORM_REGISTER, TOKEN::EXTENDED_REGISTER});

	//Rex is only awaiable in 64 bit mode.
	if (_SYSTEM_BIT_SIZE_ == 8){
		if (!Defaults_To_64 && (Uniform_Or_Extended_Registers_In_Use || Opcode_Uses_64 || Memory_Has_Uniform_Or_Extended_In_Use)){
			Result->Rex.ID = REX_DEFAULT;			
			
			//now we know that the opcode does not default to 64 bit arguments.
			//Now check if one of the arguments are 64bit size.
			if (Opcode_Uses_64){
				Result->Rex.W = true;
			}
		}
	}

	//This is Left side because Encoding switches register and immediate places.
	if (Left && Left->is(TOKEN::NUM)){
		Result->Immediate = atoll(Left->Name.c_str());
		Result->Immediate_Size = Left->Size;
		Result->Has_Immediate = true;
	}
	else if (Left && Left->is(TOKEN::LABEL)){
		Result->Immediate = 0;
		Result->Immediate_Size = 4;	// CAP the size to 32 bits.
		Result->Has_Immediate = true;
	}

	//Calculate the REX bits.
	//A REX prefix must be encoded when:
	// using 64-bit operand size and the instruction does not default to 64-bit operand size; or
	// using one of the extended registers (R8 to R15, XMM8 to XMM15, YMM8 to YMM15, CR8 to CR15 and DR8 to DR15); or
	// using one of the uniform byte registers SPL, BPL, SIL or DIL.
	//In other words we set the REX.W bit if the instruction does not default to 64-bit operand size.
	//We set the REX.R bit if the opcode has MODRM.reg field.
	//We set the REX.X bit if the opcode has a 64-bit addrressing SIB.index field.
	//We set the REX.B bit if the opcode has MODRM.rm field or SIB.base field.

	//Check if the instruction has MODRM.reg field.
	//This we can check by looking the Rex value's 4'th bit is set from the Right operand.
	if (Right && Right->XReg & REX_BIT_SETTED) {
		Result->Rex.B = true;
	}

	//Check if the instruction has a 64-bit addrressing SIB.index field.

	//Check if the instruction has MODRM.rm field or SIB.base field.
	//This we can check by looking the Rex value's 4'th bit is set from the Left operand.
	if (Left && Left->XReg & REX_BIT_SETTED) {
		Result->Rex.R = true;
	}

	unsigned char MODRM_Key = 0;
		
	//O encoding works by adding the register number to the opcode.
	if (ir->Order[0].Encoding == OPCODE_ENCODING::O || ir->Order[0].Encoding == OPCODE_ENCODING::OI){

		Result->Opcode += Left->XReg & ~(1 << 3);

	}
	else if (ir->Order[0].Encoding != OPCODE_ENCODING::ZO){
		if (Right) {
			MODRM_Key =	Get_MODRM_Type(Right);
		}

		if (MODRM_Key == 0){
			MODRM_Key = Get_MODRM_Type(Left);
		}

		Result->ModRM.Mod = MODRMS[MODRM_Key];

		Result->ModRM.Is_Used = true;
	}

	//Calculate SIB
	if (Right && Right->is(TOKEN::MEMORY)){
		bool Uses_SIB = Needs_SIB(Right);

		// The memory operator needs SIB
		if (Uses_SIB){
			//activate Sib mode by adding RSP to modrm
			Result->ModRM.Is_Used = true;

			Token* sp = nullptr;
			for (auto& i : X86_64.Registers)
				if (i->is(TOKEN::STACK_POINTTER)){
					sp = i;
					break;
				}
			
			//we know rsp will never use 0b1000 so dont need to activate B flag from REX.
			Result->ModRM.RM = sp->XReg;

			Result->Sib = Get_SIB(Right, *Result);
		}
		// The Memory operator is simple enought to not use SIB
		else{
			Token* Register_Offsetter = Right->Get_All(TOKEN::REGISTER)[0];

			Result->ModRM.RM = Register_Offsetter->XReg & ~(1 << 3);

			if (Register_Offsetter->XReg & REX_BIT_SETTED){
				Result->Rex.B = true;
			}

			//Now apply the samew thig for the disp8
			if (Right->Get_All(TOKEN::NUM).size() > 0){
				Token* Disp8 = Right->Get_All(TOKEN::NUM)[0];

				Result->Displacement = stoll(Disp8->Name);
				Result->Has_Displacement = true;
				Result->Displacement_Size = 4;
			}
			else if (Right->Get_All(TOKEN::LABEL).size() > 0){
				Result->Displacement = 0;
				Result->Has_Displacement = true;
				Result->Displacement_Size = 4;
			}
			// Displacement usages for global variables
			// NOTE: these are not flipped around the mod/rm
			else if (Right->Get_All(TOKEN::GLOBAL_VARIABLE).size() > 0){
				Result->Displacement = 0;
				Result->Displacement_Size = 4;
				Result->Has_Displacement = true;
				Result->Is_Global_Variable = true;
			}

		}
	}

	if (ir->Order[0].Post_Fix != 0){
		Result->ModRM.Reg = ir->Order[0].Post_Fix;
	}

	if (Left && Left->is(TOKEN::REGISTER)){
		//remove the rex flag bit
		Result->ModRM.Reg = Left->XReg & ~(1 << 3);
	}

	if (Right && Right->is(TOKEN::REGISTER)){
		//remove the rex flag bit
		Result->ModRM.RM = Right->XReg & ~(1 << 3);
	}

	//Add the 0x66 prefix if the args size is 16bits
	if (ir->Arguments.size() > 0) {
		if (ir->Arguments[0]->Size == 2) {

			Result->Prefix = OPERAND_SIZE_OVERRIDE;
			Result->Has_Prefix = true;

		}
	}

	if (Result->Has_Prefix == false && ir->Order[0].Pre_Fix > 0){

		Result->Prefix = ir->Order[0].Pre_Fix;
		Result->Has_Prefix = true;

	}

	//Update the opcode id
	Modify_OpCode(Result);

	if (Result->Label != ""){

		// Calculate the accurate point in which the label address is going to be appointed to. 
		Result->Precise_Label_Index = Get_Size_Without_Imm_And_Disp(Result);
	}

	// write the additional offset of the displacement and immediate by the size of the opcode
	if (Result->Has_Displacement){
		int Remaining_Opcode_Tail_After_Displacement = selector->Get_Size(Result) - Result->Precise_Label_Index;

		Result->Displacement -= Remaining_Opcode_Tail_After_Displacement;
	}


	return Result;
}

unsigned char x86_64::Get_MODRM_Type(Token* t)
{
	unsigned char Result = 0;

	bool Using_Positional_Independet_Register = false;

	vector<Token*> Contents = t->Get_All(TOKEN::STACK_POINTTER);

	if (Contents.size() > 0) {

		Result |= MODRM_FLAGS::SIB;

	}

	Contents = t->Get_All(TOKEN::REGISTER);
	if (Contents.size() > 0) {
		if (Contents[0]->is(TOKEN::POSITION_INDEPENDENT_REGISTER))
			Using_Positional_Independet_Register = true;

		Result |= MODRM_FLAGS::RM;

	}

	Contents = t->Get_All(TOKEN::NUM);
	if (Contents.size() > 0) {

		Result |= MODRM_FLAGS::RM;

	}

	// Do not trigger, Displacement flag if there is a EIP/RIP register within the bounds of the operation.
	Contents = t->Get_All(TOKEN::OFFSETTER);
	if (Contents.size() > 0 && !Using_Positional_Independet_Register) {

		Result |= MODRM_FLAGS::DISP32;

	}

	if (t->is(TOKEN::MEMORY)) {

		Result |= MODRM_FLAGS::MEMORY;

	}
	
	return Result;
}

bool x86_64::Needs_SIB(Token* RM){
	bool Result = false;

	if (RM == nullptr || !RM->is(TOKEN::MEMORY)){
		return false;
	}

	//Now we need to find out if the IR in question uses SIB.

	//This is done by checking if the RM has a stack pointer as a child.
	vector<Token*> Contents = RM->Get_All(TOKEN::STACK_POINTTER);

	if (Contents.size() > 0) {
		Result = true;
	}

	//And if the RM has more than one register init.
	Contents = RM->Get_All(TOKEN::REGISTER);

	if (Contents.size() > 1) {
		Result = true;
	}

	//And if the RM has Displacement numbers larger than 8bits.
	Contents = RM->Get_All(TOKEN::NUM);

	if (Contents.size() > 0) {
		for (auto& i : Contents){
			int Bits_Size = selector->Get_Bits_Size(stoi(i->Name));
			if (Bits_Size > sizeof(char)){
				Result = true;
			}
		}
	}

	//And if the RM has Scaling operator * init.
	Contents = RM->Get_All(TOKEN::SCALER);

	if (Contents.size() > 0) {
		Result = true;
	}

	return Result;
}

SIB x86_64::Get_SIB(Token* t, Byte_Map& back_referece){
	SIB Result;

	Result.Is_Used = true;
	bool Index_Setted = false;
	bool Base_Setted = false;
	bool Has_Stack_Pointer_Register = false;

	//First get the scaler if there is one.
	vector<Token*> Scaler_Operands = t->Get_All(TOKEN::SCALER);

	//only 1 max scaler can be in one memory operand.
	if (Scaler_Operands.size() > 0){
		Token* Num = Scaler_Operands[0]->Left;
		Token* Index = Scaler_Operands[0]->Right;

		if (!Num->is(TOKEN::NUM)){
			Num = Scaler_Operands[0]->Right;
			Index = Scaler_Operands[0]->Left;
		}

		// ((reg1 + reg2) * 2)
		if (Index->Any(TOKEN::OFFSETTER | TOKEN::DEOFFSETTER)){
			Index = Index->Right;
		}

		//Now we can resolve the scaler
		if (Num->Name == "1") 		Result.Scale = 0b00;
		else if (Num->Name == "2") 	Result.Scale = 0b01;
		else if (Num->Name == "4") 	Result.Scale = 0b10;
		else if (Num->Name == "8") 	Result.Scale = 0b11;

		//(S * Index)
		//Index must be a register
		Result.Index = Index->XReg & ~(1 << 3);
		
		if (Index->XReg & REX_BIT_SETTED) {
			back_referece.Rex.X = 1;
		}

		Index_Setted = true;
	}

	if (t->Get_All(TOKEN::STACK_POINTTER).size() > 0){
		Has_Stack_Pointer_Register = true;
	}

	//Now we need to get the base register.
	//[rsp + 2 * rax + 123]
	//[(rsp + (2 * rax)) + 123]
	
	vector<Token*> Offset_Operands = t->Get_All(TOKEN::OFFSETTER);

	for (auto& Side : Offset_Operands){
		vector<Token*> Interesting_Sides = {Side->Left};

		if (Interesting_Sides[0]->is({TOKEN::OFFSETTER, TOKEN::SCALER})){
			Interesting_Sides = {Side->Right};
		}
		else{
			Interesting_Sides.push_back(Side->Right);
		}

		for (auto& i : Interesting_Sides){
			if (i->is(TOKEN::REGISTER)){
				if (!Base_Setted || (Has_Stack_Pointer_Register && i->is(TOKEN::STACK_POINTTER))){
					//Index must be a register
					Result.Base = i->XReg & ~(1 << 3);
					
					if (i->XReg & REX_BIT_SETTED) {
						back_referece.Rex.B = 1;
					}

					Base_Setted = true;
				}
				else if(!Index_Setted){
					//[Base + Index]
					//Index must be a register
					Result.Index = i->XReg & ~(1 << 3);
					
					if (i->XReg & REX_BIT_SETTED) {
						back_referece.Rex.X = 1;
					}

					Index_Setted = true;
				}
			}
			else if (i->is(TOKEN::NUM)){
				back_referece.Displacement = stoll(i->Name);

				back_referece.Has_Displacement = true;
				back_referece.Displacement_Size = 4;
			}
			else if (i->is(TOKEN::LABEL)){

				back_referece.Displacement = 0;
				back_referece.Has_Displacement = true;
				back_referece.Displacement_Size = _SYSTEM_BIT_SIZE_;

			}
		}
	}

	//Update MODrm MOD value by SIB

	//[base + (index * s) + disp32]
	if ((Base_Setted && Index_Setted && back_referece.Has_Displacement)){

		back_referece.ModRM.Mod = 0b10;

	}
	else if (Has_Stack_Pointer_Register && back_referece.Has_Displacement){

		back_referece.ModRM.Mod = 0b10;

		//RSP needsa to be also in the Base as well in the Index
		Result.Index = Result.Base;

	}
	//[base + (index * s)] || [(index * s) + disp32]	
	else if ((Base_Setted && Index_Setted) || (Index_Setted && back_referece.Has_Displacement)){
		back_referece.ModRM.Mod = 0b00;
	}

	return Result;
}

void x86_64::Modify_OpCode(class Byte_Map* b){
	//if the opcode is maxed already at single opcode code then skip this phase.
	if (
		b->Ir->Order[0].Order[0].Min_Size == b->Ir->Order[0].Order[0].Max_Size ||
		//check if tyhis single order doesnt use 8 bit parameters.
		b->Ir->Order[0].Order[0].Min_Size > 1
	){
		return;
	}

	//This order might not have all the combinations
	if (b->Ir->Order[0].Smallest_Size > 1){
		//This means that there is no 8bit size to convert from.
		return;
	}

	//if the given byte map doesnt use more than 8bit arguments, then we can let it be.
	//if otherwise, we need to increment it by 1
	bool Args_Utilise_More_Than_8Bits = false;

	for (auto& i : b->Ir->Arguments){
		if (i->Size > 1){
			Args_Utilise_More_Than_8Bits = true;
			break;
		}
	}

	if (Args_Utilise_More_Than_8Bits){
		b->Opcode += 1;
	}
}

vector<unsigned char> x86_64::Assemble(Byte_Map* Input)
{
	string Result = "";

	if (Input->Prefix != 0){
		Result += Input->Prefix;
	}

	if (Input->Rex.ID != 0){
		//here we will contruct the REX bits with the information of bitmasks from x86_64
		unsigned char Rex = Input->Rex.ID;

		if (Input->Rex.W) {
			Rex |= REX_W;
		}
		if (Input->Rex.R) {
			Rex |= REX_R;
		}
		if (Input->Rex.X) {
			Rex |= REX_X;
		}
		if (Input->Rex.B) {
			Rex |= REX_B;
		}
	
		Result += Rex;
	}

	Result += Input->Opcode;

	if (Input->ModRM.Is_Used && Input->Ir->Order[0].Encoding != OPCODE_ENCODING::D){
		//	7                              0
		// +---+---+---+---+---+---+---+---+
		// |  mod  |    reg    |     rm    |
		// +---+---+---+---+---+---+---+---+
		unsigned char ModRM = Input->ModRM.Mod << 6;

		ModRM |= Input->ModRM.Reg << 3;
		ModRM |= Input->ModRM.RM;

		Result += ModRM;
	}

	if (Input->Sib.Is_Used){
		// 	 7                           0
		// +---+---+---+---+---+---+---+---+
		// | scale |   index   |    base   |
		// +---+---+---+---+---+---+---+---+
		unsigned char SIB = Input->Sib.Scale << 6;

		SIB |= Input->Sib.Index << 3;
		SIB |= Input->Sib.Base;

		Result += SIB;
	}

	if (Input->Has_Displacement){
		int Size = Input->Displacement_Size;

		vector<unsigned char> Displacement_Value;
		Displacement_Value.resize(Size);

		memcpy(Displacement_Value.data(), (unsigned char*)&Input->Displacement, (unsigned char)Size);

		Result.insert(Result.end(), Displacement_Value.begin(), Displacement_Value.end());
	}

	if (Input->Has_Immediate){
		int Size = Input->Immediate_Size;

		if (Input->Label != ""){
			Size = 4;	// CAP to 32 bits.
		}

		vector<unsigned char> Immediate_Value;
		Immediate_Value.resize(Size);

		memcpy(Immediate_Value.data(), (unsigned char*)&Input->Immediate, (unsigned char)Size);

		Result.insert(Result.end(), Immediate_Value.begin(), Immediate_Value.end());
	}

	//mov [rsp + 0], 1

	//transform string Result into  vector<unsigned char>
	vector<unsigned char> Result_Bytes;

	for (int i = 0; i < Result.size(); i++) {
		Result_Bytes.push_back(Result[i]);
	}

	return Result_Bytes;
}

int x86_64::Get_Size_Without_Imm_And_Disp(Byte_Map* Input){
	int Result = 0;

	if (Input->Prefix != 0){
		Result += selector->Get_Bits_Size(Input->Prefix);	//1-4 Bits
	}

	if (Input->Rex.ID != 0){
		//here we will contruct the REX bits with the information of bitmasks from x86_64
		Result += 1;	//1 Bits
	}

	Result += selector->Get_Bits_Size(Input->Opcode);	//1-4 Bits

	if (Input->ModRM.Is_Used && Input->Ir->Order[0].Encoding != OPCODE_ENCODING::D){
		Result += 1; 	//1 Bits
	}

	if (Input->Sib.Is_Used){
		Result += 1;	//1 Bits
	}

	return Result;
}

int x86_64::Get_Size(Byte_Map* Input){
	int Result = 0;

	Result += Get_Size_Without_Imm_And_Disp(Input);

	if (Input->Has_Displacement){
		Result += Input->Displacement_Size;	//1-4 Bits
	}

	if (Input->Has_Immediate){
		Result += Input->Immediate_Size;	//1-4 Bits
	}

	return Result;
}

void x86_64::Arrange_Encoding(vector<Token*>& Args, OPCODE_ENCODING Encoding){

	if (Args.size() == 2 && (Encoding == OPCODE_ENCODING::MI || Encoding == OPCODE_ENCODING::MR)){
		Args[0]->Encoding = MODRM_ENCODING::MOD_RM;
		Args[1]->Encoding = MODRM_ENCODING::MOD_REG;
	}
	else if (Args.size() == 1 && Encoding == OPCODE_ENCODING::M){
		Args[0]->Encoding = MODRM_ENCODING::MOD_RM;
	}
}
