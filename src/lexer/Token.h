//
// Created by christoph on 20.03.23.
//

#ifndef LOGISIMASSEMBLER_TOKEN_H
#define LOGISIMASSEMBLER_TOKEN_H

#include <cstdint>
#include <string_view>

class Token {
public:
    enum Type : uint8_t {
        MNEMONIC,
        IDENTIFIER,
        NUMBER,
        ADDRESS, // Using []

        // TODO: Inline calculations
        // PLUS,
        // MINUS,
        // ASTERISK,
        // SLASH,

        END,
        UNEXPECTED
    };

public:
    explicit Token(Type type);

    Token(Type type, std::string_view lexeme);

    Token(const Token &copy) = default;

    auto operator=(const Token &copy) -> Token & = default;

    Token(Token &&move) = default;

    auto operator=(Token &&move) -> Token & = default;

    ~Token() = default;

    [[nodiscard]] auto getType() const -> Type;

    [[nodiscard]] auto getTypeName() const -> std::string;

    explicit operator std::string_view() const;

private:
    Type type;

    // ! The Token only contains a reference to the string kept inside the Lexer.
    // ! If the Lexer is gone, all Tokens will be invalid!
    std::string lexeme;
};

#endif //LOGISIMASSEMBLER_TOKEN_H
