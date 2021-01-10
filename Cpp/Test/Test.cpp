#include "../../H/Test/Test.h"
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

void Lexer_Test::Check_Assert(Lexer_Expectation expectation, string s)
{
	vector<Component> C = Run(s);
	if (expectation.has(NO_ORDER))
		for (auto i : C) {
			for (auto j : expectation.Expecations) {
				if (Check_Assert(expectation.Flags, i, j)) {
					Report(SUCCESS, expectation, s, C);
					goto Found;
				}
			}
			//the loop has ended but no expectation was found!
			Report(FAIL, expectation, s, C);
		Found:;
		}
}

bool Lexer_Test::Check_Assert(long F, Component a, Component b)
{
	return true;
}