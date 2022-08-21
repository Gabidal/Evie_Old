#ifndef _FLAGS_H_
#define _FLAGS_H_

#undef OPTIONAL

enum class MODRM_ENCODING{
	NON,
	MOD_RM,
	MOD_REG
};

namespace TOKEN {
	static constexpr long long REGISTER						= 1 << 0;	//this is for that the selector can select an register if it sees this
	static constexpr long long VOLATILE						= 1 << 1;
	static constexpr long long NONVOLATILE					= 1 << 2;
	static constexpr long long RETURNING					= 1 << 3;
	static constexpr long long PARAMETER					= 1 << 4;	//fast call
	static constexpr long long REMAINDER					= 1 << 5;
	static constexpr long long QUOTIENT						= 1 << 6;
	static constexpr long long STACK_POINTTER				= 1 << 7;

	static constexpr long long NUM							= 1 << 8;
	static constexpr long long DECIMAL						= 1 << 9;

	static constexpr long long MEMORY						= 1 << 10;

	static constexpr long long OPERATOR						= 1 << 11;	//any operator
	static constexpr long long SCALER						= 1 << 12;		//*
	static constexpr long long OFFSETTER					= 1 << 13;	//+
	static constexpr long long DEOFFSETTER					= 1 << 14;	//+

	static constexpr long long CONTENT						= 1 << 15;	//any childs owner
	static constexpr long long LABEL						= 1 << 16;

	static constexpr long long FLOW							= 1 << 17; //ret, jmp
	static constexpr long long CALL							= 1 << 18; // calls

	//RULES
	static constexpr long long ALL_ARGS_SAME_SIZE			= 1 << 19;	//this means that all args on the OPCODE must be same size
	static constexpr long long OPTIONAL						= 1 << 20;
	static constexpr long long INF							= 1 << 21;
	static constexpr long long UN_ORDERED					= 1 << 22;
	static constexpr long long END_OF_FUNCTION				= 1 << 23;
	static constexpr long long START_OF_FUNCTION			= 1 << 24;
	static constexpr long long END_OF_LOOP					= 1 << 25;
	static constexpr long long NEEDS_SIZE_IDENTIFIER		= 1 << 26;
	static constexpr long long SIZE_INDENTIFIER				= 1 << 27;

	static constexpr long long GLOBAL_LABEL					= 1 << 28;
	static constexpr long long SET_DATA						= 1 << 29;
	static constexpr long long GLOBAL_VARIABLE				= 1 << 30;
	static constexpr long long STRING								 = (long long)1 << 31;
	static constexpr long long ADD_NON_VOLATILE_SPACE_NEEDS_HERE	 = (long long)1 << 32;
	static constexpr long long POSITION_INDEPENDENT_REGISTER		 = (long long)1 << 33;
	static constexpr long long STACK_ALLOCATION_CONSTANT			 = (long long)1 << 34;
	static constexpr long long UN_DECIDED							 = (long long)1 << 35;
	static constexpr long long PARAMETER_SPACE						 = (long long)1 << 36;
	static constexpr long long PUSH_SPACE							 = (long long)1 << 37;
	static constexpr long long LOCAL_VARIABLE_SCOPE					 = (long long)1 << 38;
	static constexpr long long REGISTER_SAVE_SPACE					 = (long long)1 << 39;
	static constexpr long long CALL_PARAMETER_SPACE					 = (long long)1 << 40;
	static constexpr long long ALREADY_GIVEN_REGISTER_NAME			 = (long long)1 << 41;
	static constexpr long long SECTION							 	 = (long long)1 << 42;

	//This is for the Assembler to identify end of opcode args, before Parser phase.
	static constexpr long long NEWLINE								 = (long long)1 << 43;
	static constexpr long long OPCODE								 = (long long)1 << 44;

	static constexpr long long UNIFORM_REGISTER						 = (long long)1 << 45;
	static constexpr long long EXTENDED_REGISTER					 = (long long)1 << 46;
}

namespace Flags{
	//the main flags that LEXER uses
	static constexpr long KEYWORD_COMPONENT						= 1 << 0;
	static constexpr long UNDEFINED_COMPONENT					= 1 << 1;
	static constexpr long PAREHTHESIS_COMPONENT					= 1 << 2;
	static constexpr long END_COMPONENT							= 1 << 3;
	static constexpr long STRING_COMPONENT						= 1 << 4;
	static constexpr long NUMBER_COMPONENT						= 1 << 5;
	static constexpr long COMMENT_COMPONENT						= 1 << 6;
	static constexpr long OPERATOR_COMPONENT					= 1 << 7;
	static constexpr long TEXT_COMPONENT						= 1 << 8;
	static constexpr long END_OF_DIRECTIVE_CHANGING_FILE		= 1 << 9;
	static constexpr long TEMPLATE_COMPONENT					= 1 << 10;
	static constexpr long NUMERICAL_TYPE_COMPONENT				= 1 << 11;
	static constexpr long PROCESSED_STRING						= 1 << 12;
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

	OPERATOR_NODE,				//classical operators like +-/*^
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
	NAMESPACE_INLINE_NODE,
	COUNT,

	COEFFICIENT_NODE,
};

#endif