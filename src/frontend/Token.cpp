/**
 * @file Token.cpp
 * @author DrkWithT
 * @brief Implements token utilities.
 * @date 2024-05-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <sstream>
#include "frontend/Token.hpp"

namespace toyjson::frontend {
    /* Token Utils */

    std::string_view viewLexeme(const Token& token, std::string_view source_sv) {
        if (token.type == TokenType::eof)
            return source_sv.substr(0, 0);

        return source_sv.substr(token.begin, token.length);
    }

    std::string getLexeme(const Token& token, std::string_view source_sv) {
        std::ostringstream sout {};

        auto lexeme_cursor = source_sv.begin() + token.begin;
        auto lexeme_end = lexeme_cursor + token.length;

        while (lexeme_cursor != lexeme_end) {
            char c = *lexeme_cursor;
            sout << c;
            lexeme_cursor++;
        }

        return sout.str();
    }
}