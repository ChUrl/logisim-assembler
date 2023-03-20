cmake_minimum_required(VERSION 3.25)
project(LogisimAssembler)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.81 COMPONENTS program_options REQUIRED)

add_executable(lasm
        src/main.cpp
        src/lexer/Token.cpp
        src/lexer/Lexer.cpp)

target_link_libraries(lasm Boost::program_options)