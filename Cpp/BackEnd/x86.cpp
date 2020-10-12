#include "../../H/BackEnd/x86.h"

void x86_64_Win::Init()
{
	SIZE = 8;	//64 bit arch

	Token* AL = new Token(TOKEN::VOLATILE  | TOKEN::RETURNING, "al", 1, {});
	Token* AH = new Token(TOKEN::VOLATILE  | TOKEN::RETURNING, "ah", 1, {});
	Token* AX = new Token(TOKEN::VOLATILE  | TOKEN::RETURNING, "ax", 2, { AH, AL });
	Token* EAX = new Token(TOKEN::VOLATILE | TOKEN::RETURNING, "eax", 4, { AX });
	Token* RAX = new Token(TOKEN::VOLATILE | TOKEN::RETURNING, "rax", 8, { EAX });

	Token* BL = new Token(TOKEN::NONVOLATILE, "bl", 1, {});
	Token* BH = new Token(TOKEN::NONVOLATILE, "bh", 1, {});
	Token* BX = new Token(TOKEN::NONVOLATILE, "bx", 2, { BH, BL });
	Token* EBX = new Token(TOKEN::NONVOLATILE, "ebx", 4, { BX });
	Token* RBX = new Token(TOKEN::NONVOLATILE, "rbx", 8, { EBX });

	Token* CL = new Token(TOKEN::VOLATILE, "cl", 1, {});
	Token* CH = new Token(TOKEN::VOLATILE, "ch", 1, {});
	Token* CX = new Token(TOKEN::VOLATILE, "cx", 2, { CH, CL });
	Token* ECX = new Token(TOKEN::VOLATILE, "ecx", 4, { CX });
	Token* RCX = new Token(TOKEN::VOLATILE, "rcx", 8, { ECX});

	Token* DL = new Token(TOKEN::VOLATILE, "dl", 1, {});
	Token* DH = new Token(TOKEN::VOLATILE, "dh", 1, {});
	Token* DX = new Token(TOKEN::VOLATILE, "dx", 2, { DH, DL });
	Token* EDX = new Token(TOKEN::VOLATILE, "edx", 4, { DX });
	Token* RDX = new Token(TOKEN::VOLATILE, "rdx", 8, { EDX });

	Token* DIL = new Token(TOKEN::NONVOLATILE, "dil", 1, {});
	//Token* DIH = new Token(TOKEN::NONVOLATILE, "dih", 1, {});
	Token* DI = new Token(TOKEN::NONVOLATILE , "di", 2, {DIL });
	Token* EDI = new Token(TOKEN::NONVOLATILE, "edi", 4, { DI });
	Token* RDI = new Token(TOKEN::NONVOLATILE, "rdi", 8, { EDI });

	Token* SIL = new Token(TOKEN::NONVOLATILE, "sil", 1, {});
	//Token* SIH = new Token(TOKEN::NONVOLATILE, "sih", 1, {});
	Token* SI = new Token(TOKEN::NONVOLATILE , "si", 2, {SIL });
	Token* ESI = new Token(TOKEN::NONVOLATILE, "esi", 4, { SI });
	Token* RSI = new Token(TOKEN::NONVOLATILE, "rsi", 8, { ESI });


	Token* BPL = new Token(TOKEN::NONVOLATILE, "bpl", 1, {});
	Token* BP = new Token(TOKEN::NONVOLATILE, "bp", 2, { BPL });
	Token* EBP = new Token(TOKEN::NONVOLATILE, "ebp", 4, { BP });
	Token* RBP = new Token(TOKEN::NONVOLATILE, "rbp", 8, { EBP });

	Token* SPL = new Token(TOKEN::NONVOLATILE, "spl", 1, {});
	Token* SP = new Token(TOKEN::NONVOLATILE, "sp", 2, { SPL });
	Token* ESP = new Token(TOKEN::NONVOLATILE, "esp", 4, { SP });
	Token* RSP = new Token(TOKEN::NONVOLATILE, "rsp", 8, { ESP });

	Token* XMM0 = new Token(TOKEN::VOLATILE  | TOKEN::RETURNING, "xmm0", 12, {});
	Token* XMM1 = new Token(TOKEN::VOLATILE , "xmm1", 12, {});
	Token* XMM2 = new Token(TOKEN::VOLATILE , "xmm2", 12, {});
	Token* XMM3 = new Token(TOKEN::VOLATILE , "xmm3", 12, {});
	Token* XMM4 = new Token(TOKEN::VOLATILE , "xmm4", 12, {});
	Token* XMM5 = new Token(TOKEN::VOLATILE , "xmm5", 12, {});
	Token* XMM6 = new Token(TOKEN::VOLATILE , "xmm6", 12, {});
	Token* XMM7 = new Token(TOKEN::VOLATILE , "xmm7", 12, {});
	Token* XMM8 = new Token(TOKEN::VOLATILE , "xmm8", 12, {});
	Token* XMM9 = new Token(TOKEN::VOLATILE , "xmm9", 12, {});
	Token* XMM10 = new Token(TOKEN::VOLATILE, "xm10", 12, {});
	Token* XMM11 = new Token(TOKEN::VOLATILE, "xmm11", 12, {});
	Token* XMM12 = new Token(TOKEN::VOLATILE, "xmm12", 12, {});
	Token* XMM13 = new Token(TOKEN::VOLATILE, "xmm13", 12, {});
	Token* XMM14 = new Token(TOKEN::VOLATILE, "xmm14", 12, {});
	Token* XMM15 = new Token(TOKEN::VOLATILE, "xmm15", 12, {});

	Token* R8B = new Token(TOKEN::VOLATILE, "r8b", 1, {});
	Token* R8W = new Token(TOKEN::VOLATILE, "r8w", 2, { R8B });
	Token* R8D = new Token(TOKEN::VOLATILE, "r8d", 4, { R8W });
	Token* R8 = new Token(TOKEN::VOLATILE , "r8", 8, { R8D });

	Token* R9B = new Token(TOKEN::VOLATILE, "r9b", 1, {});
	Token* R9W = new Token(TOKEN::VOLATILE, "r9w", 2, { R9B });
	Token* R9D = new Token(TOKEN::VOLATILE, "r9d", 4, { R9W });
	Token* R9 = new Token(TOKEN::VOLATILE , "r9", 8, { R9D });

	Token* R10B = new Token(TOKEN::VOLATILE, "r10b", 1, {});
	Token* R10W = new Token(TOKEN::VOLATILE, "r10w", 2, { R10B });
	Token* R10D = new Token(TOKEN::VOLATILE, "r10d", 4, { R10W });
	Token* R10 = new Token(TOKEN::VOLATILE , "r10", 8, { R10D });

	Token* R11B = new Token(TOKEN::VOLATILE, "r11b", 1, {});
	Token* R11W = new Token(TOKEN::VOLATILE, "r11w", 2, { R11B });
	Token* R11D = new Token(TOKEN::VOLATILE, "r11d", 4, { R11W });
	Token* R11 = new Token(TOKEN::VOLATILE , "r11", 8, { R11D });

	Token* R12B = new Token(TOKEN::NONVOLATILE, "r12b", 1, {});
	Token* R12W = new Token(TOKEN::NONVOLATILE, "r12w", 2, { R12B });
	Token* R12D = new Token(TOKEN::NONVOLATILE, "r12d", 4, { R12W });
	Token* R12 = new Token(TOKEN::NONVOLATILE , "r12", 8, { R12D });

	Token* R13B = new Token(TOKEN::NONVOLATILE, "r13b", 1, {});
	Token* R13W = new Token(TOKEN::NONVOLATILE, "r13w", 2, { R13B });
	Token* R13D = new Token(TOKEN::NONVOLATILE, "r13d", 4, { R13W });
	Token* R13 = new Token(TOKEN::NONVOLATILE , "r13", 8, { R13D });

	Token* R14B = new Token(TOKEN::NONVOLATILE, "r14b", 1, {});
	Token* R14W = new Token(TOKEN::NONVOLATILE, "r14w", 2, { R14B });
	Token* R14D = new Token(TOKEN::NONVOLATILE, "r14d", 4, { R14W });
	Token* R14 = new Token(TOKEN::NONVOLATILE , "r14", 8, { R14D });

	Token* R15B = new Token(TOKEN::NONVOLATILE, "r15b", 1, {});
	Token* R15W = new Token(TOKEN::NONVOLATILE, "r15w", 2, { R15B });
	Token* R15D = new Token(TOKEN::NONVOLATILE, "r15d", 4, { R15W });
	Token* R15 = new Token(TOKEN::NONVOLATILE , "r15", 8, { R15D });


	Parameter_Registers = { RCX, RDX, R8, R9 , XMM0, XMM1, XMM2, XMM3 };
	Registers = { 
		RAX, EAX, AX, AH, AL,
		RBX, EBX, BX, BH, BL,
		RCX, ECX, CX, CH, CL,
		RDX, EDX, DX, DH, DL,
		RDI, EDI, DI, DIL,
		RSI, ESI, SI, SIL,
		RBP, EBP, BP,
		RSP, ESP, SP,
		XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7, XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15
	};
	using namespace TOKEN;
	Token* Register = new Token(REGISTER);
	Token* Scalar = new Token(NUM, {
		new Token(NUM, "1"),
		new Token(NUM, "2"),
		new Token(NUM, "4"),
		new Token(NUM, "8")
		});	
	Token* Const = new Token(NUM);
	Token* BRACKETS = new Token(MEMORY, {
			{ new Token(REGISTER), 2},
			{ new Token(SCALER, vector<pair<Token*, Token*>>{
				{Register, Scalar},
				{Scalar, Register},
				{Scalar, Scalar}
				}), 1},
			{ new Token(OFFSETTER, vector<pair<Token*, Token*>>{
				{Register, Register},
				{Register, Const},
				{Const, Register},
				{Const, Const}
				}), INT32_MAX},
			{ new Token(DEOFFSETTER, vector<pair<Token*, Token*>>{
				{Register, Register},
				{Register, Const},
				{Const, Register},
				{Const, Const}
				}), INT32_MAX}
		});


	//2reg, 1mul, inf*const, inf*operator
	//*(reg, const) | *(const, const) | *(const, reg)
	//+-(reg, reg) | +-(reg, const) | +-(const, reg) | +-(const, const)

}
