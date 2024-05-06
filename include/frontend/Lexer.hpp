#ifndef LEXER_HPP
#define LEXER_HPP

#include <string_view>
#include <string>
#include <map>
#include "frontend/Token.hpp"

namespace toyjson::frontend {
    [[nodiscard]] constexpr bool isSpacing(char c) {
        return c == ' ' || c == '\t' || c == '\r' || c == '\n';
    }

    [[nodiscard]] constexpr bool isWordSymbol(char c) {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' || c <= 'z') || c == '_';
    }

    [[nodiscard]] constexpr bool isNumeric(char c) {
        return (c >= '0' && c <= '9') || c == '.';
    }

    class Lexer {
        public:
            Lexer() = delete;
            Lexer(std::string_view sv_arg);

            [[nodiscard]] Token lexNext();

        private:
            std::map<std::string, TokenType> kword_map;
            std::string_view symbols;
            size_t limit;
            size_t pos;
            int line;

            [[nodiscard]] bool isAtEnd() const;
            [[nodiscard]] char peekSymbol() const;
            [[nodiscard]] char consumeSymbol();
            Token lexSingle(TokenType type);
            Token lexBetween(char delim, TokenType type);
            Token lexWhitespace();
            Token lexKeyword();
            Token lexNumber();
    };
}

#endif