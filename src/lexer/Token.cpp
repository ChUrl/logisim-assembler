//
// Created by christoph on 20.03.23.
//

#include <array>
#include <string>
#include <charconv>
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

auto Token::subtoken(uint8_t pos, uint8_t len) const -> Token {
    return std::move(Token(type, lexeme.substr(pos, len)));
}

Token::operator std::string_view() const {
    return lexeme;
}

Token::operator std::string() const {
    return lexeme;
}

// https://stackoverflow.com/questions/56634507/safely-convert-stdstring-view-to-int-like-stoi-or-atoi#answer-65675200
Token::operator uint8_t() const {
    uint8_t out;
    const std::from_chars_result result = std::from_chars(lexeme.data(), lexeme.data() + lexeme.size(), out);
    if (result.ec == std::errc::invalid_argument || result.ec == std::errc::result_out_of_range)
    {
        throw "Conversion Error: Can't convert Token to uint8_t!";
    }
    return out;
}
