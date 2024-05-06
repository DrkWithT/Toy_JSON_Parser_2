/**
 * @file Lexer.cpp
 * @author DrkWithT
 * @brief Implements tokenizer.
 * @date 2024-05-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "frontend/Lexer.hpp"
#include "frontend/Token.hpp"

namespace toyjson::frontend {
    /* Lexer public impl */

    Lexer::Lexer(std::string_view sv_arg)
    : kword_map{}, symbols {sv_arg}, limit {sv_arg.length()}, pos {0}, line {0} {
        kword_map["null"] = TokenType::lt_null;
        kword_map["true"] = TokenType::lt_true;
        kword_map["false"] = TokenType::lt_false;
    }

    Token Lexer::lexNext() {
        if (isAtEnd())
            return {.begin = limit, .length = 1, .type = TokenType::eof};

        char peeked = peekSymbol();

        if (isSpacing(peeked))
            return lexWhitespace();

        switch (peeked) {
            case '{':
                return lexSingle(TokenType::lbrace);
            case '}':
                return lexSingle(TokenType::rbrace);
            case '[':
                return lexSingle(TokenType::lbrack);
            case ']':
                return lexSingle(TokenType::rbrack);
            case ':':
                return lexSingle(TokenType::colon);
            case ',':
                return lexSingle(TokenType::comma);
            case '\"':
                return lexBetween('\"', TokenType::lt_strbody);
            default:
                break;
        }

        if (isNumeric(peeked))
            return lexNumber();
        else if (isWordSymbol(peeked))
            return lexKeyword();

        pos++;

        return {.begin = pos - 1, .length = 1, .type = TokenType::unknown};
    }

    /* Lexer private impl */

    bool Lexer::isAtEnd() const {
        return pos >= limit;
    }

    char Lexer::peekSymbol() const {
        return symbols.at(pos);
    }

    char Lexer::consumeSymbol() {
        char temp = peekSymbol();

        pos++;

        return temp;
    }

    Token Lexer::lexSingle(TokenType type) {
        size_t begin = pos;

        pos++;

        return {.begin = begin, .length = 1, .type = type};
    }

    Token Lexer::lexBetween(char delim, TokenType type) {
        size_t begin = ++pos;
        size_t length = 0;
        char c;
        bool closed = false; // has right-side delim

        while (!isAtEnd()) {
            c = consumeSymbol();

            if (c == delim) {
                closed = true;
                c = consumeSymbol();
                break;
            }

            length++;
        }

        return {
            .begin = begin,
            .length = length,
            .type = (closed) ? type : TokenType::unknown
        };
    }

    Token Lexer::lexWhitespace() {
        size_t begin = pos;
        size_t length = 0;
        char c;

        while (!isAtEnd()) {
            c = consumeSymbol();

            if (!isSpacing(c))
                break;

            if (c == '\n')
                line++;

            length++;
        }

        return {.begin = begin, .length = length, .type = TokenType::whitespace};
    }

    Token Lexer::lexKeyword() {
        size_t begin = 0;
        size_t length = 0;
        char c;

        while (!isAtEnd()) {
            c = consumeSymbol();

            if (!isWordSymbol(c))
                break;

            length++;
        }

        Token result = {.begin = begin, .length = length, .type = TokenType::unknown};
        auto lexeme = getLexeme(result, symbols);

        if (kword_map.find(lexeme) == kword_map.end())
            return result;

        result.type = kword_map.at(lexeme);

        return result;
    }

    Token Lexer::lexNumber() {
        size_t begin = 0;
        size_t length = 0;
        int dots = 0;
        char c;

        while (!isAtEnd()) {
            c = consumeSymbol();

            if (!isNumeric(c))
                break;

            if (c == '.')
                dots++;

            length++;
        }

        switch (dots) {
            case 0:
            case 1:
                return {.begin = begin, .length = length, .type = TokenType::lt_number};
            default:
                return {.begin = begin, .length = length, .type = TokenType::unknown};
        }
    }
}
