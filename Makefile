
ifneq ($(OS), Windows_NT)
	Additional_Flags += -fPIC -pie
endif

Additional_Flags += -o Evie -g

all:
	g++ --std=c++17 $(Additional_Flags) -fpermissive -lcurl -L"Dependencies/Curl/"  Cpp/*.cpp Cpp/BackEnd/*.cpp Cpp/Docker/*.cpp Cpp/Lexer/*.cpp Cpp/Nodes/*.cpp Cpp/Parser/*.cpp Cpp/PreProsessor/*.cpp Cpp/UI/*.cpp Tests/*.cpp Tests/Cpp/*.cpp