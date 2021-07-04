#ifndef _FLAGS_H_
#define _FLAGS_H_

#undef OPTIONAL

namespace TOKEN {
	constexpr long long REGISTER				 = 1 << 0;	//this is for that the selector can select an register if it sees this
	constexpr long long VOLATILE				 = 1 << 1;
	constexpr long long NONVOLATILE				 = 1 << 2;
	constexpr long long RETURNING				 = 1 << 3;
	constexpr long long PARAMETER				 = 1 << 4;	//fast call
	constexpr long long REMAINDER				 = 1 << 5;
	constexpr long long QUOTIENT				 = 1 << 6;
	constexpr long long STACK_POINTTER			 = 1 << 7;

	constexpr long long NUM						 = 1 << 8;
	constexpr long long DECIMAL					 = 1 << 9;

	constexpr long long MEMORY					 = 1 << 10;

	constexpr long long OPERATOR				 = 1 << 11;	//any operator
	constexpr long long SCALER					 = 1 << 12;		//*
	constexpr long long OFFSETTER				 = 1 << 13;	//+
	constexpr long long DEOFFSETTER				 = 1 << 14;	//+

	constexpr long long CONTENT					 = 1 << 15;	//any childs owner
	constexpr long long LABEL					 = 1 << 16;

	constexpr long long FLOW					 = 1 << 17; //ret, jmp
	constexpr long long CALL					 = 1 << 18; // calls

	//RULES
	constexpr long long ALL_ARGS_SAME_SIZE		 = 1 << 19;	//this means that all args on the OPCODE must be same size
	constexpr long long OPTIONAL				 = 1 << 20;
	constexpr long long INF						 = 1 << 21;
	constexpr long long UN_ORDERED				 = 1 << 22;
	constexpr long long END_OF_FUNCTION			 = 1 << 23;
	constexpr long long START_OF_FUNCTION		 = 1 << 24;
	constexpr long long END_OF_LOOP				 = 1 << 25;
	constexpr long long NEEDS_SIZE_IDENTIFIER	 = 1 << 26;
	constexpr long long SIZE_INDENTIFIER		 = 1 << 27;

	constexpr long long GLOBAL_LABEL			 = 1 << 28;
	constexpr long long SET_DATA				 = 1 << 29;
	constexpr long long GLOBAL_VARIABLE			 = 1 << 30;
	constexpr long long STRING								 = (long long)1 << 31;
	constexpr long long ADD_NON_VOLATILE_SPACE_NEEDS_HERE	 = (long long)1 << 32;
	constexpr long long POSITION_INDEPENDENT_REGISTER		 = (long long)1 << 33;
	constexpr long long STACK_ALLOCATION_CONSTANT			 = (long long)1 << 34;
}

namespace Flags{
	//the main flags that LEXER uses
	constexpr long KEYWORD_COMPONENT					= 1 << 0;
	constexpr long UNDEFINED_COMPONENT					= 1 << 1;
	constexpr long PAREHTHESIS_COMPONENT				= 1 << 2;
	constexpr long END_COMPONENT						= 1 << 3;
	constexpr long STRING_COMPONENT						= 1 << 4;
	constexpr long NUMBER_COMPONENT						= 1 << 5;
	constexpr long COMMENT_COMPONENT					= 1 << 6;
	constexpr long OPERATOR_COMPONENT					= 1 << 7;
	constexpr long TEXT_COMPONENT						= 1 << 8;
	constexpr long END_OF_DIRECTIVE_CHANGING_FILE		= 1 << 9;
	constexpr long TEMPLATE_COMPONENT					= 1 << 10;
	constexpr long NUMERICAL_TYPE_COMPONENT				= 1 << 11;
}

enum Node_Type {
	CONTENT_NODE,
	ELSE_IF_NODE,
	ELSE_NODE,
	IF_NODE,
	WHILE_NODE,
	FUNCTION_NODE,
	CALL_NODE,
	PROTOTYPE,
	IMPORT,
	EXPORT,
	FLOW_NODE,
	PTR_NODE,
	NUMBER_NODE,

	OPERATOR_NODE,				//classical operators like +-/*
	ASSIGN_OPERATOR_NODE,
	CONDITION_OPERATOR_NODE,	//==, !=, <, >
	BIT_OPERATOR_NODE,			// &, |, ¤, <<, >>
	LOGICAL_OPERATOR_NODE,
	ARRAY_NODE,					//a[1]
	NODE_CASTER,				//fruit x->banana.a

	STRING_NODE,
	CLASS_NODE,
	OBJECT_NODE,
	PARAMETER_NODE,
	ANY,
	TEMPLATE_NODE,
	KEYWORD_NODE,
	PREFIX_NODE,
	POSTFIX_NODE,
	OBJECT_DEFINTION_NODE,
	LABEL_NODE,
};

#endif