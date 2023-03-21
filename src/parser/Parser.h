//
// Created by christoph on 20.03.23.
//

#ifndef LOGISIMASSEMBLER_PARSER_H
#define LOGISIMASSEMBLER_PARSER_H

#include <memory>
#include <vector>
#include "../lexer/Token.h"
#include "../ast/Node.h"

class Parser {
public:
    Parser(const std::vector<Token> &tokens);

    Parser(std::vector<Token> &&tokens) = delete;

    auto parse() -> std::unique_ptr<Node>;

private:
    [[nodiscard]] auto peek() const -> const Token &;

    auto get() -> const Token &;

    auto mov() -> std::unique_ptr<Node>;

    auto alu() -> std::unique_ptr<Node>;

private:
    const std::vector<Token> &tokens;

    std::vector<Token>::const_iterator position;
};

#endif //LOGISIMASSEMBLER_PARSER_H
