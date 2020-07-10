#include "..\..\H\Parser\Parser.h"
#include "../../H/Parser/Parser.h"

void Parser::Definition_Pattern(int i)
{
	//this pattern just goes and looks for type/object/variable definition and tryes to put em into an list
	if (!Input[i].is(Flags::KEYWORD_COMPONENT))
		return;
}

void Parser::Factory() {

}