ifeq ($(OS), Windows_NT)
	Additional_Flags += -lkernel32 -lWs2_32 -lWldap32 -lcrypt32 -ladvapi32 -lmsvcrt -o Evie -L"Dependencies/Curl/"
else
	Additional_Flags += -lm -ldl -lstdc++ -o Evie 
endif

Debuggarna:
	g++ --std=c++20 $(Additional_Flags) -g -fpermissive Cpp/*.cpp Cpp/BackEnd/*.cpp Cpp/Docker/*.cpp Cpp/Lexer/*.cpp Cpp/Nodes/*.cpp Cpp/Parser/*.cpp Cpp/PreProsessor/*.cpp Cpp/UI/*.cpp Tests/*.cpp Tests/Cpp/*.cpp -lcurl

all:
	g++ --std=c++20 $(Additional_Flags) -fpermissive Cpp/*.cpp Cpp/BackEnd/*.cpp Cpp/Docker/*.cpp Cpp/Lexer/*.cpp Cpp/Nodes/*.cpp Cpp/Parser/*.cpp Cpp/PreProsessor/*.cpp Cpp/UI/*.cpp Tests/*.cpp Tests/Cpp/*.cpp -lcurl