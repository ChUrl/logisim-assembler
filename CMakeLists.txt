cmake_minimum_required(VERSION 3.25)
project(LogisimAssembler)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.81 COMPONENTS program_options REQUIRED)

add_executable(lasm
        src/main.cpp
        src/lexer/Token.cpp
        src/lexer/Lexer.cpp
        src/ast/Node.cpp
        src/ast/nodes/RootNode.cpp
        src/ast/nodes/ConstNode.cpp
        src/ast/nodes/RegNode.cpp
        src/ast/nodes/MovNode.cpp
        src/ast/nodes/AluNode.cpp
        src/ast/nodes/JumpNode.cpp
        src/ast/Observer.cpp
        src/ast/PrefixObserver.cpp
        src/ast/PostfixObserver.cpp
        src/codegen/PrintObserver.cpp
        src/codegen/CodegenObserver.cpp
        src/parser/Parser.cpp)

target_link_libraries(lasm Boost::program_options)