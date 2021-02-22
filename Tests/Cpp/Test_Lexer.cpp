#include "../H/Test_Lexer.h"
#include "../../H/UI/Safe.h"

vector<Component> Lexer_Test::Run(string Case)
{
	return Lexer::GetComponents(Case);
}

void Lexer_Test::Factory()
{
	for (auto i : Tests) {
		Check_Assert(i.first, i.second);
	}
}

void Lexer_Test::Check_Assert(Lexer_Expectation_Set expectation, string s)
{
	bool fail = false;
	vector<Component> C = Run(s);
	if (expectation.has(NO_ORDER))
		for (auto i : C) {
			for (auto j : expectation.Expecations) {
				if (i.Components.size() > 0) {
					for (auto C_C : i.Components) {
						for (auto E_C : expectation.Childs) {
							if (Check_Assert(E_C, C_C, s))
								goto Child_Ok;
						}
						//no child was as expected
						fail = true;
						Report(FAIL, Lexer_Expectation_Set(expectation.Childs, expectation.F | expectation.Childs.begin()->F), "\"" + expectation.Get_Name(C_C) + "\" from '" + s + "'", i.Components);
					Child_Ok:;
					}
					goto Inside_Ok;
				}
				if (Check_Assert(expectation.F, i, j)) {
					goto Found;
				}
			}
			//the loop has ended but no expectation was found!
			fail = true;
			Report(FAIL, expectation, "\"" + expectation.Get_Name(i) + "\" from '" + s + "'", C);
		Found:;
		}
Inside_Ok:;
	if (!fail) {
		Report(SUCCESS, expectation, "\"" + s + "\"", C);
	}

}

bool Lexer_Test::Check_Assert(Lexer_Expectation_Set expectation, Component C, string s)
{
	bool fail = false;
	if (expectation.has(NO_ORDER)) {
		for (auto j : expectation.Expecations) {
			if (C.Components.size() > 0) {
				for (auto C_C : C.Components) {
					for (auto E_C : expectation.Childs) {
						if (Check_Assert(E_C, C_C, s))
							goto Child_Ok;
					}
					//no child was as expected
					fail = true;
					Report(FAIL, expectation, "\"" + expectation.Get_Name(C_C) + "\" from '" + s + "'", C.Components);
				Child_Ok:;
				}
				if (!fail)
					goto Inside_Ok;
			}
			if (Check_Assert(expectation.F, C, j)) {
				goto Found;
			}
		}
		//the loop has ended but no expectation was found!
		fail = true;
		return false; //Report(FAIL, expectation, "\"" + expectation.Get_Name(i) + "\" from '" + s + "'", C);

	Found:;
		if (!fail) {
		Inside_Ok:;
			return true; // Report(SUCCESS, expectation, "\"" + s + "\"", C);
		}
	}
}

bool Lexer_Test::Check_Assert(long F, Component a, Component b)
{
	if (is(F, NO_NAMES) && a.is(b.Flags))
		//this Flag means the only thing we are interested is the flag type that the component has
		return true;
	else if (a.is(b.Flags) && a.Value == b.Value)
		//name comparison & flag comparison
		return true;
	else
		return false;
}

void Lexer_Test::Init()
{
	Lexer::DecimalSeparator = '.';
	Lexer::ExponentSeparator = 'e';
	Lexer::SingleLineCommentIdentifier = '#';
	Lexer::StringIdentifier = '\"';
	Lexer::Keywords = {
		"type", "func", "loyal", "export", "import", "use", "if", "while", "else", "ptr", "ref", "cache", "jump", /*"size", size and deciaml and integer and format is no more a keyword because it can be also a variable name, only special in a class scoope*/ "return", "state", "const",
		"cpp", "evie", "vivid"
	};
	Tests = {
		
		{ {vector<long>{Flags::KEYWORD_COMPONENT, Flags::NUMBER_COMPONENT}}, "return 0"},
		{ {vector<long>{Flags::TEXT_COMPONENT, Flags::TEXT_COMPONENT}}, "int a"},
		{ {vector<pair<long, string>>{ {Flags::TEXT_COMPONENT, "a"}, {Flags::OPERATOR_COMPONENT, "+"}, {Flags::NUMBER_COMPONENT, "1"}}}, "a + 1"},
		{ {vector<long>{Flags::NUMBER_COMPONENT, Flags::OPERATOR_COMPONENT, Flags::TEXT_COMPONENT}}, "1.1 + a"},
		{ {vector<long>{Flags::OPERATOR_COMPONENT, Flags::TEXT_COMPONENT, Flags::OPERATOR_COMPONENT, Flags::OPERATOR_COMPONENT, Flags::OPERATOR_COMPONENT, Flags::TEXT_COMPONENT, Flags::OPERATOR_COMPONENT}}, "++a-- + --a++"},
		{ {{vector<Base*>{ new Text_Info({Flags::KEYWORD_COMPONENT, "while"}),new Lexer_Expectation_Set({Flags::TEXT_COMPONENT})}}}, "while (int)"},
		{ {{vector<Base*>{ new Text_Info({Flags::TEXT_COMPONENT, "call"}),new Lexer_Expectation_Set({Flags::TEXT_COMPONENT})}}}, "call(a)"},
		{ {{vector<Base*>{ new Text_Info({Flags::KEYWORD_COMPONENT, "import"}),new Text_Info({Flags::TEXT_COMPONENT, "function"}),new Lexer_Expectation_Set({Flags::TEXT_COMPONENT}),new Lexer_Expectation_Set({Flags::OPERATOR_COMPONENT}),new Lexer_Expectation_Set({Flags::NUMBER_COMPONENT})}}}, "import function(int, 0)"},

	};
}
