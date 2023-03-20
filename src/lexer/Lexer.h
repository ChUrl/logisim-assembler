//
// Created by christoph on 20.03.23.
//

#ifndef LOGISIMASSEMBLER_LEXER_H
#define LOGISIMASSEMBLER_LEXER_H

#include <string>
#include <string_view>
#include "Token.h"

class Lexer {
public:
    explicit Lexer(std::string_view input_string);

    Lexer(const Lexer &copy) = delete;

    auto operator=(const Lexer &copy) -> Lexer & = delete;

    Lexer(Lexer &&move) = delete;

    auto operator=(Lexer &&move) -> Lexer & = delete;

    ~Lexer() = default;

    auto next() -> Token;

private:
    [[nodiscard]] auto peek() const -> char;

    auto get() -> char;

    auto identifier_or_mnemonic() -> Token;

    auto number() -> Token;

    auto address() -> Token;

    void comment();

private:
    std::string_view input_string;
    std::string_view::const_iterator position;
};

#endif //LOGISIMASSEMBLER_LEXER_H
