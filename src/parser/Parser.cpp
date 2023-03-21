//
// Created by christoph on 20.03.23.
//

#include "Parser.h"
#include "../ast/nodes/MovNode.h"
#include "../ast/nodes/ConstNode.h"
#include "../ast/nodes/AluNode.h"
#include "../ast/nodes/JumpNode.h"

// ! Helper Functions

// ! Public Functions

Parser::Parser(const std::vector<Token> &tokens) : position(tokens.begin()) {}

auto Parser::parse() -> std::unique_ptr<Node> {
    while (peek().getType() != Token::END) {
        if (peek().getType() != Token::MNEMONIC) {
            throw "Parser Error: Expected Mnemonic!";
        }

        eaters[static_cast<std::string>(peek())](*this);
    }

    return std::move(ast);
}

// ! Private Functions

auto Parser::peek() const -> const Token & {
    return *position;
}

auto Parser::get() -> const Token & {
    return *(position++);
}

void Parser::mov() {
    if (peek().getType() != Token::MNEMONIC || static_cast<std::string_view>(peek()) != "MOV") {
        throw "Parser Error: Expected 'MOV'!";
    }
    get(); // Eat 'MOV'

    uint8_t source = 0; // Load from reg0
    if (peek().getType() == Token::NUMBER) {
        ast->addChild(std::move(std::make_unique<ConstNode>(static_cast<uint8_t>(peek())))); // Load constant to reg0
    } else if (peek().getType() == Token::IDENTIFIER && static_cast<std::string_view>(peek().subtoken(0, 3)) == "reg") {
        source = static_cast<uint8_t>(peek().subtoken(3, 1));
    } else {
        throw "Parser Error: Expected Constant or Register!";
    }
    get(); // Eat source

    if (peek().getType() != Token::IDENTIFIER || static_cast<std::string_view>(peek().subtoken(0, 3)) != "reg") {
        throw "Parser Error: Expected Register!";
    }
    auto target = static_cast<uint8_t>(peek().subtoken(3, 1));
    get(); // Eat target

    ast->addChild(std::move(std::make_unique<MovNode>(source, target)));
}

void Parser::alu() {
    std::map<std::string, AluNode::AluOperation> aluMap = {{"AND",  AluNode::AND},
                                                           {"OR",   AluNode::OR},
                                                           {"NAND", AluNode::NAND},
                                                           {"NOR",  AluNode::NOR},
                                                           {"ADD",  AluNode::ADD},
                                                           {"SUB",  AluNode::SUB}};

    if (peek().getType() != Token::MNEMONIC) {
        throw "Parser Error: Expected Mnemonic!";
    }
    if (!aluMap.contains(static_cast<std::string>(peek()))) {
        throw "Parser Error: Invalid ALU operation!";
    }

    ast->addChild(std::move(std::make_unique<AluNode>(aluMap[static_cast<std::string>(get())]))); // Eat alu
}

void Parser::jmp() {
    std::map<std::string, JumpNode::JumpOperation> jmpMap = {{"JEQ", JumpNode::EQUAL_ZERO},
                                                             {"JLE", JumpNode::LESS_ZERO},
                                                             {"JLEQ", JumpNode::LESS_EQUAL_ZERO},
                                                             {"JNEQ", JumpNode::NOT_ZERO},
                                                             {"JGR", JumpNode::GREATER_ZERO},
                                                             {"JGEQ", JumpNode::GREATER_EQUAL_ZERO}};

    if (peek().getType() != Token::MNEMONIC) {
        throw "Parser Error: Expected Mnemonic!";
    }
    if (!jmpMap.contains(static_cast<std::string>(peek()))) {
        throw "Parser Error: Invalid JMP operation!";
    }

    ast->addChild(std::move(std::make_unique<JumpNode>(jmpMap[static_cast<std::string>(get())]))); // Eat jmp
}
