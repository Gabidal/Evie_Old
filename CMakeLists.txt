cmake_minimum_required(VERSION 3.10)
project(Evie)

# Source files:
FILE(GLOB root Cpp/*.cpp)
FILE(GLOB interpreter Cpp/Interpreter/*.cpp)
FILE(GLOB selector Cpp/Selector/*.cpp)
FILE(GLOB opc Cpp/OpC/*.cpp)
FILE(GLOB ui Cpp/UI/*.cpp)
FILE(GLOB back Cpp/Back/*.cpp)
FILE(GLOB lexer Cpp/Lexer/*.cpp)
FILE(GLOB linux Cpp/Linux/*.cpp)
FILE(GLOB parser Cpp/Parser/*.cpp)
FILE(GLOB emulator Cpp/Emulator/*.cpp)
FILE(GLOB windows Cpp/Windows/*.cpp)
FILE(GLOB x86 Cpp/Architecture/x86/*.cpp)
FILE(GLOB arm Cpp/Architecture/ARM/*.cpp)

# Add source files
add_executable(${PROJECT_NAME} 
                ${root} 
                ${interpreter} 
                ${selector} 
                ${opc} 
                ${ui} 
                ${back} 
                ${lexer} 
                ${parser} 
                ${emulator} 
                ${x86} 
                ${arm})
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
target_compile_options(${PROJECT_NAME} PRIVATE)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)