//
// Created by christoph on 20.03.23.
//

#include "Parser.h"
#include "../ast/nodes/RootNode.h"
#include "../ast/nodes/MovNode.h"
#include "../ast/nodes/ConstNode.h"
#include "../ast/nodes/RegNode.h"
#include "../ast/nodes/AluNode.h"
#include <map>

// ! Helper Functions

// ! Public Functions

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), position(tokens.begin()) {}

auto Parser::parse() -> std::unique_ptr<Node> {
    auto root = std::make_unique<RootNode>();

    while (peek().getType() != Token::END) {
        if (peek().getType() != Token::MNEMONIC) {
            throw "Parser Error: Expected Mnemonic!";
        }

        // TODO: Put these functions in a map, mapped to the mnemonic name string
        if (static_cast<std::string_view>(peek()) == "MOV") {
            root->addChild(std::move(mov()));
            continue;
        }

        if (static_cast<std::string_view>(peek()) == "ADD") {
            root->addChild(std::move(alu()));
            continue;
        }
    }

    return std::move(root);
}

// ! Private Functions

auto Parser::peek() const -> const Token & {
    return *position;
}

auto Parser::get() -> const Token & {
    return *(position++);
}

auto Parser::mov() -> std::unique_ptr<Node> {
    if (peek().getType() != Token::MNEMONIC || static_cast<std::string_view>(peek()) != "MOV") {
        throw "Parser Error: Expected 'MOV'!";
    }
    get(); // Eat 'MOV'

    std::unique_ptr<Node> sourceNode;
    if (peek().getType() == Token::NUMBER) {
        sourceNode = std::make_unique<ConstNode>(static_cast<uint8_t>(peek()));
    } else if (peek().getType() == Token::IDENTIFIER) {
        sourceNode = std::make_unique<RegNode>(static_cast<uint8_t>(peek()));
    } else {
        throw "Parser Error: Expected Constant or Register!";
    }
    get(); // Eat source

    const Token identifier = peek().subtoken(0, 3);
    const Token reg = peek().subtoken(3, 1); // Get reg number
    if (peek().getType() != Token::IDENTIFIER || static_cast<std::string_view>(identifier) != "reg") {
        throw "Parser Error: Expected Register!";
    }
    std::unique_ptr<Node> targetNode = std::make_unique<RegNode>(static_cast<uint8_t>(reg));
    get(); // Eat target

    return std::move(std::make_unique<MovNode>(std::move(sourceNode), std::move(targetNode)));
}

auto Parser::alu() -> std::unique_ptr<Node> {
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

    return std::move(std::make_unique<AluNode>(aluMap[static_cast<std::string>(get())])); // Eat alu
}
