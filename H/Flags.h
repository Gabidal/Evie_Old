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
	//more complex flags
	constexpr long GIVING_ADDRESS_COMPONENT = 1 << 9;
	constexpr long ARRAY_OPERATOR_COMPONENT = 1 << 10;
	constexpr long FUNCTION_CALL_COMPONENT = 1 << 11;
	//the while loopper and the iffer are int the same, while loopper just has the jmp in the end
	//while ID is located in the NAME member in Node.h
	constexpr long CONDITION_COMPONENT = 1 << 12;
}

#endif