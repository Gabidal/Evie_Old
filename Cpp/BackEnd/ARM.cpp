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


	Token* W0B = new Token(TOKEN::VOLATILE | TOKEN::RETURNING, "w0", 1, {});
	Token* W0W = new Token(TOKEN::VOLATILE | TOKEN::RETURNING, "w0", 2, {W0B});
	Token* W0D = new Token(TOKEN::VOLATILE | TOKEN::RETURNING, "w0", 4, {W0W});
	Token* X0 = new Token(TOKEN::VOLATILE | TOKEN::RETURNING, "x0", 8, { W0D });

	Token* W1B = new Token(TOKEN::VOLATILE, "w1", 1, {});
	Token* W1W = new Token(TOKEN::VOLATILE, "w1", 2, { W1B });
	Token* W1D = new Token(TOKEN::VOLATILE, "w1", 4, { W1W });
	Token* X1 = new Token(TOKEN::VOLATILE, "x1", 8, { W1D });

	Token* W2B = new Token(TOKEN::VOLATILE, "w2", 1, {});
	Token* W2W = new Token(TOKEN::VOLATILE, "w2", 2, { W2B });
	Token* W2D = new Token(TOKEN::VOLATILE, "w2", 4, { W2W });
	Token* X2 = new Token(TOKEN::VOLATILE, "x2", 8, { W2D });

	Token* W3B = new Token(TOKEN::VOLATILE, "w3", 1, {});
	Token* W3W = new Token(TOKEN::VOLATILE, "w3", 2, { W3B });
	Token* W3D = new Token(TOKEN::VOLATILE, "w3", 4, { W3W });
	Token* X3 = new Token(TOKEN::VOLATILE, "x3", 8, { W3D });

	Token* W4B = new Token(TOKEN::VOLATILE, "w4", 1, {});
	Token* W4W = new Token(TOKEN::VOLATILE, "w4", 2, { W4B });
	Token* W4D = new Token(TOKEN::VOLATILE, "w4", 4, { W4W });
	Token* X4 = new Token(TOKEN::VOLATILE, "x4", 8, { W4D });

	Token* W5B = new Token(TOKEN::VOLATILE, "w5", 1, {});
	Token* W5W = new Token(TOKEN::VOLATILE, "w5", 2, { W5B });
	Token* W5D = new Token(TOKEN::VOLATILE, "w5", 4, { W5W });
	Token* X5 = new Token(TOKEN::VOLATILE, "x5", 8, { W5D });

	Token* W6B = new Token(TOKEN::VOLATILE, "w6", 1, {});
	Token* W6W = new Token(TOKEN::VOLATILE, "w6", 2, { W6B });
	Token* W6D = new Token(TOKEN::VOLATILE, "w6", 4, { W6W });
	Token* X6 = new Token(TOKEN::VOLATILE, "x6", 8, { W6D });

	Token* W7B = new Token(TOKEN::VOLATILE, "w7", 1, {});
	Token* W7W = new Token(TOKEN::VOLATILE, "w7", 2, { W7B });
	Token* W7D = new Token(TOKEN::VOLATILE, "w7", 4, { W7W });
	Token* X7 = new Token(TOKEN::VOLATILE, "x7", 8, { W7D });

	Token* W8B = new Token(TOKEN::VOLATILE, "w8", 1, {});
	Token* W8W = new Token(TOKEN::VOLATILE, "w8", 2, { W8B });
	Token* W8D = new Token(TOKEN::VOLATILE, "w8", 4, { W8W });
	Token* X8 = new Token(TOKEN::VOLATILE, "x8", 8, { W8D });

	Token* W9B = new Token(TOKEN::VOLATILE, "w9", 1, {});
	Token* W9W = new Token(TOKEN::VOLATILE, "w9", 2, { W9B });
	Token* W9D = new Token(TOKEN::VOLATILE, "w9", 4, { W9W });
	Token* X9 = new Token(TOKEN::VOLATILE, "x9", 8, { W9D });

	Token* W10B = new Token(TOKEN::VOLATILE, "w10", 1, {});
	Token* W10W = new Token(TOKEN::VOLATILE, "w10", 2, { W10B });
	Token* W10D = new Token(TOKEN::VOLATILE, "w10", 4, { W10W });
	Token* X10 = new Token(TOKEN::VOLATILE, "x10", 8, { W10D });

	Token* W11B = new Token(TOKEN::VOLATILE, "w11", 1, {});
	Token* W11W = new Token(TOKEN::VOLATILE, "w11", 2, { W11B });
	Token* W11D = new Token(TOKEN::VOLATILE, "w11", 4, { W11W });
	Token* X11 = new Token(TOKEN::VOLATILE, "x11", 8, { W11D });

	Token* W12B = new Token(TOKEN::VOLATILE, "w12", 1, {});
	Token* W12W = new Token(TOKEN::VOLATILE, "w12", 2, { W12B });
	Token* W12D = new Token(TOKEN::VOLATILE, "w12", 4, { W12W });
	Token* X12 = new Token(TOKEN::VOLATILE, "x12", 8, { W12D });

	Token* W13B = new Token(TOKEN::VOLATILE, "w13", 1, {});
	Token* W13W = new Token(TOKEN::VOLATILE, "w13", 2, { W13B });
	Token* W13D = new Token(TOKEN::VOLATILE, "w13", 4, { W13W });
	Token* X13 = new Token(TOKEN::VOLATILE, "x13", 8, { W13D });

	Token* W14B = new Token(TOKEN::VOLATILE, "w14", 1, {});
	Token* W14W = new Token(TOKEN::VOLATILE, "w14", 2, { W14B });
	Token* W14D = new Token(TOKEN::VOLATILE, "w14", 4, { W14W });
	Token* X14 = new Token(TOKEN::VOLATILE,  "x14", 8, { W14D });

	Token* W15B = new Token(TOKEN::VOLATILE, "w15", 1, {});
	Token* W15W = new Token(TOKEN::VOLATILE, "w15", 2, { W15B });
	Token* W15D = new Token(TOKEN::VOLATILE, "w15", 4, { W15W });
	Token* X15 = new Token(TOKEN::VOLATILE,  "x15", 8, { W15D });

	Token* W16B = new Token(TOKEN::VOLATILE, "w16", 1, {});
	Token* W16W = new Token(TOKEN::VOLATILE, "w16", 2, { W16B });
	Token* W16D = new Token(TOKEN::VOLATILE, "w16", 4, { W16W });
	Token* X16 = new Token(TOKEN::VOLATILE, "x16", 8, { W16D });

	Token* W17B = new Token(TOKEN::VOLATILE, "w17", 1, {});
	Token* W17W = new Token(TOKEN::VOLATILE, "w17", 2, { W17B });
	Token* W17D = new Token(TOKEN::VOLATILE, "w17", 4, { W17W });
	Token* X17 = new Token(TOKEN::VOLATILE, "x17", 8, { W17D });

	Token* W18B = new Token(TOKEN::VOLATILE, "w18", 1, {});
	Token* W18W = new Token(TOKEN::VOLATILE, "w18", 2, { W18B });
	Token* W18D = new Token(TOKEN::VOLATILE, "w18", 4, { W18W });
	Token* X18 = new Token(TOKEN::VOLATILE, "x18", 8, { W18D });

	Token* W19B = new Token(TOKEN::NONVOLATILE, "w19", 1, {});
	Token* W19W = new Token(TOKEN::NONVOLATILE, "w19", 2, { W19B });
	Token* W19D = new Token(TOKEN::NONVOLATILE, "w19", 4, { W19W });
	Token* X19 = new Token(TOKEN::NONVOLATILE, "x19", 8, { W19D });

	Token* W20B = new Token(TOKEN::NONVOLATILE, "w20", 1, {});
	Token* W20W = new Token(TOKEN::NONVOLATILE, "w20", 2, { W20B });
	Token* W20D = new Token(TOKEN::NONVOLATILE, "w20", 4, { W20W });
	Token* X20 = new Token(TOKEN::NONVOLATILE, "x20", 8, { W20D });

	Token* W21B = new Token(TOKEN::NONVOLATILE, "w21", 1, {});
	Token* W21W = new Token(TOKEN::NONVOLATILE, "w21", 2, { W21B });
	Token* W21D = new Token(TOKEN::NONVOLATILE, "w21", 4, { W21W });
	Token* X21 = new Token(TOKEN::NONVOLATILE, "x21", 8, { W21D });

	Token* W22B = new Token(TOKEN::NONVOLATILE, "w22", 1, {});
	Token* W22W = new Token(TOKEN::NONVOLATILE, "w22", 2, { W22B });
	Token* W22D = new Token(TOKEN::NONVOLATILE, "w22", 4, { W22W });
	Token* X22 = new Token(TOKEN::NONVOLATILE, "x22", 8, { W22D });

	Token* W23B = new Token(TOKEN::NONVOLATILE, "w23", 1, {});
	Token* W23W = new Token(TOKEN::NONVOLATILE, "w23", 2, { W23B });
	Token* W23D = new Token(TOKEN::NONVOLATILE, "w23", 4, { W23W });
	Token* X23 = new Token(TOKEN::NONVOLATILE, "x23", 8, { W23D });

	Token* W24B = new Token(TOKEN::NONVOLATILE, "w24", 1, {});
	Token* W24W = new Token(TOKEN::NONVOLATILE, "w24", 2, { W24B });
	Token* W24D = new Token(TOKEN::NONVOLATILE, "w24", 4, { W24W });
	Token* X24 = new Token(TOKEN::NONVOLATILE, "x24", 8, { W24D });

	Token* W25B = new Token(TOKEN::NONVOLATILE, "w25", 1, {});
	Token* W25W = new Token(TOKEN::NONVOLATILE, "w25", 2, { W25B });
	Token* W25D = new Token(TOKEN::NONVOLATILE, "w25", 4, { W25W });
	Token* X25 = new Token(TOKEN::NONVOLATILE, "x25", 8, { W25D });

	Token* W26B = new Token(TOKEN::NONVOLATILE, "w26", 1, {});
	Token* W26W = new Token(TOKEN::NONVOLATILE, "w26", 2, { W26B });
	Token* W26D = new Token(TOKEN::NONVOLATILE, "w26", 4, { W26W });
	Token* X26 = new Token(TOKEN::NONVOLATILE, "x26", 8, { W26D });

	Token* W27B = new Token(TOKEN::NONVOLATILE, "w27", 1, {});
	Token* W27W = new Token(TOKEN::NONVOLATILE, "w27", 2, { W27B });
	Token* W27D = new Token(TOKEN::NONVOLATILE, "w27", 4, { W27W });
	Token* X27 = new Token(TOKEN::NONVOLATILE, "x27", 8, { W27D });

	Token* W28B = new Token(TOKEN::NONVOLATILE, "w28", 1, {});
	Token* W28W = new Token(TOKEN::NONVOLATILE, "w28", 2, { W28B });
	Token* W28D = new Token(TOKEN::NONVOLATILE, "w28", 4, { W28W });
	Token* X28 = new Token(TOKEN::NONVOLATILE, "x28", 8, { W28D });

	Token* W29B = new Token(TOKEN::NONVOLATILE, "w29", 1, {});
	Token* W29W = new Token(TOKEN::NONVOLATILE, "w29", 2, { W29B });
	Token* W29D = new Token(TOKEN::NONVOLATILE, "w29", 4, { W29W });
	Token* X29 = new Token(TOKEN::NONVOLATILE, "x29", 8, { W29D });




	//FPU REGISTERS:	
	/*
		B0
		H0
		S0
		D0
		Q0
	*/
	Token* B0 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER | TOKEN::RETURNING, "b0", 1, {});
	Token* H0 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER | TOKEN::RETURNING, "h0", 2, { B0 });
	Token* S0 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER | TOKEN::RETURNING, "s0", 4, { H0 });
	Token* D0 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER | TOKEN::RETURNING, "d0", 8, { S0 });
	Token* Q0 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER | TOKEN::RETURNING, "q0", 12, { D0 });
														   
	Token* B1 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "b1", 1, {});
	Token* H1 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "h1", 2, { B1 });
	Token* S1 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "s1", 4, { H1 });
	Token* D1 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "d1", 8, { S1 });
	Token* Q1 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "q1", 12, { D1 });
														   
	Token* B2 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "b2", 1, {});
	Token* H2 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "h2", 2, { B2 });
	Token* S2 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "s2", 4, { H2 });
	Token* D2 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "d2", 8, { S2 });
	Token* Q2 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "q2", 12, { D2 });
														   
	Token* B3 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "b3", 1, {});
	Token* H3 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "h3", 2, { B3 });
	Token* S3 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "s3", 4, { H3 });
	Token* D3 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "d3", 8, { S3 });
	Token* Q3 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "q3", 12, { D3 });
												   		   
	Token* B4 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "b4", 1, {});
	Token* H4 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "h4", 2, { B4 });
	Token* S4 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "s4", 4, { H4 });
	Token* D4 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "d4", 8, { S4 });
	Token* Q4 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "q4", 12, { D4 });
												   		   
	Token* B5 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "b5", 1, {});
	Token* H5 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "h5", 2, { B5 });
	Token* S5 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "s5", 4, { H5 });
	Token* D5 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "d5", 8, { S5 });
	Token* Q5 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "q5", 12, { D5 });
												   		   
	Token* B6 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "b6", 1, {});
	Token* H6 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "h6", 2, { B6 });
	Token* S6 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "s6", 4, { H6 });
	Token* D6 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "d6", 8, { S6 });
	Token* Q6 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "q6", 12, { D6 });
												   		   
	Token* B7 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "b7", 1, {});
	Token* H7 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "h7", 2, { B7 });
	Token* S7 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "s7", 4, { H7 });
	Token* D7 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "d7", 8, { S7 });
	Token* Q7 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL | TOKEN::PARAMETER, "q7", 12, { D7 });
												   		  
	Token* B8 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b8", 1, {});
	Token* H8 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h8", 2, { B8 });
	Token* S8 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s8", 4, { H8 });
	Token* D8 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d8", 8, { S8 });
	Token* Q8 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q8", 12, { D8 });
												   		  
	Token* B9 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b9", 1, {});
	Token* H9 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h9", 2, { B9 });
	Token* S9 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s9", 4, { H9 });
	Token* D9 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d9", 8, { S9 });
	Token* Q9 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q9", 12, { D9 });
												   
	Token* B10 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b10", 1, {});
	Token* H10 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h10", 2, { B10 });
	Token* S10 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s10", 4, { H10 });
	Token* D10 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d10", 8, { S10 });
	Token* Q10 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q10", 12, { D10 });
												   
	Token* B11 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b11", 1, {});
	Token* H11 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h11", 2, { B11 });
	Token* S11 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s11", 4, { H11 });
	Token* D11 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d11", 8, { S11 });
	Token* Q11 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q11", 12, { D11 });
												   
	Token* B12 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b12", 1, {});
	Token* H12 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h12", 2, { B12 });
	Token* S12 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s12", 4, { H12 });
	Token* D12 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d12", 8, { S12 });
	Token* Q12 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q12", 12, { D12 });
												   
	Token* B13 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b13", 1, {});
	Token* H13 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h13", 2, { B13 });
	Token* S13 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s13", 4, { H13 });
	Token* D13 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d13", 8, { S13 });
	Token* Q13 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q13", 12, { D13 });
												   
	Token* B14 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b14", 1, {});
	Token* H14 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h14", 2, { B14 });
	Token* S14 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s14", 4, { H14 });
	Token* D14 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d14", 8, { S14 });
	Token* Q14 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q14", 12, { D14 });
												   
	Token* B15 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b15", 1, {});
	Token* H15 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h15", 2, { B15 });
	Token* S15 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s15", 4, { H15 });
	Token* D15 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d15", 8, { S15 });
	Token* Q15 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q15", 12, { D15 });
												   
	Token* B16 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b16", 1, {});
	Token* H16 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h16", 2, { B16 });
	Token* S16 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s16", 4, { H16 });
	Token* D16 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d16", 8, { S16 });
	Token* Q16 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q16", 12, { D16 });
												   
	Token* B17 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b17", 1, {});
	Token* H17 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h17", 2, { B17 });
	Token* S17 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s17", 4, { H17 });
	Token* D17 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d17", 8, { S17 });
	Token* Q17 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q17", 12, { D17 });
												   
	Token* B18 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "b18", 1, {});
	Token* H18 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "h18", 2, { B18 });
	Token* S18 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "s18", 4, { H18 });
	Token* D18 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "d18", 8, { S18 });
	Token* Q18 = new Token(TOKEN::VOLATILE | TOKEN::DECIMAL, "q18", 12, { D18 });
												   
	Token* B19 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b19", 1, {});
	Token* H19 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h19", 2, { B19 });
	Token* S19 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s19", 4, { H19 });
	Token* D19 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d19", 8, { S19 });
	Token* Q19 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q19", 12, { D19 });
												   
	Token* B20 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b20", 1, {});
	Token* H20 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h20", 2, { B20 });
	Token* S20 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s20", 4, { H20 });
	Token* D20 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d20", 8, { S20 });
	Token* Q20 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q20", 12, { D20 });
												   
	Token* B21 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b21", 1, {});
	Token* H21 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h21", 2, { B21 });
	Token* S21 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s21", 4, { H21 });
	Token* D21 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d21", 8, { S21 });
	Token* Q21 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q21", 12, { D21 });
												   
	Token* B22 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b22", 1, {});
	Token* H22 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h22", 2, { B22 });
	Token* S22 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s22", 4, { H22 });
	Token* D22 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d22", 8, { S22 });
	Token* Q22 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q22", 12, { D22 });
												   
	Token* B23 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b23", 1, {});
	Token* H23 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h23", 2, { B23 });
	Token* S23 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s23", 4, { H23 });
	Token* D23 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d23", 8, { S23 });
	Token* Q23 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q23", 12, { D23 });
												   
	Token* B24 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b24", 1, {});
	Token* H24 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h24", 2, { B24 });
	Token* S24 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s24", 4, { H24 });
	Token* D24 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d24", 8, { S24 });
	Token* Q24 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q24", 12, { D24 });
												   
	Token* B25 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b25", 1, {});
	Token* H25 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h25", 2, { B25 });
	Token* S25 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s25", 4, { H25 });
	Token* D25 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d25", 8, { S25 });
	Token* Q25 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q25", 12, { D25 });
												   
	Token* B26 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b26", 1, {});
	Token* H26 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h26", 2, { B26 });
	Token* S26 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s26", 4, { H26 });
	Token* D26 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d26", 8, { S26 });
	Token* Q26 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q26", 12, { D26 });
												   
	Token* B27 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b27", 1, {});
	Token* H27 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h27", 2, { B27 });
	Token* S27 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s27", 4, { H27 });
	Token* D27 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d27", 8, { S27 });
	Token* Q27 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q27", 12, { D27 });
												   
	Token* B28 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b28", 1, {});
	Token* H28 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h28", 2, { B28 });
	Token* S28 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s28", 4, { H28 });
	Token* D28 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d28", 8, { S28 });
	Token* Q28 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q28", 12, { D28 });
												   
	Token* B29 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "b29", 1, {});
	Token* H29 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "h29", 2, { B29 });
	Token* S29 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "s29", 4, { H29 });
	Token* D29 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "d29", 8, { S29 });
	Token* Q29 = new Token(TOKEN::DECIMAL | TOKEN::NONVOLATILE, "q29", 12, { D29 });



	Token* SP = new Token(TOKEN::STACK_POINTTER, "sp", 8, {});

	Parameter_Registers = { X0, X1, X2, X3, X4, X5, X6, X7 , Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7};
	Registers = {
		W0B, W0W, W0D, X0,
		W1B, W1W, W1D, X1,
		W2B, W2W, W2D, X2,
		W3B, W3W, W3D, X3,
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

		B0, H0, S0, D0, Q0,
		B1, H1, S1, D1, Q1,
		B2, H2, S2, D2, Q2,
		B3, H3, S3, D3, Q3,
		B4, H4, S4, D4, Q4,
		B5, H5, S5, D5, Q5,
		B6, H6, S6, D6, Q6,
		B7, H7, S7, D7, Q7,
		B8, H8, S8, D8, Q8,
		B9, H9, S9, D9, Q9,
		B10, H10, S10, D10, Q10,
		B11, H11, S11, D11, Q11,
		B12, H12, S12, D12, Q12,
		B13, H13, S13, D13, Q13,
		B14, H14, S14, D14, Q14,
		B15, H15, S15, D15, Q15,
		B16, H16, S16, D16, Q16,
		B17, H17, S17, D17, Q17,
		B18, H18, S18, D18, Q18,
		B19, H19, S19, D19, Q19,
		B20, H20, S20, D20, Q20,
		B21, H21, S21, D21, Q21,
		B22, H22, S22, D22, Q22,
		B23, H23, S23, D23, Q23,
		B24, H24, S24, D24, Q24,
		B25, H25, S25, D25, Q25,
		B26, H26, S26, D26, Q26,
		B27, H27, S27, D27, Q27,
		B28, H28, S28, D28, Q28,
		B29, H29, S29, D29, Q29,

		SP,
	};

	IR* MOV_ALL = new IR("=", new Token(OPERATOR), {
		//accepted arguments
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },

		{{Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Decimal, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Decimal, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];
			string Move = "mov";	//some genious decided that every move operator must have its own opcode naming :/

			long long Fpu = 0;
			if (Left->is(TOKEN::DECIMAL) || Right->is(TOKEN::DECIMAL)) {
				Move = "fmov";
				Fpu = TOKEN::DECIMAL;
			}

			if (Right->is(NUM)) {
				if (Left->is(REGISTER)) {
					long long Num = atoll(Right->Get_Name().c_str());
					if (Right->is(DECIMAL)) {
						if (Right->Get_Size() == 8) {
							double tmp = atof(Right->Get_Name().c_str());
							Num = *(long long*)&tmp;
						}
						else {
							float tmp = atof(Right->Get_Name().c_str());
							Num = *(long*)&tmp;
						}
					}
					if (Num > UINT16_MAX) {
						/*
						mov w0, 0001 0000 0000 0000
						mov w1, 0000 0000 0000 0001 
						lsl w1, w1, 16
						orr w0, w0, w1
						*/
						long long Chunk1 = Num & 0xffff;
						Token* Reg1 = new Token(REGISTER | Fpu, "REG_" + to_string(Reg_Random_ID_Addon++), 4);
						Result.push_back(new IR(new Token(OPERATOR, Move), { Reg1, new Token(NUM | Fpu, to_string(Chunk1), Reg1->Get_Size()) }, nullptr));
					
						long long Chunk2 = (Num >> 16 ) & 0xffff;
						Token* Reg2 = new Token(REGISTER | Fpu, "REG_" + to_string(Reg_Random_ID_Addon++), 4);
						Result.push_back(new IR(new Token(OPERATOR, Move), { Reg1, new Token(NUM | Fpu, to_string(Chunk2), Reg1->Get_Size()) }, nullptr));

						Result.push_back(new IR(new Token(OPERATOR, "lsl"), { Reg2, Reg2, new Token(NUM, to_string(16), Reg2->Get_Size()) }, nullptr));
						Result.push_back(new IR(new Token(OPERATOR, "orr"), { Reg1, Reg1, Reg2 }, nullptr));

						Right = Reg1;
					}
				}
				else {
					//of memory
					Token* Reg1 = new Token(REGISTER | Fpu, "REG_" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
					Result.push_back(new IR(new Token(OPERATOR, "="), { Reg1, Right }, nullptr));

					Result.push_back(new IR(new Token(OPERATOR, "="), { Left, Reg1 }, nullptr));
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
			
			Result.push_back(new IR(new Token(OPERATOR, Move), { Left, Right }, nullptr));

			return Result;
		}
	);

	IR* MOVE = new IR(*MOV_ALL);
	MOVE->ID = "move";

	IR* MOV = new IR("mov", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mov"), {
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
	});

	IR* FMOV = new IR("fmov", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "fmov"), {
		{{Register_Float, {1, 8}}, {Decimal, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
	});


	IR* LDR = new IR("ldr", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "ldr"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },

		{{Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		});

	IR* STR = new IR("str", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "str"), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },

		{{Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		});

	IR* LSL = new IR("lsl", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "lsl"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, { Const, {1, 8}} },
	});

	IR* LSR = new IR("lsr", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "lsr"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, { Const, {1, 8}} },
	});

	IR* FLSL = new IR("lsl", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "lsl"), {
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, { Const, {1, 8}} },
	});

	IR* FLSR = new IR("lsr", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "lsr"), {
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, { Const, {1, 8}} },
	});

	IR* SHIFT_LEFT = new IR("<<", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
	},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Result.push_back(new IR(new Token(OPERATOR, "lsl"), { args[0], args[0], args[1] }, nullptr));
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
			Result.push_back(new IR(new Token(OPERATOR, "lsr"), { args[0], args[0], args[1] }, nullptr));
			return Result;
		}
	);

	IR* ORR = new IR("orr", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "orr"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, { Const, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}}, { Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}}, { Const, {1, 8}} },
	});

	IR* FORR = new IR("orr", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "orr"), {
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, { Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, { Decimal, {1, 8}} },
		{{Register_Float, {1, 8}}, {Decimal, {1, 8}}, { Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Decimal, {1, 8}}, { Decimal, {1, 8}} },
	});

	IR* OR = new IR("|", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },
	},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Result.push_back(new IR(new Token(OPERATOR, "orr"), { args[0], args[0], args[1] }, nullptr));
			return Result;
		}
	);

	IR* ADD_LAMBDA = new IR("+", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },

		{{Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Decimal, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Decimal, {1, 8}} },
	},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];

			long long Fpu = 0;
			if (Left->is(TOKEN::DECIMAL) || Right->is(TOKEN::DECIMAL))
				Fpu = TOKEN::DECIMAL;

			if (Right->is(NUM) && atoll(Right->Get_Name().c_str()) > 4095) {	//max 12bit number
				Token* Reg1 = new Token(REGISTER | Fpu, "REG_" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { Reg1, Right }, nullptr));

				Right = Reg1;
			}

			Result.push_back(new IR(new Token(OPERATOR, "add"), { Left, Left, Right }, nullptr));

			return Result;
		}
	);

	IR* SUB_LAMBDA = new IR("-", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },

		{{Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Decimal, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Decimal, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];

			long long Fpu = 0;
			if (Left->is(TOKEN::DECIMAL) || Right->is(TOKEN::DECIMAL))
				Fpu = TOKEN::DECIMAL;

			if (Right->is(NUM) && atoll(Right->Get_Name().c_str()) > 4095) {	//max 12bit number
				Token* Reg1 = new Token(REGISTER | Fpu, "REG_" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { Reg1, Right }, nullptr));

				Right = Reg1;
			}

			Result.push_back(new IR(new Token(OPERATOR, "sub"), { Left, Left, Right }, nullptr));

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

	IR* FADD = new IR("add", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "fadd"), {
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Memory_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, {Decimal, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Memory_Float, {1, 8}}, {Decimal, {1, 8}} },
	});

	IR* FSUB = new IR("sub", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "fsub"), {
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Memory_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, {Decimal, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Memory_Float, {1, 8}}, {Decimal, {1, 8}} },
	});


	IR* MUL_LAMBDA = new IR("*", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },

		{{Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Decimal, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Decimal, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];

			long long Fpu = 0;
			if (Left->is(TOKEN::DECIMAL) || Right->is(TOKEN::DECIMAL))
				Fpu = TOKEN::DECIMAL;

			if (Right->is(NUM)) {
				Token* Reg1 = new Token(REGISTER | Fpu, "REG_" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { Reg1, Right }, nullptr));

				Right = Reg1;
			}

			Result.push_back(new IR(new Token(OPERATOR, "mul"), { Left, Left, Right }, nullptr));

			return Result;
		}
	);

	IR* MUL = new IR("mul", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "mul"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}}, {Register, {1, 8}} },
	});

	IR* FMUL = new IR("mul", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "fmul"), {
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Memory_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
	});

	IR* DIV_LAMBDA = new IR("/", new Token(OPERATOR | ALL_ARGS_SAME_SIZE), {
		{{Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Const, {1, 8}} },
		{{Memory, {1, 8}}, {Const, {1, 8}} },

		{{Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Decimal, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Decimal, {1, 8}} },
		},
		[](vector<Token*> args) {
			vector<IR*> Result;
			Token* Left = args[0];
			Token* Right = args[1];

			long long Fpu = 0;
			if (Left->is(TOKEN::DECIMAL) || Right->is(TOKEN::DECIMAL))
				Fpu = TOKEN::DECIMAL;

			if (Right->is(NUM)) {
				Token* Reg1 = new Token(REGISTER | Fpu, "REG_" + to_string(Reg_Random_ID_Addon++), Right->Get_Size());
				Result.push_back(new IR(new Token(OPERATOR, "="), { Reg1, Right }, nullptr));

				Right = Reg1;
			}

			Result.push_back(new IR(new Token(OPERATOR, "div"), { Left, Left, Right }, nullptr));

			return Result;
		}
	);

	IR* DIV = new IR("div", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "sdiv"), {
		{{Register, {1, 8}}, {Register, {1, 8}}, {Memory, {1, 8}} },
		{{Memory, {1, 8}}, {Memory, {1, 8}}, {Register, {1, 8}} },
		{{Register, {1, 8}}, {Register, {1, 8}}, {Register, {1, 8}} },
	});

	IR* FDIV = new IR("div", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "fdiv"), {
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Memory_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
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

			Result.push_back(new IR(new Token(OPERATOR, Eval_Type), tmp.first, nullptr));

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
			}, nullptr));

			Result.push_back(new IR(new Token(OPERATOR, "ldr"), {
				args[0], new Token(MEMORY, "MEM_" + args[1]->Get_Name(), _SYSTEM_BIT_SIZE_, {new Token(OFFSETTER, ",", args[0], new Token(LABEL, ":got_lo12:" + args[1]->Get_Name(), 0))})
			}, nullptr));

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
		{{Register,  {1, 8}}, {Const, {1, 8}}},

		{{Register_Float, {1, 8}}, {Memory_Float, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Register_Float, {1, 8}} },
		{{Register_Float, {1, 8}}, {Decimal, {1, 8}} },
		{{Memory_Float, {1, 8}}, {Decimal, {1, 8}} },
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

	//FCVTZS float to int
	//SCVTF int to float
	//fcvt float to double and double to float

	IR* FCSTZS = new IR("convert", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "fcvtzs"), {
		{{Register, {4, 4}}, {Register_Float, {4, 4}} },
	});

	IR* SCSTF = new IR("convert", new Token(OPERATOR | ALL_ARGS_SAME_SIZE, "scvtf"), {
		{{Register_Float, {4, 4}}, {Register, {4, 4}} },
	});

	IR* FCVT = new IR("convert", new Token(OPERATOR, "fcvt"), {
		{{Register_Float, {4, 8}}, {Register_Float, {4, 8}} },
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
			}, nullptr));

			//sub sp, sp, args[0].size
			Result.push_back(new IR(new Token(OPERATOR, "sub"), {
				Stack, Stack, new Token(NUM, to_string(args[0]->Get_Size()), _SYSTEM_BIT_SIZE_)
			}, nullptr));

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
				}, nullptr));

			//add sp, sp, args[0].size
			Result.push_back(new IR(new Token(OPERATOR, "add"), {
				Stack, Stack, new Token(NUM, to_string(args[0]->Get_Size()), _SYSTEM_BIT_SIZE_)
				}, nullptr));

			return Result;
		}
	);

	Opcodes = {
		MOV_ALL, MOVE, MOV, LDR, STR,
		LSL, LSR, SHIFT_LEFT, SHIFT_RIGHT,
		ORR, OR, FORR,
		ADD_LAMBDA, ADD, LEA_MEM, LEA_LABEL, ADRP,
		SUB_LAMBDA, SUB,
		MUL, MUL_LAMBDA, DIV, DIV_LAMBDA,
		BL, B, BEQ, BNE, BLE, BLT, BNL, BGE, BGT, BNG,
		RET, PUSH, POP,
		GLOBAL, EXTERN,
		FADD, FSUB, FMUL, FDIV, FLSL, FLSR, FMOV,
		FCSTZS, SCSTF, FCVT,
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
