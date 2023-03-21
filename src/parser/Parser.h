//
// Created by christoph on 20.03.23.
//

#ifndef LOGISIMASSEMBLER_PARSER_H
#define LOGISIMASSEMBLER_PARSER_H

#include <memory>
#include <vector>
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

private:
    const std::vector<Token> &tokens;
    std::vector<Token>::const_iterator position;
    std::unique_ptr<Node> ast = std::make_unique<RootNode>();
};

#endif //LOGISIMASSEMBLER_PARSER_H
