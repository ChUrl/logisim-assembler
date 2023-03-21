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
    } else if (peek().getType() == Token::IDENTIFIER) {
        if (static_cast<std::string_view>(peek().subtoken(0, 3)) == "reg") {
            source = static_cast<uint8_t>(peek().subtoken(3, 1));
        } else if (static_cast<std::string_view>(peek()) == "input") {
            source = 6;
        }
    } else {
        throw "Parser Error: Expected Constant or Register!";
    }
    get(); // Eat source

    uint8_t target = 0;
    if (peek().getType() == Token::IDENTIFIER) {
        if (static_cast<std::string_view>(peek().subtoken(0, 3)) == "reg") {
            target = static_cast<uint8_t>(peek().subtoken(3, 1));
        } else if (static_cast<std::string_view>(peek()) == "output") {
            target = 6;
        }
    } else {
        throw "Parser Error: Expected Register!";
    }
    get(); // Eat target

    if (source > 6 || target > 6) {
        throw "Parser Error: Invalid Register!";
    }

    if (source != target) {
        // This happens on e.g. MOV 10, reg0
        ast->addChild(std::move(std::make_unique<MovNode>(source, target)));
    }
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
    std::map<std::string, JumpNode::JumpOperation> jmpMap = {{"JMP", JumpNode::ALWAYS},
                                                             {"JEQ", JumpNode::EQUAL_ZERO},
                                                             {"JLE", JumpNode::LESS_ZERO},
                                                             {"JLEQ", JumpNode::LESS_EQUAL_ZERO},
                                                             {"NOP", JumpNode::NEVER}, // TODO: ?
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
