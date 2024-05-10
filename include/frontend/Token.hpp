#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <initializer_list>
#include <string_view>
#include <string>

namespace toyjson::frontend {
    enum class TokenType {
        unknown,
        whitespace,
        lbrace,
        rbrace,
        lbrack,
        rbrack,
        colon,
        comma,
        lt_null,
        lt_true,
        lt_false,
        lt_number,
        lt_strbody,
        eof
    };

    struct Token {
        size_t begin;
        size_t length;
        TokenType type;
    };

    [[nodiscard]] std::string_view viewLexeme(const Token& token, std::string_view source_sv);

    [[nodiscard]] std::string getLexeme(const Token& token, std::string_view source_sv);

    [[nodiscard]] constexpr bool matchTokenImpl(Token token, std::initializer_list<TokenType> types) {
        if (types.size() == 0)
            return true;

        for (const auto& item : types) {
            if (token.type == item)
                return true;
        }

        return false;
    }
};

#endif