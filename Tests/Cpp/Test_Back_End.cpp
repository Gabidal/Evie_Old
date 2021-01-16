#include "..\H\Test_Back_End.h"
#include "../../H/UI/Usr.h"
#include "../../H/Nodes/Node.h"
#include "../../H/BackEnd/Selector.h"
#include "../../H/UI/Safe.h"


#ifdef _WIN32
#include <Windows.h>
template<typename R, typename... T>
R Call(void* handle, const char* name, T... arguments) {
	auto f = (R(*)(T...))GetProcAddress(name);

	return f(arguments...);
}
//int a = Call<int>(Handle, "Start_Test", 1, 2, 1.1);
int Back_End_Test::Run_Dll(string f) {
	auto Handle = LoadLibrary(f.c_str());
	if (Handle == nullptr)
		throw::exception("INTERNAL ERROR!");

	auto Func = (int(*)())GetProcAddress(Handle, "Start_Test");
	if (Func == nullptr)
		throw::exception("INTERNAL ERROR!");
	return Func();
}

#else 
#include <dlfcn.h>
int Back_End_Test::Run_Dll(string f) {

}
#endif



extern Usr* sys;
extern Node* Global_Scope;
extern Selector* selector;
extern x86_64_Win X86_64_WIN;
extern int _SYSTEM_BIT_SIZE_;

extern string Output;
extern int arg_count;

extern int Build(int argc, const char* argv[]);

vector<Base*> Back_End_Test::Run(string File)
{
	arg_count = 0;
	const char* argv[] = {"-in" , File.c_str() , "-out" , File.c_str() , ".dll" , " -f" , "dll"};
	int argc = 6;
	Build(argc, argv);
	return { &Numeric_Info{Run_Dll(File + ".dll")} };
}

void Back_End_Test::Factory()
{
	for (auto i : Tests) {
		Check_Assert(i.first, i.second);
	}
}

void Back_End_Test::Check_Assert(Back_Expectation_Set expectation, string s)
{
	bool fail = false;
	vector<Base*> C = Run(s);
	if (expectation.has(NO_ORDER))
		for (auto i : C) {
			for (auto j : expectation.Expecations) {
				/*if (i.Components.size() > 0) {
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
				}*/
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

bool Back_End_Test::Check_Assert(Back_Expectation_Set expectation, Base* a, string s)
{
	return false;
}

bool Back_End_Test::Check_Assert(long F, Base* a, Base* b)
{
	return false;
}

void Back_End_Test::Init()
{
}
