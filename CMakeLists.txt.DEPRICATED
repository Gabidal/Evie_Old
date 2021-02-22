cmake_minimum_required(VERSION 3.10)
project(Evie)

# Source files:
FILE(GLOB root Cpp/*.cpp)
FILE(GLOB Back_End Cpp/BackEnd/*.cpp)
FILE(GLOB Docker Cpp/Docker/*.cpp)
FILE(GLOB Lexer Cpp/Lexer/*.cpp)
FILE(GLOB Nodes Cpp/Nodes/*.cpp)
FILE(GLOB Parser Cpp/Parser/*.cpp)
FILE(GLOB Pre Cpp/PreProsessor/*.cpp)
FILE(GLOB UI Cpp/UI/*.cpp)


FILE(GLOB Suite Tests/*.cpp)
FILE(GLOB Tests Tests/Cpp/*.cpp)


# Add source files
add_executable(${PROJECT_NAME} 
                ${root} 
                ${Back_End} 
                ${Docker} 
                ${Lexer}
                ${Nodes}
                ${Parser}
                ${Pre}
                ${UI}

                ${Suite}
                ${Tests}
                )
                
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
target_compile_options(${PROJECT_NAME} PRIVATE)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)