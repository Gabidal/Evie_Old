#ifndef _FLAGS_H_
#define _FLAGS_H_

namespace Flags{
	//the main flags that LEXER uses
	constexpr long KEYWORD_COMPONENT	 = 1 << 0;
	constexpr long UNDEFINED_COMPONENT	 = 1 << 1;
	constexpr long PAREHTHESIS_COMPONENT = 1 << 2;
	constexpr long END_COMPONENT		 = 1 << 3;
	constexpr long STRING_COMPONENT		 = 1 << 4;
	constexpr long NUMBER_COMPONENT		 = 1 << 5;
	constexpr long COMMENT_COMPONENT	 = 1 << 6;
	constexpr long OPERATOR_COMPONENT	 = 1 << 7;
	constexpr long TEXT_COMPONENT		 = 1 << 8;
}

enum Node_Type {
	CONTENT_NODE,
	ELSE_IF_NODE,
	ELSE_NODE,
	IF_NODE,
	WHILE_NODE,
	FUNCTION_NODE,
	CALL_NODE,
	FLOW_NODE,
	PTR_NODE,
	ARRAY_NODE,
	NUMBER_NODE,

	OPERATOR_NODE,		//idk really know
	CONDITION_OPERATOR_NODE,
	BIT_OPERATOR_NODE,

	STRING_NODE,
	CLASS_NODE,
	OBJECT_NODE,
	ANY,
	TEMPLATE_NODE,
	KEYWORD_NODE,
	PREFIX_NODE,
	POSTFIX_NODE,
	OBJECT_DEFINTION_NODE
};

#endif