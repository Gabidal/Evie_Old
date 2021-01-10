#include "../../H/Lexer/Component.h"
#include "../../H/Lexer/Lexer.h"


string Component::Transform(long f)
{
	if (f == Flags::COMMENT_COMPONENT) {
		return "comment";
	}
	else if (f == Flags::END_COMPONENT) {
		return "end component";
	}
	else if (f == Flags::KEYWORD_COMPONENT) {
		return "keyword";
	}
	else if (f == Flags::NUMBER_COMPONENT) {
		return "number";
	}
	else if (f == Flags::OPERATOR_COMPONENT) {
		return "operator";
	}
	else if (f == Flags::PAREHTHESIS_COMPONENT) {
		return "parenthesis";
	}
	else if (f == Flags::STRING_COMPONENT) {
		return "string";
	}
	else if (f == Flags::TEXT_COMPONENT) {
		return "text";
	}
	else if (f == Flags::UNDEFINED_COMPONENT) {
		return "undefined";
	}
	else {
		throw::exception("INTERNAL ERROR!");
	}
}