#include "../../H/UI/Service.h"

void Proxy::Factory() {
	for (int i = 0; i < Input.size(); i++) {
		Parse_Num(i);
		Parse_String(i);
		Parse_Position(i);
	}
}

int Proxy::Parse_Num(int i) {
	//"Label name": 123
	if (i + 2 >= Input.size())
		return;

	if (!Input[i + 2].is(Flags::NUMBER_COMPONENT))
		return;

	Type = (Document_Request_Type)atoi(Input[i + 2].Value.c_str());
}

string Proxy::Parse_String(int i) {
	//"Label name": "ABC"
	if (i + 2 >= Input.size())
		return;

	if (!Input[i + 2].is(Flags::STRING_COMPONENT))
		return;

	if (Word == "")
		Word = Input[i + 2].Value;
	else
		Uri = Input[i + 2].Value;
}

Position Proxy::Parse_Position(int i) {
	//"Label Name": {
	//	"Member1": Value,
	//	"Member2": Value2,
	//	"member3": Value3,
	//}
	if (i + 2 >= Input.size())
		return;

	if (!Input[i + 2].is(Flags::PAREHTHESIS_COMPONENT))
		return;

	//here we get from the paranthesis that resides in index i + 2
	//the components, every component is same as the ValueX above
	//"Member name": ValueX,
	Location = Position(
		atoi(Input[i + 2].Components[2].Value.c_str()),
		atoi(Input[i + 2].Components[6].Value.c_str()),
		atoi(Input[i + 2].Components[10].Value.c_str()),
		atoi(Input[i + 2].Components[14].Value.c_str())
	);
}