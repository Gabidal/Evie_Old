
ifneq ($(OS), Windows_NT)
	Additional_Flags += -fPIC -pie
endif

Additional_Flags += -o Evie -g

compile:
	g++ --std=c++17 $(Additional_Flags) Cpp/*.cpp Cpp/Interpreter/*.cpp Cpp/Selector/*.cpp Cpp/OpC/*.cpp Cpp/UI/*.cpp Cpp/Back/*.cpp Cpp/Lexer/*.cpp Cpp/Linux/*.cpp Cpp/Parser/*.cpp Cpp/Emulator/*.cpp Cpp/Windows/*.cpp Cpp/Architecture/x86/*.cpp Cpp/Architecture/ARM/*.cpp