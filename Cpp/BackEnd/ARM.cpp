#include "../../H/BackEnd/ARM.h"
extern unsigned long long Reg_Random_ID_Addon;

void ARM_64::Init() {
	size = 8;	//64 bit arch

	Seperator = ",";
	Register_Pre_Fix = "";
	Number_Pre_Fix = "";
	Label_Post_Fix = ":";

	using namespace TOKEN;
	Token* Register = new Token(REGISTER | NONVOLATILE | VOLATILE | RETURNING | QUOTIENT | REMAINDER | PARAMETER | STACK_POINTTER);
	Token* Register_Float = new Token(REGISTER | NONVOLATILE | VOLATILE | RETURNING | DECIMAL | PARAMETER);
	Token* Scalar = new Token(NUM, {
		new Token(NUM, "1"),
		new Token(NUM, "2"),
		new Token(NUM, "4"),
		new Token(NUM, "8")
		}, "scaler");
	Token* Const = new Token(NUM, "const");
	Token* Decimal = new Token(DECIMAL | NUM, "const");
	Token* Memory = new Token(MEMORY, {
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
	Token* Memory_Float = new Token(MEMORY | DECIMAL, {
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
	Token* Data = new Token(NUM | STRING);
	Utility = {
		Register,
		Scalar,
		Const,
		Memory,
		Label,
		Data
	};

	Token* BYTE = new Token(SIZE_INDENTIFIER, "", 1);
	Token* WORD = new Token(SIZE_INDENTIFIER, "", 2);
	Token* DWORD = new Token(SIZE_INDENTIFIER, "", 4);
	Token* QWORD = new Token(SIZE_INDENTIFIER, "", 8);
	Size_Identifiers = {
		BYTE,
		WORD,
		DWORD,
		QWORD
	};


	Token* W0B = new Token(TOKEN::REGISTER | TOKEN::RETURNING, "w0", 1, {});
	Token* W0W = new Token(TOKEN::REGISTER | TOKEN::RETURNING, "w0", 2, {W0B});
	Token* W0D = new Token(TOKEN::REGISTER | TOKEN::RETURNING, "w0", 4, {W0W});
	Token* X0 = new Token(TOKEN::REGISTER | TOKEN::RETURNING, "x0", 8, { W0D });

	Token* W1B = new Token(TOKEN::REGISTER, "w1", 1, {});
	Token* W1W = new Token(TOKEN::REGISTER, "w1", 2, { W1B });
	Token* W1D = new Token(TOKEN::REGISTER, "w1", 4, { W1W });
	Token* X1 = new Token(TOKEN::REGISTER, "x1", 8, { W1D });

	Token* W2B = new Token(TOKEN::REGISTER, "w2", 1, {});
	Token* W2W = new Token(TOKEN::REGISTER, "w2", 2, { W2B });
	Token* W2D = new Token(TOKEN::REGISTER, "w2", 4, { W2W });
	Token* X2 = new Token(TOKEN::REGISTER, "x2", 8, { W2D });

	Token* W3B = new Token(TOKEN::REGISTER, "w3", 1, {});
	Token* W3W = new Token(TOKEN::REGISTER, "w3", 2, { W3B });
	Token* W3D = new Token(TOKEN::REGISTER, "w3", 4, { W3W });
	Token* X3 = new Token(TOKEN::REGISTER, "x3", 8, { W3D });

	Token* W4B = new Token(TOKEN::REGISTER, "w4", 1, {});
	Token* W4W = new Token(TOKEN::REGISTER, "w4", 2, { W4B });
	Token* W4D = new Token(TOKEN::REGISTER, "w4", 4, { W4W });
	Token* X4 = new Token(TOKEN::REGISTER, "x4", 8, { W4D });

	Token* W5B = new Token(TOKEN::REGISTER, "w5", 1, {});
	Token* W5W = new Token(TOKEN::REGISTER, "w5", 2, { W5B });
	Token* W5D = new Token(TOKEN::REGISTER, "w5", 4, { W5W });
	Token* X5 = new Token(TOKEN::REGISTER, "x5", 8, { W5D });

	Token* W6B = new Token(TOKEN::REGISTER, "w6", 1, {});
	Token* W6W = new Token(TOKEN::REGISTER, "w6", 2, { W6B });
	Token* W6D = new Token(TOKEN::REGISTER, "w6", 4, { W6W });
	Token* X6 = new Token(TOKEN::REGISTER, "x6", 8, { W6D });

	Token* W7B = new Token(TOKEN::REGISTER, "w7", 1, {});
	Token* W7W = new Token(TOKEN::REGISTER, "w7", 2, { W7B });
	Token* W7D = new Token(TOKEN::REGISTER, "w7", 4, { W7W });
	Token* X7 = new Token(TOKEN::REGISTER, "x7", 8, { W7D });

	Token* W8B = new Token(TOKEN::REGISTER, "w8", 1, {});
	Token* W8W = new Token(TOKEN::REGISTER, "w8", 2, { W8B });
	Token* W8D = new Token(TOKEN::REGISTER, "w8", 4, { W8W });
	Token* X8 = new Token(TOKEN::REGISTER, "x8", 8, { W8D });

	Token* W9B = new Token(TOKEN::REGISTER, "w9", 1, {});
	Token* W9W = new Token(TOKEN::REGISTER, "w9", 2, { W9B });
	Token* W9D = new Token(TOKEN::REGISTER, "w9", 4, { W9W });
	Token* X9 = new Token(TOKEN::REGISTER, "x9", 8, { W9D });

	Token* W10B = new Token(TOKEN::REGISTER, "w10", 1, {});
	Token* W10W = new Token(TOKEN::REGISTER, "w10", 2, { W10B });
	Token* W10D = new Token(TOKEN::REGISTER, "w10", 4, { W10W });
	Token* X10 = new Token(TOKEN::REGISTER, "x10", 8, { W10D });

	Token* W11B = new Token(TOKEN::REGISTER, "w11", 1, {});
	Token* W11W = new Token(TOKEN::REGISTER, "w11", 2, { W11B });
	Token* W11D = new Token(TOKEN::REGISTER, "w11", 4, { W11W });
	Token* X11 = new Token(TOKEN::REGISTER, "x11", 8, { W11D });

	Token* W12B = new Token(TOKEN::REGISTER, "w12", 1, {});
	Token* W12W = new Token(TOKEN::REGISTER, "w12", 2, { W12B });
	Token* W12D = new Token(TOKEN::REGISTER, "w12", 4, { W12W });
	Token* X12 = new Token(TOKEN::REGISTER, "x12", 8, { W12D });

	Token* W13B = new Token(TOKEN::REGISTER, "w13", 1, {});
	Token* W13W = new Token(TOKEN::REGISTER, "w13", 2, { W13B });
	Token* W13D = new Token(TOKEN::REGISTER, "w13", 4, { W13W });
	Token* X13 = new Token(TOKEN::REGISTER, "x13", 8, { W13D });

	Token* W14B = new Token(TOKEN::REGISTER, "w14", 1, {});
	Token* W14W = new Token(TOKEN::REGISTER, "w14", 2, { W14B });
	Token* W14D = new Token(TOKEN::REGISTER, "w14", 4, { W14W });
	Token* X14 = new Token(TOKEN::REGISTER,  "x14", 8, { W14D });

	Token* W15B = new Token(TOKEN::REGISTER, "w15", 1, {});
	Token* W15W = new Token(TOKEN::REGISTER, "w15", 2, { W15B });
	Token* W15D = new Token(TOKEN::REGISTER, "w15", 4, { W15W });
	Token* X15 = new Token(TOKEN::REGISTER,  "x15", 8, { W15D });

	Token* W16B = new Token(TOKEN::REGISTER, "w16", 1, {});
	Token* W16W = new Token(TOKEN::REGISTER, "w16", 2, { W16B });
	Token* W16D = new Token(TOKEN::REGISTER, "w16", 4, { W16W });
	Token* X16 = new Token(TOKEN::REGISTER, "x16", 8, { W16D });

	Token* W17B = new Token(TOKEN::REGISTER, "w17", 1, {});
	Token* W17W = new Token(TOKEN::REGISTER, "w17", 2, { W17B });
	Token* W17D = new Token(TOKEN::REGISTER, "w17", 4, { W17W });
	Token* X17 = new Token(TOKEN::REGISTER, "x17", 8, { W17D });

	Token* W18B = new Token(TOKEN::REGISTER, "w18", 1, {});
	Token* W18W = new Token(TOKEN::REGISTER, "w18", 2, { W18B });
	Token* W18D = new Token(TOKEN::REGISTER, "w18", 4, { W18W });
	Token* X18 = new Token(TOKEN::REGISTER, "x18", 8, { W18D });

	Token* W19B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w19", 1, {});
	Token* W19W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w19", 2, { W19B });
	Token* W19D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w19", 4, { W19W });
	Token* X19 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x19", 8, { W19D });

	Token* W20B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w20", 1, {});
	Token* W20W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w20", 2, { W20B });
	Token* W20D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w20", 4, { W20W });
	Token* X20 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x20", 8, { W20D });

	Token* W21B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w21", 1, {});
	Token* W21W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w21", 2, { W21B });
	Token* W21D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w21", 4, { W21W });
	Token* X21 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x21", 8, { W21D });

	Token* W22B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w22", 1, {});
	Token* W22W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w22", 2, { W22B });
	Token* W22D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w22", 4, { W22W });
	Token* X22 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x22", 8, { W22D });

	Token* W23B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w23", 1, {});
	Token* W23W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w23", 2, { W23B });
	Token* W23D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w23", 4, { W23W });
	Token* X23 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x23", 8, { W23D });

	Token* W24B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w24", 1, {});
	Token* W24W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w24", 2, { W24B });
	Token* W24D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w24", 4, { W24W });
	Token* X24 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x24", 8, { W24D });

	Token* W25B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w25", 1, {});
	Token* W25W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w25", 2, { W25B });
	Token* W25D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w25", 4, { W25W });
	Token* X25 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x25", 8, { W25D });

	Token* W26B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w26", 1, {});
	Token* W26W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w26", 2, { W26B });
	Token* W26D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w26", 4, { W26W });
	Token* X26 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x26", 8, { W26D });

	Token* W27B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w27", 1, {});
	Token* W27W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w27", 2, { W27B });
	Token* W27D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w27", 4, { W27W });
	Token* X27 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x27", 8, { W27D });

	Token* W28B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w28", 1, {});
	Token* W28W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w28", 2, { W28B });
	Token* W28D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w28", 4, { W28W });
	Token* X28 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x28", 8, { W28D });

	Token* W29B = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w29", 1, {});
	Token* W29W = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w29", 2, { W29B });
	Token* W29D = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "w29", 4, { W29W });
	Token* X29 = new Token(TOKEN::REGISTER | TOKEN::NONVOLATILE, "x29", 8, { W29D });

	Token* SP = new Token(TOKEN::STACK_POINTTER, "sp", 8, {});

	Parameter_Registers = { X0, X1, X2, X3, X4, X5, X6, X7 };
	Registers = {
		W0B, W0W, W0D, X0,
		W1B, W1W, W1D, X1,
		W2B, W2W, W2D, X3,
		W4B, W4W, W4D, X4,
		W5B, W5W, W5D, X5,
		W6B, W6W, W6D, X6,
		W7B, W7W, W7D, X7,
		W8B, W8W, W8D, X8,
		W9B, W9W, W9D, X9,
		W10B, W10W, W10D, X10,
		W11B, W11W, W11D, X11,
		W12B, W12W, W12D, X12,
		W13B, W13W, W13D, X13,
		W14B, W14W, W14D, X14,
		W15B, W15W, W15D, X15,
		W16B, W16W, W16D, X16,
		W17B, W17W, W17D, X17,
		W18B, W18W, W18D, X18,
		W19B, W19W, W19D, X19,
		W20B, W20W, W20D, X20,
		W21B, W21W, W21D, X21,
		W22B, W22W, W22D, X22,
		W23B, W23W, W23D, X23,
		W24B, W24W, W24D, X24,
		W25B, W25W, W25D, X25,
		W26B, W26W, W26D, X26,
		W27B, W27W, W27D, X27,
		W28B, W28W, W28D, X28,
		W29B, W29W, W29D, X29,
		SP,
	};

	IR* MOV_ALL = new IR("=", new Token(OPERATOR), {
		//accepted arguments
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];
			string Move = "mov";	//some genious decided that every move operator must have its own opcode naming :/

			if (Right->is(NUM)) {
				if (Left->is(REGISTER)) {
					long long Num = atoll(Right->Get_Name().c_str());
					if (Num > UINT16_MAX) {
						/*
						mov w0, 0001 0000 0000 0000
						mov w1, 0000 0000 0000 0001 
						lsl w1, w1, 16
						orr w0, w0, w1
						*/
						long long Chunk1 = Num & 0xffff;
						Token* Reg1 = new Token(REGISTER, "REG_" + to_string(Reg_Random_ID_Addon++), 4);
						Result.push_back(new IR(new Token(OPERATOR, "mov"), { Reg1, new Token(NUM, to_string(Chunk1), 4) }));
					
						long long Chunk2 = (Num >> 16 ) & 0xffff;
						Token* Reg2 = new Token(REGISTER, "REG_" + to_string(Reg_Random_ID_Addon++), 4);
						Result.push_back(new IR(new Token(OPERATOR, "mov"), { Reg1, new Token(NUM, to_string(Chunk2), 4) }));

						Result.push_back(new IR(new Token(OPERATOR, "lsl"), { Reg2, Reg2, new Token(NUM, to_string(16)) }));
						Result.push_back(new IR(new Token(OPERATOR, "orr"), { Reg1, Reg1, Reg2 }));
					}
				}
				else {
					//of memory
					Token* Reg1 = new Token(REGISTER, "REG_" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
					Result.push_back(new IR(new Token(OPERATOR, "="), { Reg1, Right }));

					Result.push_back(new IR(new Token(OPERATOR, "="), { Left, Reg1 }));
				}
			}

			if (Left->is(MEMORY)) {
				Token* tmp = Left;
				Left = Right;	//because some genious decided that storing must be left to right :/
				Right = tmp;
				Move = "str";
			}
			else if (Right->is(MEMORY)) {
				Move = "ldr";
			}
			
			Result.push_back(new IR(new Token(OPERATOR, Move), { Left, Right }));

			return Result;
		}
	);

	IR* MOVE = new IR(*MOV_ALL);
	MOVE->ID = "move";

	IR* MOV = new IR("mov", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mov"), {
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
	});

	IR* LDR = new IR("ldr", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "ldr"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		});

	IR* STR = new IR("str", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "str"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		});

	IR* LSL = new IR("lsl", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "lsl"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, { Const, {1, 8}} },
	});

	IR* LSR = new IR("lsr", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "lsr"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, { Const, {1, 8}} },
	});

	IR* SHIFT_LEFT = new IR("<<", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
	},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Result.push_back(new IR(new Token(OPERATOR, "lsl"), { args[0], args[0], args[1] }));
			return Result;
		}
	);

	IR* SHIFT_RIGHT = new IR(">>", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
	{{Memory, {1, 8}}, {Register, {1, 8}} },
	{{Register, {1, 8}}, {Register, {1, 8}} },
	{{Register, {1, 8}}, {Const, {1, 8}} },
	{{Memory, {1, 8}}, {Const, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Result.push_back(new IR(new Token(OPERATOR, "lsr"), { args[0], args[0], args[1] }));
			return Result;
		}
	);

	IR* ORR = new IR("orr", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "orr"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, { Const, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}}, { Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}}, { Const, {1, 8}} },
		});

	IR* OR = new IR("|", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
	},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Result.push_back(new IR(new Token(OPERATOR, "orr"), { args[0], args[0], args[1] }));
			return Result;
		}
	);

	IR* ADD_LAMBDA = new IR("+", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
	},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];

			if (Right->is(NUM) && atoll(Right->Get_Name().c_str()) > 4095) {	//max 12bit number
				Token* Reg1 = new Token(REGISTER, "REG_" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { Reg1, Right }));

				Right = Reg1;
			}

			Result.push_back(new IR(new Token(OPERATOR, "add"), { Left, Left, Right }));

			return Result;
		}
	);

	IR* SUB_LAMBDA = new IR("-", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
	{{Register, {1, 8}}, {Memory, {1, 8}} },
	{{Memory, {1, 8}}, {Register, {1, 8}} },
	{{Register, {1, 8}}, {Register, {1, 8}} },
	{{Register, {1, 8}}, {Const, {1, 8}} },
	{{Memory, {1, 8}}, {Const, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];

			if (Right->is(NUM) && atoll(Right->Get_Name().c_str()) > 4095) {	//max 12bit number
				Token* Reg1 = new Token(REGISTER, "REG_" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { Reg1, Right }));

				Right = Reg1;
			}

			Result.push_back(new IR(new Token(OPERATOR, "sub"), { Left, Left, Right }));

			return Result;
		}
	);

	IR* ADD = new IR("add", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "add"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Memory, {1, 8}}, {Const, {1, 8}} },
	});

	IR* SUB = new IR("sub", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "sub"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Memory, {1, 8}}, {Const, {1, 8}} },
	});


	IR* MUL_LAMBDA = new IR("*", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];

			if (Right->is(NUM)) {
				Token* Reg1 = new Token(REGISTER, "REG_" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { Reg1, Right }));

				Right = Reg1;
			}

			Result.push_back(new IR(new Token(OPERATOR, "mul"), { Left, Left, Right }));

			return Result;
		}
	);

	IR* MUL = new IR("mul", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mul"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}}, {Register, {1, 8}} },
	});

	IR* DIV_LAMBDA = new IR("/", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];

			if (Right->is(NUM)) {
				Token* Reg1 = new Token(REGISTER, "REG_" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { Reg1, Right }));

				Right = Reg1;
			}

			Result.push_back(new IR(new Token(OPERATOR, "div"), { Left, Left, Right }));

			return Result;
		}
	);

	IR* DIV = new IR("div", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "div"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}}, {Register, {1, 8}} },
		});

	IR* LEA_MEM = new IR("evaluate", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
	},
	[](vector<Token*> args) {
			vector<IR*> Result;
			//un-wrap memory contents into argument styled listing.
			string Eval_Type = "add";

			pair<vector<Token*>, bool> tmp = Un_Wrap_Content(args[1]);

			tmp.first.insert(tmp.first.begin(), args[0]);

			if (!tmp.second)
				Eval_Type = "sub";

			Result.push_back(new IR(new Token(OPERATOR, Eval_Type), tmp.first));

			return Result;
		}
	);

	IR* LEA_LABEL = new IR("evaluate", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Register, {1, 8}}, {Label, {0, 0}} },
	},
	[](vector<Token*> args) {
			vector<IR*> Result;

			//adrp reg1, :got:label
			//ldr reg1, [reg1, :got_lo12:label]

			Result.push_back(new IR(new Token(OPERATOR, "adrp"), {
				args[0], new Token(LABEL, ":got:" + args[1]->Get_Name(), 0)
			}));

			Result.push_back(new IR(new Token(OPERATOR, "ldr"), {
				args[0], new Token(MEMORY, "MEM_" + args[1]->Get_Name(), _SYSTEM_BIT_SIZE_, {new Token(OFFSETTER, ",", args[0], new Token(LABEL, ":got_lo12:" + args[1]->Get_Name(), 0))})
			}));

			return Result;
		}
	);

	IR* ADRP = new IR("adrp", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), { {
		{Register, {1, 8}}, {Label, {0, 0}} },
	});

	IR* BL = new IR("call", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "bl"), {
		{{Label, {0, 0}}},
		{{Register, {_SYSTEM_BIT_SIZE_, _SYSTEM_BIT_SIZE_}}},
	});

	IR* CMP = new IR("compare", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "cmp"), {
		{{Register, {1, 8}}, {Register, {1, 8}}},
		{{Register, {1, 8}}, {Memory, {1, 8}}},
		{{Memory, {1, 8}}, {Register, {1, 8}}},
		{{Register,  {1, 8}}, {Const, {1, 8}}}
	});

	IR* B = new IR("jump", new Token(FLOW, "b"), { {{Label, {0, 0}}} });
	IR* BEQ = new IR("==", new Token(FLOW, "b.eq"), { {{Label, {0, 0}}} });
	IR* BNE = new IR("!=", new Token(FLOW, "b.ne"), { {{Label, {0, 0}}} });
	IR* BLE = new IR("<", new Token(FLOW, "b.lt"), { {{Label, {0, 0}}} });
	IR* BLT = new IR("<=", new Token(FLOW, "b.le"), { {{Label, {0, 0}}} });
	IR* BNL = new IR("!<", new Token(FLOW, "b.ge"), { {{Label, {0, 0}}} });
	IR* BGE = new IR(">", new Token(FLOW, "b.gt"), { {{Label, {0, 0}}} });
	IR* BGT = new IR(">=", new Token(FLOW, "b.ge"), { {{Label, {0, 0}}} });
	IR* BNG = new IR("!>", new Token(FLOW, "b.le"), { {{Label, {0, 0}}} });

	IR* RET = new IR("return", new Token(FLOW, "ret"), {});

	IR* GLOBAL = new IR("global", new Token(TOKEN::GLOBAL_LABEL, ".global"), {
		{{Label, {0, 0}}}
		});
	IR* EXTERN = new IR("extern", new Token(TOKEN::GLOBAL_LABEL, ".extern"), {
		{{Label, {0, 0}}}
		});

	IR* PUSH = new IR("push", new Token(TOKEN::OPERATOR), 
		{
			{{Register, {1, 8}}},
		}, 
		[](vector<Token*> args) {
			vector<IR*> Result;

			Token* Stack = new Token(STACK_POINTTER | REGISTER, ".STACK", _SYSTEM_BIT_SIZE_);

			//str args[0], [sp]
			Result.push_back(new IR(new Token(OPERATOR, "str"), {
				args[0], new Token(MEMORY,args[0]->Get_Name() + "stack" , args[0]->Get_Size(), {Stack})
			}));

			//sub sp, sp, args[0].size
			Result.push_back(new IR(new Token(OPERATOR, "sub"), {
				Stack, Stack, new Token(NUM, to_string(args[0]->Get_Size()), _SYSTEM_BIT_SIZE_)
			}));

			return Result;
		}
	);

	IR* POP = new IR("pop", new Token(TOKEN::OPERATOR),
		{
			{{Register, {1, 8}}},
		},
		[](vector<Token*> args) {
			vector<IR*> Result;

			Token* Stack = new Token(STACK_POINTTER | REGISTER, ".STACK", _SYSTEM_BIT_SIZE_);

			//ldr args[0], [sp]
			Result.push_back(new IR(new Token(OPERATOR, "ldr"), {
				args[0], new Token(MEMORY,args[0]->Get_Name() + "stack" , args[0]->Get_Size(), {Stack})
				}));

			//add sp, sp, args[0].size
			Result.push_back(new IR(new Token(OPERATOR, "add"), {
				Stack, Stack, new Token(NUM, to_string(args[0]->Get_Size()), _SYSTEM_BIT_SIZE_)
				}));

			return Result;
		}
	);

	Opcodes = {
		MOV_ALL, MOVE, MOV, LDR, STR,
		LSL, LSR, SHIFT_LEFT, SHIFT_RIGHT,
		ORR, OR,
		ADD_LAMBDA, ADD, LEA_MEM, LEA_LABEL, ADRP,
		SUB_LAMBDA, SUB,
		MUL, MUL_LAMBDA, DIV, DIV_LAMBDA,
		BL, B, BEQ, BNE, BLE, BLT, BNL, BGE, BGT, BNG,
		RET, PUSH, POP,
		GLOBAL, EXTERN,
	};
}

pair<vector<Token*>, bool> ARM_64::Un_Wrap_Content(Token* t)
{
	vector<Token*> Result;
	bool Positive_Offsetter = true;

	if (t->is(TOKEN::MEMORY))
		for (auto c : t->Childs) {
			pair<vector<Token*>, bool> tmp = Un_Wrap_Content(c);
			Result.insert(Result.end(), tmp.first.begin(), tmp.first.end());
			if (!tmp.second)
				Positive_Offsetter = false;
		}
	else if (t->is(TOKEN::OFFSETTER) || t->is(TOKEN::DEOFFSETTER) || t->is(TOKEN::SCALER)) {
		pair<vector<Token*>, bool> tmp = Un_Wrap_Content(t->Left);
		Result.insert(Result.end(), tmp.first.begin(), tmp.first.end());
		if (!tmp.second)
			Positive_Offsetter = false;

		tmp = Un_Wrap_Content(t->Right);
		Result.insert(Result.end(), tmp.first.begin(), tmp.first.end());
		if (!tmp.second)
			Positive_Offsetter = false;
	}
	else {
		Result.push_back(t);
	}

	if (t->is(TOKEN::DEOFFSETTER))
		Positive_Offsetter = false;

	return { Result, Positive_Offsetter };

}
