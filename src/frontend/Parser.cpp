/**
 * @file Parser.cpp
 * @author DrkWithT
 * @brief Implements recursive descent parser.
 * @date 2024-05-06
 * @note Relies on copy-elision since C++17 to make unique_ptr<JsonAny> from temporary XXXField objects.
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <memory>
#include <stdexcept>
#include <utility>
#include <exception>
#include <string>
#include <sstream>
#include <iostream>
#include "data/Value.hpp"
#include "frontend/ParseInfo.hpp"
#include "frontend/Parser.hpp"
#include "frontend/Token.hpp"

namespace toyjson::frontend {
    /* Usings */
    using JsonNull = toyjson::data::NullField;
    using JsonBoolean = toyjson::data::BooleanField;
    using JsonNumber = toyjson::data::NumberField;
    using JsonString = toyjson::data::StringField;
    using JsonArray = toyjson::data::ArrayField;
    using JsonObject = toyjson::data::ObjectField;
    using JsonAny = toyjson::data::AnyField;

    /* Parse public impl. */

    Parser::Parser(std::string_view json_sv)
        : lexer {json_sv}, current {.begin = 0, .length = 0, .type = TokenType::unknown}, previous {.begin = 0, .length = 0, .type = TokenType::unknown}, symbols {json_sv} {}

    JsonDoc Parser::parseToADT(const std::string& name) {
        consumeToken({}); // pass initial unknowns

        auto x_root = parseValue();

        return JsonDoc {name, std::move(x_root)};
    }

    /* Parser private impl. */

    std::string Parser::createErrorMsg(const Token& culprit, ParseStatus status, std::string_view msg_sv) {
        std::ostringstream sout {};

        sout << toErrorName(status) << " at position " << culprit.begin << ": " << msg_sv;

        return sout.str();
    }

    void Parser::logErrorBy(const Token& culprit, ParseStatus status, std::string_view msg_sv) const {
        std::cerr << toErrorName(status) << " at position " << culprit.begin << ": " << msg_sv;
    }

    const Token& Parser::peekCurrent() const {
        return current;
    }

    const Token& Parser::peekPrevious() const {
        return previous;
    }

    bool Parser::isAtEOF() const {
        return peekCurrent().type == TokenType::eof;
    }

    Token Parser::doAdvance() {
        Token temp;

        do {
            temp = lexer.lexNext();

            if (temp.type == TokenType::unknown) {
                logErrorBy(temp, ParseStatus::err_unknown_token, "Unknown token!\n");
                continue;
            }

            if (temp.type == TokenType::whitespace)
                continue;

            break;
        } while (!isAtEOF());

        return temp;
    }

    bool Parser::matchToken(const Token& token, std::initializer_list<TokenType> types) {
        return matchTokenImpl(token, types);
    }

    void Parser::consumeToken(std::initializer_list<TokenType> types) {
        if (isAtEOF())
            return;

        if (matchToken(current, types)) {
            previous = current;
            current = doAdvance();
            return;
        }

        throw std::runtime_error {createErrorMsg(current, ParseStatus::err_misplaced_token, "Unexpected token!\n")};
    }

    std::shared_ptr<JsonValue> Parser::parseValue() {
        TokenType peeked_type = peekCurrent().type;

        if (peeked_type == TokenType::lt_null) {
            auto x_null = std::make_shared<JsonAny>(JsonNull());
            consumeToken({});
            return x_null;
        } else if (peeked_type == TokenType::lt_true || peeked_type == TokenType::lt_false) {
            auto x_bool = std::make_shared<JsonAny>(JsonBoolean(peeked_type == TokenType::lt_true));
            consumeToken({});
            return x_bool;
        } else if (peeked_type == TokenType::lt_number) {
            auto lexeme = getLexeme(peekCurrent(), symbols);
            consumeToken({});
            return std::make_shared<JsonAny>(JsonNumber(std::stod(lexeme)));
        } else if (peeked_type == TokenType::lt_strbody) {
            auto lexeme = getLexeme(peekCurrent(), symbols);
            consumeToken({});
            return std::make_shared<JsonAny>(JsonString(std::move(lexeme)));
        } else if (peeked_type == TokenType::lbrack) {
            return parseArray();
        } else if (peeked_type == TokenType::lbrace) {
            return parseObject();
        } else {
            throw std::runtime_error {createErrorMsg(peekCurrent(), ParseStatus::err_misplaced_token, "Unexpected token for value.\n")};
        }
    }

    std::shared_ptr<JsonValue> Parser::parseArray() {
        consumeToken({}); // pass '[' symbol

        std::vector<std::shared_ptr<JsonValue>> x_items {};

        while (!isAtEOF()) {
            if (matchToken(peekCurrent(), {TokenType::rbrack})) {
                consumeToken({});
                break;
            }

            auto x_item = parseValue();
            x_items.emplace_back(std::move(x_item));

            if (matchToken(peekCurrent(), {TokenType::comma})) {
                consumeToken({});
            } else if (matchToken(peekCurrent(), {TokenType::rbrack})) {
                continue;
            } else {
                throw std::runtime_error {createErrorMsg(peekCurrent(), ParseStatus::err_misplaced_token, "Unexpected token in Array.\n")};
            }
        }

        return std::make_shared<JsonAny>(JsonArray(std::move(x_items)));
    }

    std::shared_ptr<JsonValue> Parser::parseObject() {
        consumeToken({}); // pass '{' symbol

        std::map<std::string, std::shared_ptr<JsonValue>> x_dict {};

        while (!isAtEOF()) {
            if (matchToken(peekCurrent(), {TokenType::rbrace})) {
                consumeToken({});
                break;
            }

            auto x_name = getLexeme(peekCurrent(), symbols);

            consumeToken({TokenType::lt_strbody});

            consumeToken({TokenType::colon});

            auto x_prop_val = parseValue();

            x_dict[x_name] = std::move(x_prop_val);

            if (matchToken(peekCurrent(), {TokenType::comma})) {
                consumeToken({});
            } else if (matchToken(peekCurrent(), {TokenType::rbrace})) {
                continue;
            } else {
                throw std::runtime_error {createErrorMsg(peekCurrent(), ParseStatus::err_misplaced_token, "Unexpected token in Object.\n")};
            }
        }

        return std::make_shared<JsonAny>(JsonObject(std::move(x_dict)));
    }
}
