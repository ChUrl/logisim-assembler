//
// Created by christoph on 20.03.23.
//

#include <array>
#include <string>
#include "Token.h"

Token::Token(Token::Type type) : type(type) {}

Token::Token(Token::Type type, std::string_view lexeme) : type(type), lexeme(lexeme) {}

auto Token::getType() const -> Token::Type {
    return type;
}

auto Token::getTypeName() const -> std::string {
    return std::array<std::string, 6> {"MNEMONIC",
                                       "IDENTIFIER",
                                       "NUMBER",
                                       "ADDRESS",
                                       "END",
                                       "UNEXPECTED"}[type];
}

Token::operator std::string_view() const {
    return lexeme;
}
