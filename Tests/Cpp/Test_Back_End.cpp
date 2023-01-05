#include "../H/Test_Back_End.h"
#include "../../H/UI/Usr.h"
#include "../../H/Nodes/Node.h"
#include "../../H/BackEnd/Selector.h"
#include "../../H/UI/Safe.h"
#include "../../H/Docker/Mangler.h"
#include "../../H/Docker/Docker.h"


#ifdef _WIN32

typedef __int64(__stdcall* FARPROC)();

extern "C" FARPROC __stdcall GetProcAddress(void*, const char*);
extern "C" void*   __stdcall LoadLibraryA  (const char*);
extern "C" int     __stdcall FreeLibrary   (void*);
extern "C" int    __stdcall GetLastError  ();

template<typename R, typename... T>
R Call(void* handle, const char* name, T... arguments) {
	auto f = (R(*)(T...))GetProcAddress(handle, name);

	return f(arguments...);
}
//int a = Call<int>(Handle, "Start_Test", 1, 2, 1.1);
int Back_End_Test::Run_Dll(string f) {
	auto Handle = LoadLibraryA(f.c_str());
	if (Handle == nullptr){
		throw::runtime_error("INTERNAL ERROR!");
	}

	auto Func = (int(*)())GetProcAddress(Handle, "_Z10Start_Testv");
	//auto Func = (int(*)())GetProcAddress(Handle, "main");
	if (Func == nullptr)
		throw::runtime_error("INTERNAL ERROR!");

	int Result = Func();

	FreeLibrary(Handle);

	return Result;
}

#else 
#include <dlfcn.h>
int Back_End_Test::Run_Dll(string f) {

}
#endif

bool Use_ARM = false;
bool Generate_Debug;


extern Usr* sys;
extern Node* Global_Scope;
extern Selector* selector;
extern x86_64 X86_64;
extern int _SYSTEM_BIT_SIZE_;

extern string Output;
extern int arg_count;
extern vector<pair<string, vector<pair<string, pair<int, string>>>>> MANGLER::IDS;
extern vector<pair<string, string>> DOCKER::Working_Dir;
extern int ID;
extern string* FileName;

extern int Build(int argc, const char* argv[]);

vector<Base*> Back_End_Test::Run(string File)
{
	MANGLER::IDS.clear();
	arg_count = 0;
	DOCKER::Working_Dir.clear();
	DOCKER::Included_Files.clear();
	DOCKER::Assembly_Source_File.clear();
	Global_Scope = nullptr;
	sys = nullptr;
	selector = nullptr;
	ID = 2;
	FileName = new string("No File");

	const char** argv; 
	int argc;
	string Use_Debug;
	if (Generate_Debug) 
		Use_Debug = "-d";
	if (Use_ARM) {
		argv = new const char* [9 + (Use_Debug == "-d")] { (new string(Executable_Location))->c_str(), "-in", File.c_str(), "-f", "dll", "-arch", "-arm", "-reference-count-size", "0" , Use_Debug.c_str() };
		argc = 9 + (Use_Debug == "-d");
		Output = "";
	}
	else {
		argv = new const char* [7 + (Use_Debug == "-d")] { (new string(Executable_Location))->c_str(), "-in", File.c_str(), "-f", "asm", "-reference-count-size", "0", Use_Debug.c_str() };
		argc = 7 + (Use_Debug == "-d");
		Output = ".intel_syntax noprefix\n";
	}
	
	Build(argc, argv);

	return { new Numeric_Info{Run_Dll(File + ".dll")} };
}

void Back_End_Test::Factory()
{
	cout << Magenta << "x86_64 -Release tests:" << Reset << endl;
	Use_ARM = false;
	Generate_Debug = false;
	for (auto i : Tests) {
		Check_Assert(i.first, i.second);
	}
	cout << "\n";
	cout << Magenta << "x86_64 -Debug tests:" << Reset << endl;
	Use_ARM = false;
	Generate_Debug = true;
	for (auto i : Tests) {
		Check_Assert(i.first, i.second);
	}
	cout << "\n";		

	cout << "\n";	
	/*
	cout << Magenta << "\nARMv8_64 tests:" << Reset << endl;
	Use_ARM = true;
	for (auto i : Tests) {
		Check_Assert(i.first, i.second);
	}
	*/
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
	if (is(F, NO_NAMES)) {
		if (a->F == b->F)
			return true;
		return false;
	}
	else if (a->Type == NUMERIC_INFO) {
		if (((Numeric_Info&)*a).Val == ((Numeric_Info&)*b).Val)
			return true;
		return false;
	}
	else if (a->Type == TEXT_INFO) {
		if (((Text_Info&)*a).Val == ((Text_Info&)*b).Val)
			return true;
		return false;
	}
	return false;
}

void Back_End_Test::Init()
{
	//what we expect the function to return, file name
	Tests = {
		//{{1}, "Tests/IO/main"},	
		{{2}, "IO/Test.e"},
		{{5}, "Tests/IO/Template.e"},
		{{0}, "Tests/IO/NameSpace.e"},
		{{1}, "Tests/IO/Comment.e"},
		{{5}, "Tests/IO/Func.e"},
		{{1}, "Tests/IO/Type.e"},
		{{2}, "Tests/IO/Cast.e"},
		{{100}, "Tests/IO/Conditions.e"},
		{{1}, "Tests/IO/Array.e"},
		{{-6}, "Tests/IO/Math.e"},
		{{1}, "Tests/IO/Destructor.e"},
		{{10}, "Tests/IO/Ptr.e"},
		{{4}, "Tests/IO/Global.e"},
	};
}
