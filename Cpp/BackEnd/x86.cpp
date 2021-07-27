#include "../../H/BackEnd/x86.h"
#include "../../H/UI/Usr.h"

extern Usr* sys;

void x86_64::Init()
{
	size = 8;	//64 bit arch

	long long OS_DEPENDENT_FLAG = TOKEN::NONVOLATILE;

	if (sys->Info.OS == "unix")
		OS_DEPENDENT_FLAG = TOKEN::VOLATILE;

	Seperator = ",";
	Register_Pre_Fix = "";
	Number_Pre_Fix = "";
	Label_Post_Fix = ":";

	Token* AL = new Token(TOKEN::RETURNING | TOKEN::QUOTIENT, "al", 1, {});
	Token* AH = new Token(TOKEN::RETURNING, "ah", 1, {});
	Token* AX = new Token(TOKEN::RETURNING | TOKEN::QUOTIENT, "ax", 2, { AH, AL });
	Token* EAX = new Token(TOKEN::RETURNING | TOKEN::QUOTIENT, "eax", 4, { AX });
	Token* RAX = new Token(TOKEN::RETURNING | TOKEN::QUOTIENT, "rax", 8, { EAX });

	Token* BL = new Token(TOKEN::NONVOLATILE, "bl", 1, {});
	Token* BH = new Token(TOKEN::NONVOLATILE, "bh", 1, {});
	Token* BX = new Token(TOKEN::NONVOLATILE, "bx", 2, { BH, BL });
	Token* EBX = new Token(TOKEN::NONVOLATILE, "ebx", 4, { BX });
	Token* RBX = new Token(TOKEN::NONVOLATILE, "rbx", 8, { EBX });

	Token* CL = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "cl", 1, {});
	Token* CH = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "ch", 1, {});
	Token* CX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "cx", 2, { CH, CL });
	Token* ECX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "ecx", 4, { CX });
	Token* RCX = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "rcx", 8, { ECX});

	Token* DL = new Token( TOKEN::PARAMETER, "dl", 1, {});
	Token* DH = new Token( TOKEN::PARAMETER, "dh", 1, {});
	Token* DX = new Token( TOKEN::PARAMETER  | TOKEN::REMAINDER, "dx", 2, { DH, DL });
	Token* EDX = new Token( TOKEN::PARAMETER | TOKEN::REMAINDER, "edx", 4, { DX });
	Token* RDX = new Token( TOKEN::PARAMETER | TOKEN::REMAINDER, "rdx", 8, { EDX });

	Token* DIL = new Token(OS_DEPENDENT_FLAG, "dil", 1, {});
	//Token* DIH = new Token(TOKEN::NONVOLATILE, "dih", 1, {});
	Token* DI = new Token(OS_DEPENDENT_FLAG, "di", 2, {DIL });
	Token* EDI = new Token(OS_DEPENDENT_FLAG, "edi", 4, { DI });
	Token* RDI = new Token(OS_DEPENDENT_FLAG, "rdi", 8, { EDI });

	Token* SIL = new Token(OS_DEPENDENT_FLAG, "sil", 1, {});
	//Token* SIH = new Token(TOKEN::NONVOLATILE, "sih", 1, {});
	Token* SI = new Token(OS_DEPENDENT_FLAG, "si", 2, {SIL });
	Token* ESI = new Token(OS_DEPENDENT_FLAG, "esi", 4, { SI });
	Token* RSI = new Token(OS_DEPENDENT_FLAG, "rsi", 8, { ESI });


	Token* BPL = new Token(TOKEN::NONVOLATILE, "bpl", 1, {});
	Token* BP = new Token(TOKEN::NONVOLATILE, "bp", 2, { BPL });
	Token* EBP = new Token(TOKEN::NONVOLATILE, "ebp", 4, { BP });
	Token* RBP = new Token(TOKEN::NONVOLATILE, "rbp", 8, { EBP });

	Token* SPL = new Token(TOKEN::STACK_POINTTER, "spl", 1, {});
	Token* SP = new Token(TOKEN::STACK_POINTTER, "sp", 2, { SPL });
	Token* ESP = new Token(TOKEN::STACK_POINTTER, "esp", 4, { SP });
	Token* RSP = new Token(TOKEN::STACK_POINTTER, "rsp", 8, { ESP });

	Token* IPL = new Token(TOKEN::POSITION_INDEPENDENT_REGISTER, "ipl", 1, {});
	Token* IP = new Token(TOKEN::POSITION_INDEPENDENT_REGISTER, "ip", 2, {IPL});
	Token* EIP = new Token(TOKEN::POSITION_INDEPENDENT_REGISTER, "eip", 4, { IP });
	Token* RIP = new Token(TOKEN::POSITION_INDEPENDENT_REGISTER, "rip", 8, { EIP });

	Token* XMM0D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::RETURNING | TOKEN::DECIMAL, "xmm0", 4, {});
	Token* XMM1D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm1", 4, {});
	Token* XMM2D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm2", 4, {});
	Token* XMM3D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm3", 4, {});
	Token* XMM4D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm4", 4, {});
	Token* XMM5D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm5", 4, {});
	Token* XMM6D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm6", 4, {});
	Token* XMM7D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm7", 4, {});
	Token* XMM8D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm8", 4, {});
	Token* XMM9D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm9", 4, {});
	Token* XMM10D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xm10", 4, {});
	Token* XMM11D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm11", 4, {});
	Token* XMM12D = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm12", 4, {});
	Token* XMM13D = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL, "xmm13", 4, {});
	Token* XMM14D = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL, "xmm14", 4, {});
	Token* XMM15D = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL, "xmm15", 4, {});

	Token* XMM0Q = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::RETURNING | TOKEN::DECIMAL, "xmm0", 8, {XMM0D});
	Token* XMM1Q = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm1", 8, {XMM1D});
	Token* XMM2Q = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm2", 8, { XMM2D });
	Token* XMM3Q = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm3", 8, { XMM3D });
	Token* XMM4Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm4", 8, { XMM4D });
	Token* XMM5Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm5", 8, { XMM5D });
	Token* XMM6Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm6", 8, { XMM6D });
	Token* XMM7Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm7", 8, { XMM7D });
	Token* XMM8Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm8", 8, { XMM8D });
	Token* XMM9Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm9", 8, { XMM9D });
	Token* XMM10Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xm10", 8, { XMM10D });
	Token* XMM11Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm11", 8, { XMM11D });
	Token* XMM12Q = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm12", 8, { XMM12D });
	Token* XMM13Q = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL, "xmm13", 8, { XMM13D });
	Token* XMM14Q = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL, "xmm14", 8, { XMM14D });
	Token* XMM15Q = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL, "xmm15", 8, { XMM15D });

	Token* XMM0 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::RETURNING | TOKEN::DECIMAL, "xmm0", 12, { XMM0Q });
	Token* XMM1 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm1", 12, { XMM1Q });
	Token* XMM2 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm2", 12, { XMM2Q });
	Token* XMM3 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER | TOKEN::DECIMAL, "xmm3", 12, { XMM3Q });
	Token* XMM4 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm4", 12, { XMM4Q });
	Token* XMM5 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm5", 12, { XMM5Q });
	Token* XMM6 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm6", 12, { XMM6Q });
	Token* XMM7 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm7", 12, { XMM7Q });
	Token* XMM8 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm8", 12, { XMM8Q });
	Token* XMM9 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm9", 12, { XMM9Q });
	Token* XMM10 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xm10", 12, { XMM10Q });
	Token* XMM11 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm11", 12, { XMM11Q });
	Token* XMM12 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "xmm12", 12, { XMM12Q });
	Token* XMM13 = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL, "xmm13", 12, { XMM13Q });
	Token* XMM14 = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL, "xmm14", 12, { XMM14Q });
	Token* XMM15 = new Token(TOKEN::NONVOLATILE | TOKEN::DECIMAL, "xmm15", 12, { XMM15Q });

	Token* R8B = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r8b", 1, {});
	Token* R8W = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r8w", 2, { R8B });
	Token* R8D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r8d", 4, { R8W });
	Token* R8 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r8", 8, { R8D });

	Token* R9B = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r9b", 1, {});
	Token* R9W = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r9w", 2, { R9B });
	Token* R9D = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r9d", 4, { R9W });
	Token* R9 = new Token(TOKEN::VOLATILE | TOKEN::PARAMETER, "r9", 8, { R9D });

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

	if (sys->Info.OS == "win")
		Parameter_Registers = { RCX, RDX, R8, R9, XMM0, XMM1, XMM2, XMM3 };
	else
		Parameter_Registers = { RDI, RSI, RDX, RCX, R8, R9, XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6 };
	Registers = { 
		RAX, EAX, AX, AH, AL,
		RBX, EBX, BX, BH, BL,
		RCX, ECX, CX, CH, CL,
		RDX, EDX, DX, DH, DL,
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
	Token* Register = new Token(REGISTER | NONVOLATILE | VOLATILE | RETURNING | QUOTIENT | REMAINDER | PARAMETER | STACK_POINTTER);
	Token* Register_Float = new Token(REGISTER | NONVOLATILE | VOLATILE | RETURNING | DECIMAL | PARAMETER);
	Token* Scalar = new Token(NUM, {
		new Token(NUM, "1"),
		new Token(NUM, "2"),
		new Token(NUM, "4"),
		new Token(NUM, "8")
		}, "scaler");
	Token* Const = new Token(NUM | STACK_ALLOCATION_CONSTANT, "const");
	Token* Decimal = new Token(DECIMAL | NUM, "const");

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
	
	IR* MOV = new IR("move", new Token(OPERATOR, "mov"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Register, {1, 8}}, {Label, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} }
		});

	IR* SET = new IR("=", new Token(OPERATOR, "mov"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Register, {1, 8}}, {Label, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },

		{ {Memory_Float, {4, 4}}, {Register, {4, 4}} }
		});

	IR* XOR = new IR("�", new Token(OPERATOR, "xor"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Register, {1, 8}}, {Label, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} }
	});

	IR* LEA = new IR("evaluate", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "lea"), {
		{ {Register, { 1, 8 }}, { Memory, {1, 8} } }
		});

	IR* ADD = new IR("+", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "add"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} }
		});

	IR* SUB = new IR("-", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "sub"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} }
		});	

	IR* MUL = new IR("mul", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mul"), {
		{{Register, {1, 8}}},
		{{Memory, {1, 8}}},
		});	

	IR* DIV = new IR("div", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "div"), {
		{{Register, {1, 8}}},
		{{Memory, {1, 8}}},
			});
	
	IR* C_MUL = new IR("*", new Token(OPERATOR), {
		//accepted arguments
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Const, {1, 8}}, {Register, {1, 8}} },
		{{Const, {1, 8}}, {Memory, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* eax = nullptr;
			Token* mul = nullptr;
			if (args[1]->is(NUM)) {
				eax = args[1];
				mul = args[0];
			}
			else {
				eax = args[0];
				mul = args[1];
			}
			Token* quotient = new Token(QUOTIENT | REGISTER, eax->Get_Name() + "_QUOTIENT" + to_string(rand()), eax->Get_Size());
			if (mul->is(NUM)) {
				//you cant give mul a num as a arg so move it to a register.
				Token* tmp = mul;
				mul = new Token(REGISTER, mul->Get_Name() + "_REG" + to_string(rand()), mul->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { mul, tmp }, nullptr));
			}

			//save the rdx if it has some valuable value inside of it.
			//this can occur when a multiplication has been done
			Token* Save_Hold_Remainder = new Token(TOKEN::REGISTER, mul->Get_Name() + "_REMAINDER" + to_string(rand()), _SYSTEM_BIT_SIZE_);
			Token* Remainder = new Token(TOKEN::REMAINDER | TOKEN::REGISTER, "REMAINDER_" + to_string(rand()), _SYSTEM_BIT_SIZE_);

			Result.push_back(new IR(new Token(OPERATOR, "="), { Save_Hold_Remainder, Remainder }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { quotient, eax }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "mul"), { mul }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { args[0], quotient }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { Remainder, Save_Hold_Remainder }, nullptr));
			return Result;
		}
	);

	IR* C_MOD = new IR("%", new Token(OPERATOR), {
		//accepted arguments
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Const, {1, 8}}, {Register, {1, 8}} },
		{{Const, {1, 8}}, {Memory, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* eax = nullptr;
			Token* div = nullptr;
			if (args[1]->is(NUM)) {
				eax = args[1];
				div = args[0];
			}
			else {
				eax = args[0];
				div = args[1];
			}
			Token* quotient = new Token(QUOTIENT | REGISTER, eax->Get_Name() + "_QUOTIENT" + to_string(rand()), eax->Get_Size());
			Token* Remainder = new Token(REMAINDER | REGISTER, eax->Get_Name() + "_REMAINDER" + to_string(rand()), eax->Get_Size());
			if (div->is(NUM)) {
				//you cant give mul a num as a arg so move it to a register.
				Token* tmp = div;
				div = new Token(REGISTER, div->Get_Name() + "_REG" + to_string(rand()), div->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { div, tmp }, nullptr));
			}
			//\u00a4
			Result.push_back(new IR(new Token(OPERATOR, "�"), { Remainder, Remainder }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { quotient, eax }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "div"), { div }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { args[0], Remainder }, nullptr));
			return Result;
		}
	);

	IR* C_DIV = new IR("/", new Token(OPERATOR), {
		//accepted arguments
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Const, {1, 8}}, {Register, {1, 8}} },
		{{Const, {1, 8}}, {Memory, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* eax = nullptr;
			Token* div = nullptr;
			if (args[1]->is(NUM)) {
				eax = args[1];
				div = args[0];
			}
			else {
				eax = args[0];
				div = args[1];
			}
			Token* quotient = new Token(QUOTIENT | REGISTER, eax->Get_Name() + "_QUOTIENT" + to_string(rand()), eax->Get_Size());
			Token* Remainder = new Token(REMAINDER | REGISTER, eax->Get_Name() + "_REMAINDER" + to_string(rand()), eax->Get_Size());
			if (div->is(NUM)) {
				//you cant give mul a num as a arg so move it to a register.
				Token* tmp = div;
				div = new Token(REGISTER, div->Get_Name() + "_REG" + to_string(rand()), div->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { div, tmp }, nullptr));
			}
			//\u00a4
			Result.push_back(new IR(new Token(OPERATOR, "�"), { Remainder, Remainder }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { quotient, eax }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "div"), { div }, nullptr));
			Result.push_back(new IR(new Token(OPERATOR, "="), { args[0], quotient }, nullptr));
			return Result;
		}
	);

	IR* MOVQ = new IR("=", new Token(OPERATOR, "movq"), {
		{{Register_Float, {8, 12}}, {Register, {8, 8}}},
		{{Register, {8, 8}}, {Register_Float, {8, 8}}},
	});	

	IR* MOVD = new IR("=", new Token(OPERATOR, "movd"), {
		{{Register_Float, {4, 4}}, {Register, {4, 4}}},
		{{Register, {4, 4}}, {Register_Float, {4, 4}}},
	});

	IR* MOVSS = new IR("=", new Token(OPERATOR, "movss"), {
		{{Register_Float, {4, 4}}, {Register_Float, {4, 4}}},
		{{Register_Float, {4, 4}}, {Memory_Float, {4, 4}}},
		{{Memory_Float, {4, 4}}, {Register_Float, {4, 4}}},
	});

	IR* MOVSD = new IR("=", new Token(OPERATOR, "movsd"), {
		{{Register_Float, {8, 8}}, {Register_Float, {8, 8}}},
		{{Register_Float, {8, 8}}, {Memory_Float, {8, 8}}},
		{{Memory_Float, {8, 8}}, {Register_Float, {8, 8}}},
	});

	IR* CONVERTI2F = new IR("convert", new Token(OPERATOR, "cvtsi2ss"), {
		{{Register_Float, {4, 4}}, {Memory, {4, 4}}},
		{{Register_Float, {4, 4}}, {Register, {4, 4}}},
	});

	IR* CONVERTI2D = new IR("convert", new Token(OPERATOR, "cvtsi2sd"), {
		{{Register_Float, {8, 12}}, {Memory, {4, 8}}},
		{{Register_Float, {8, 12}}, {Register, {4, 8}}},
	});

	IR* CONVERTF2I = new IR("convert", new Token(OPERATOR, "cvttss2si"), {
		{{Register, {4, 8}}, {Register_Float, {4, 4}}},
		{{Register, {4, 8}}, {Memory_Float, {4, 4}}},
	});

	IR* CONVERTD2I = new IR("convert", new Token(OPERATOR, "cvttsd2si"), {
		{{Register, {4, 8}}, {Register_Float, {8, 12}}},
		{{Register, {4, 8}}, {Memory_Float, {8, 12}}},
		});

	IR* CONVERTD2F = new IR("convert", new Token(OPERATOR, "cvtsd2ss"), {
		{{Register_Float, {4, 4}}, {Register_Float, {8, 12}}},
		{{Register_Float, {4, 4}}, {Memory_Float, {8, 12}}},
		});

	IR* CONVERTF2D = new IR("convert", new Token(OPERATOR, "cvtss2sd"), {
	{{Register_Float, {8, 12}}, {Register_Float, {4, 4}}},
	{{Register_Float, {8, 12}}, {Register_Float, {4, 4}}},
	});


	IR* F_MOV = new IR("=", new Token(OPERATOR), {
		//accepted arguments
		{{Register_Float, {4, 12}}, {Memory, {4, 8}} },
		{{Memory, {4, 8}}, {Register_Float, {4, 12}} },
		{{Register_Float, {4, 12}}, {Memory_Float, {4, 8}} },
		{{Memory_Float, {4, 8}}, {Register_Float, {4, 12}} },
		{{Memory_Float, {4, 8}}, {Decimal, {4, 12}} },
		{{Register_Float, {4, 12}}, {Register_Float, {4, 12}} },
		{{Register_Float, {4, 12}}, {Const, {4, 8}} },
		{{Memory, {4, 8}}, {Const, {4, 8}} },
		{{Register_Float, {4, 12}}, {Decimal, {4, 8}} },
		{{Memory, {4, 8}}, {Decimal, {4, 8}} },
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
		{{Register_Float, {4, 8}}, {Memory_Float, {4, 8}} },
		{{Memory_Float, {4, 8}}, {Register_Float, {4, 8}} },
		{{Register_Float, {4, 8}}, {Register_Float, {4, 8}} },
		{{Register_Float, {4, 8}}, {Decimal, {4, 8}} },
		{{Memory_Float, {4, 8}}, {Decimal, {4, 8}} },
		{ {Decimal, {4, 8}}, {Register_Float, {4, 8}} },
		{{Decimal, {4, 8}}, {Memory_Float, {4, 8}} }
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
		{{Register_Float, {4, 8}}, {Memory_Float, {4, 8}} },
		{{Memory_Float, {4, 8}}, {Register_Float, {4, 8}} },
		{{Register_Float, {4, 8}}, {Register_Float, {4, 8}} },
		{{Register_Float, {4, 8}}, {Decimal, {4, 8}} },
		{{Memory_Float, {4, 8}}, {Decimal, {4, 8}} },
		{ {Decimal, {4, 8}}, {Register_Float, {4, 8}} },
		{{Decimal, {4, 8}}, {Memory_Float, {4, 8}} }
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
		{{Register_Float, {4, 8}}, {Memory_Float, {4, 8}} },
		{{Memory_Float, {4, 8}}, {Register_Float, {4, 8}} },
		{{Register_Float, {4, 8}}, {Register_Float, {4, 8}} },
		{{Register_Float, {4, 8}}, {Decimal, {4, 8}} },
		{{Memory_Float, {4, 8}}, {Decimal, {4, 8}} },
		{ {Decimal, {4, 8}}, {Register_Float, {4, 8}} },
		{{Decimal, {4, 8}}, {Memory_Float, {4, 8}} }
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
		{{Register_Float, {4, 8}}, {Memory_Float, {4, 8}} },
		{{Memory_Float, {4, 8}}, {Register_Float, {4, 8}} },
		{{Register_Float, {4, 8}}, {Register_Float, {4, 8}} },
		{{Register_Float, {4, 8}}, {Decimal, {4, 8}} },
		{{Memory_Float, {4, 8}}, {Decimal, {4, 8}} },
		{ {Decimal, {4, 8}}, {Register_Float, {4, 8}} },
		{{Decimal, {4, 8}}, {Memory_Float, {4, 8}} }
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
		{{Register_Float, {4, 4}}, {Memory_Float, {4, 4}} },
		{{Memory_Float, {4, 4}}, {Register_Float, {4, 4}} },
		{{Register_Float, {4, 4}}, {Register_Float, {4, 4}} },
		{{Register_Float, {4, 4}}, {Decimal, {4, 4}} },
		{{Memory_Float, {4, 4}}, {Decimal, {4, 4}} }
	});

	IR* F_ADDSD = new IR("addF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "addsd"), {
		{{Register_Float, {8, 8}}, {Memory_Float, {8, 8}} },
		{{Memory_Float, {8, 8}}, {Register_Float, {8, 8}} },
		{{Register_Float, {8, 8}}, {Register_Float, {8, 8}} },
		{{Register_Float, {8, 8}}, {Decimal, {8, 8}} },
		{{Memory_Float, {8, 8}}, {Decimal, {8, 8}} }
	});

	IR* F_SUBSS = new IR("subF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "subss"), {
		{{Register_Float, {4, 4}}, {Memory_Float, {4, 4}} },
		{{Memory_Float, {4, 4}}, {Register_Float, {4, 4}} },
		{{Register_Float, {4, 4}}, {Register_Float, {4, 4}} },
		{{Register_Float, {4, 4}}, {Decimal, {4, 4}} },
		{{Memory_Float, {4, 4}}, {Decimal, {4, 4}} }
	});

	IR* F_SUBSD = new IR("subF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "subsd"), {
		{{Register_Float, {8, 8}}, {Memory_Float, {8, 8}} },
		{{Memory_Float, {8, 8}}, {Register_Float, {8, 8}} },
		{{Register_Float, {8, 8}}, {Register_Float, {8, 8}} },
		{{Register_Float, {8, 8}}, {Decimal, {8, 8}} },
		{{Memory_Float, {8, 8}}, {Decimal, {8, 8}} }
	});

	IR* F_MULSS = new IR("mulF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mulss"), {
		{{Register_Float, {4, 4}}, {Memory_Float, {4, 4}} },
		{{Memory_Float, {4, 4}}, {Register_Float, {4, 4}} },
		{{Register_Float, {4, 4}}, {Register_Float, {4, 4}} },
		{{Register_Float, {4, 4}}, {Decimal, {4, 4}} },
		{{Memory_Float, {4, 4}}, {Decimal, {4, 4}} }
	});

	IR* F_MULSD = new IR("mulF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mulsd"), {
		{{Register_Float, {8, 8}}, {Memory_Float, {8, 8}} },
		{{Memory_Float, {8, 8}}, {Register_Float, {8, 8}} },
		{{Register_Float, {8, 8}}, {Register_Float, {8, 8}} },
		{{Register_Float, {8, 8}}, {Decimal, {8, 8}} },
		{{Memory_Float, {8, 8}}, {Decimal, {8, 8}} }
	});

	IR* F_DIVSS = new IR("divF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "divss"), {
		{{Register_Float, {4, 4}}, {Memory_Float, {4, 4}} },
		{{Memory_Float, {4, 4}}, {Register_Float, {4, 4}} },
		{{Register_Float, {4, 4}}, {Register_Float, {4, 4}} },
		{{Register_Float, {4, 4}}, {Decimal, {4, 4}} },
		{{Memory_Float, {4, 4}}, {Decimal, {4, 4}} }
	});

	IR* F_DIVSD = new IR("divF", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "divsd"), {
		{{Register_Float, {8, 8}}, {Memory_Float, {8, 8}} },
		{{Memory_Float, {8, 8}}, {Register_Float, {8, 8}} },
		{{Register_Float, {8, 8}}, {Register_Float, {8, 8}} },
		{{Register_Float, {8, 8}}, {Decimal, {8, 8}} },
		{{Memory_Float, {8, 8}}, {Decimal, {8, 8}} }
	});

	IR* CMP = new IR("compare", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "cmp"), {
		{{Register, {1, 8}}, {Register, {1, 8}}},
		{{Register, {1, 8}}, {Memory, {1, 8}}},
		{{Memory, {1, 8}}, {Register, {1, 8}}},
		{{Register,  {1, 8}}, {Const, {1, 8}}},
		{ {Memory,  {1, 8}}, {Const, {1, 8}}}
		});

	IR* JMP = new IR("jump", new Token(FLOW, "jmp"), { {{Label, {0, 0}}} });
	IR* JE = new IR("==", new Token(FLOW, "je"), { {{Label, {0, 0}}} });
	IR* JNE = new IR("!=", new Token(FLOW, "jne"), { {{Label, {0, 0}}} });
	IR* JL = new IR("<", new Token(FLOW, "jl"), { {{Label, {0, 0}}} });
	IR* JLE = new IR("<=", new Token(FLOW, "jle"), { {{Label, {0, 0}}} });
	IR* JNL = new IR("!<", new Token(FLOW, "jnl"), { {{Label, {0, 0}}} });
	IR* JG = new IR(">", new Token(FLOW, "jg"), { {{Label, {0, 0}}} });
	IR* JGE = new IR(">=", new Token(FLOW, "jge"), { {{Label, {0, 0}}} });
	IR* JNG = new IR("!>", new Token(FLOW, "jng"), { {{Label, {0, 0}}} });

	IR* RET = new IR("return", new Token(FLOW, "ret"), vector<vector<pair<Token*, pair<int, int>>>>{});

	IR* PUSH = new IR("push", new Token(OPERATOR, "push"), {
	{{Memory, {2, 8}}},
	{{Register, {2, 8}}},
	{{Const, {1, 4}}},
		}); 
	IR* POP = new IR("pop", new Token(OPERATOR, "pop"), {
	{{Memory, {2, 8}}},
	{{Register, {2, 8}}},
			});

	IR* CALL = new IR("call", new Token(TOKEN::CALL, "call"), {
		{{Label, {0, 0}}},
		{{Register, {_SYSTEM_BIT_SIZE_, _SYSTEM_BIT_SIZE_}}},
		{ {Memory, {_SYSTEM_BIT_SIZE_, _SYSTEM_BIT_SIZE_}}}
	});	

	IR* GLOBAL = new IR("global", new Token(TOKEN::GLOBAL_LABEL, ".global"), {
		{{Label, {0, 0}}}
		}); 
	IR* EXTERN = new IR("extern", new Token(TOKEN::GLOBAL_LABEL, ".extern"), {
		{{Label, {0, 0}}}
	});
	IR* SECTION = new IR("section", new Token(TOKEN::OPERATOR, ".section"), {
		{{Label, {0, 0}}}
	});
	IR* FILE = new IR("file", new Token(TOKEN::OPERATOR, ".file"), {
		{{Label, {0, 1}}}
	});

	IR* DB = new IR("init", new Token(TOKEN::SET_DATA, ".byte"), {
		{{Data, {1, 1}}}
		}); 
	IR* ASCII = new IR("ascii", new Token(TOKEN::SET_DATA, ".asciz"), {
		{{Data, {0, 1}}}
	});
	IR* DW = new IR("init", new Token(TOKEN::SET_DATA, ".word"), {
		{{Data, {2, 2}}}
		});
	IR* DD = new IR("init", new Token(TOKEN::SET_DATA, ".long"), {
		{{Data, {4, 4}}}
		});
	IR* DQ = new IR("init", new Token(TOKEN::SET_DATA, ".quad"), {
		{{Data, {8, 8}}}
		});
	IR* SECREL32 = new IR("secrel32", new Token(TOKEN::SET_DATA, ".secrel32"), {
		{{Data, {4, 8}}}
	});
	IR* LOCATOIN = new IR("location", new Token(TOKEN::SET_DATA, ".loc"), {
		{{Data, {0, 0}}}
	});
	IR* CFI_START = new IR("cfi_start", new Token(TOKEN::SET_DATA, ".cfi_startproc"), {});
	IR* CFI_END = new IR("cfi_end", new Token(TOKEN::SET_DATA, ".cfi_endproc"), {});
	IR* CFI_OFFSET = new IR("cfi_offset", new Token(TOKEN::SET_DATA, ".cfi_def_cfa_offset"), {
		{{Data, {0, 4}}}
	});


	Opcodes = {
		MOV,
		LEA,
		ADD,
		SUB,
		MUL,
		C_MUL,
		DIV,
		C_DIV,
		C_MOD,
		CMP,
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
