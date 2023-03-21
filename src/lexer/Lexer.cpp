//
// Created by christoph on 20.03.23.
//

#include <algorithm>
#include <vector>
#include "Lexer.h"

// ! Helper Functions

auto is_whitespace(const char character) -> bool {
    const auto ascii_value = static_cast<uint8_t>(character);
    const uint8_t ascii_tab = 9;
    const uint8_t ascii_cr = 13;
    const uint8_t ascii_space = 32;

    return (ascii_value >= ascii_tab && ascii_value <= ascii_cr)
           || ascii_value == ascii_space;
}

auto is_ignored(const char character) -> bool {
    // TODO: Any other ignored characters that could happen in the program?
    return character == ',';
}

auto is_numeric(const char character) -> bool {
    const auto ascii_value = static_cast<uint8_t>(character);
    const uint8_t ascii_zero = 48;
    const uint8_t ascii_nine = 57;

    return ascii_value >= ascii_zero && ascii_value <= ascii_nine;
}

auto is_alphabetical(const char character) -> bool {
    const auto ascii_value = static_cast<uint8_t>(character);
    const uint8_t ascii_a = 97;
    const uint8_t ascii_A = 65;
    const uint8_t ascii_z = 122;
    const uint8_t ascii_Z = 90;
    const uint8_t ascii_underscore = 95;

    return (ascii_value >= ascii_a && ascii_value <= ascii_z)
           || (ascii_value >= ascii_A && ascii_value <= ascii_Z)
           || ascii_value == ascii_underscore;
}

auto is_mnemonic(const Token &token) -> bool {
    // TODO: Move this to a separate header
    const std::vector<std::string> mnemonics = {"MOV",
                                                "AND", "OR", "NAND", "NOR", "ADD", "SUB",
                                                "JMP", "JEQ", "JLE", "JLEQ", "NOP", "JNEQ", "JGR", "JGEQ"};

    return std::find(mnemonics.begin(), mnemonics.end(), static_cast<std::string_view>(token))
           != mnemonics.end();
}

// ! Public Functions

Lexer::Lexer(std::string_view input_string)
        : input_string(input_string), position(input_string.begin()) {}

auto Lexer::next() -> Token {
    // Skip past everything that doesn't contain program information
    while (is_whitespace(peek()) || peek() == ',' || peek() == '#') {
        if (peek() == '#') {
            // Eat whole comment, we can't decide if sth is a comment after eating #
            comment();
        } else {
            get();
        }
    }

    if (position >= input_string.end()) {
        return static_cast<Token>(Token::END);
    }

    if (is_numeric(peek())) {
        return number();
    }

    if (peek() == '[') {
        return address();
    }

    if (is_alphabetical(peek())) {
        const Token token = identifier_or_mnemonic();
        if (is_mnemonic(token)) {
            return {Token::MNEMONIC, static_cast<std::string_view>(token)};
        }
        return {Token::IDENTIFIER, static_cast<std::string_view>(token)};
    }

    return {Token::UNEXPECTED, std::string_view(position, position + 1)};
}

// ! Private Functions

auto Lexer::peek() const -> char {
    return *position;
}

auto Lexer::get() -> char {
    return *(position++);
}

auto Lexer::identifier_or_mnemonic() -> Token {
    const std::string_view::const_iterator begin = position;
    while (peek() != ' ' && (is_alphabetical(peek()) || is_numeric(peek()))) {
        get();
    }
    const std::string_view::const_iterator end = position;

    // We don't know the type yet, so use UNEXPECTED
    return {Token::UNEXPECTED, std::string_view(begin, end)};
}

auto Lexer::number() -> Token {
    const std::string_view::const_iterator begin = position;
    while (is_numeric(peek())) {
        get();
    }
    const std::string_view::const_iterator end = position;

    return {Token::NUMBER, std::string_view(begin, end)};
}

auto Lexer::address() -> Token {
    get(); // Eat '['

    const std::string_view::const_iterator begin = position;
    while (is_numeric(peek())) {
        get(); // Eat the address number
    }
    const std::string_view::const_iterator end = position;

    if (peek() != ']') {
        throw "Lexer Error: Expected ']'!";
    }
    get(); // Eat ']'

    return {Token::ADDRESS, std::string_view(begin, end)};
}

void Lexer::comment() {
    // Eat the whole line
    while (peek() != '\n') {
        get();
    }
}
