cmake_minimum_required(VERSION 3.10)
project(Evie)

# Source files:
FILE(GLOB root Cpp/*.cpp)
FILE(GLOB ui Cpp/UI/*.cpp)
FILE(GLOB lexer Cpp/Lexer/*.cpp)
FILE(GLOB parser Cpp/Parser/*.cpp)
FILE(GLOB Docker Cpp/Docker/*.cpp)
FILE(GLOB TestSweet Cpp/Test/*.cpp)
FILE(GLOB PreProses Cpp/PreProsessor/*.cpp)
FILE(GLOB PostProses Cpp/PostProsessor/*.cpp)

# Add source files
add_executable(${PROJECT_NAME} 
                ${root} 
                ${lexer} 
                ${parser} 
                ${Docker}
                ${TestSweet}
                ${ui}
                ${PreProses}
                ${PostProses}
                )
                
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
target_compile_options(${PROJECT_NAME} PRIVATE)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)