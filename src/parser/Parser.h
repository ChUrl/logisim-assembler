//
// Created by christoph on 20.03.23.
//

#ifndef LOGISIMASSEMBLER_PARSER_H
#define LOGISIMASSEMBLER_PARSER_H

#include <memory>
#include <vector>
#include <map>
#include <functional>
#include "../lexer/Token.h"
#include "../ast/Node.h"
#include "../ast/nodes/RootNode.h"

class Parser {
public:
    Parser(const std::vector<Token> &tokens);

    Parser(std::vector<Token> &&tokens) = delete;

    auto parse() -> std::unique_ptr<Node>;

private:
    [[nodiscard]] auto peek() const -> const Token &;

    auto get() -> const Token &;

    void mov();

    void alu();

    void jmp();

private:
    std::vector<Token>::const_iterator position;
    std::unique_ptr<Node> ast = std::make_unique<RootNode>();

    std::map<std::string, std::function<void(Parser &)>> eaters = {{"MOV",  &Parser::mov},
                                                                   {"AND",  &Parser::alu},
                                                                   {"OR",   &Parser::alu},
                                                                   {"NAND", &Parser::alu},
                                                                   {"NOR",  &Parser::alu},
                                                                   {"ADD",  &Parser::alu},
                                                                   {"SUB",  &Parser::alu},
                                                                   {"JEQ",  &Parser::jmp},
                                                                   {"JLE",  &Parser::jmp},
                                                                   {"JLEQ", &Parser::jmp},
                                                                   {"JNEQ", &Parser::jmp},
                                                                   {"JGR",  &Parser::jmp},
                                                                   {"JGEQ", &Parser::jmp}};
};

#endif //LOGISIMASSEMBLER_PARSER_H
