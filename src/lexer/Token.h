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

    Token(Token &&move) noexcept = default;

    auto operator=(Token &&move) noexcept -> Token & = default;

    ~Token() = default;

    [[nodiscard]] auto getType() const -> Type;

    [[nodiscard]] auto getTypeName() const -> std::string;

    [[nodiscard]] auto subtoken(uint8_t pos, uint8_t len) const -> Token;

    explicit operator std::string_view() const;

    explicit operator std::string() const;

    explicit operator uint8_t() const;

private:
    Type type;
    std::string lexeme;
};

#endif //LOGISIMASSEMBLER_TOKEN_H
