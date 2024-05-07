#ifndef PARSER_HPP
#define PARSER_HPP

#include <string_view>
#include <initializer_list>
#include <memory>
#include "frontend/Token.hpp"
#include "frontend/Lexer.hpp"
#include "data/Value.hpp"
#include "frontend/ParseInfo.hpp"

namespace toyjson::frontend {
    using JsonValue = data::IJsonValue;
    using JsonDoc = data::ToyJsonDocument;

    class Parser {
        public:
            Parser(std::string_view json_sv);

            [[nodiscard]] JsonDoc parseToADT(const std::string& name);

        private:
            Lexer lexer;
            Token current;
            Token previous;
            std::string_view symbols;

            [[nodiscard ]] std::string createErrorMsg(const Token& culprit, ParseStatus status, std::string_view msg_sv);
            void logErrorBy(const Token& culprit, ParseStatus status, std::string_view msg_sv) const;

            const Token& peekCurrent() const;
            const Token& peekPrevious() const;
            [[nodiscard]] bool isAtEOF() const;
            [[nodiscard]] Token doAdvance();
            [[nodiscard]] bool matchToken(const Token& token, std::initializer_list<TokenType> types);
            void consumeToken(std::initializer_list<TokenType> types);

            std::shared_ptr<JsonValue> parseValue();

            std::shared_ptr<JsonValue> parseArray();
            std::shared_ptr<JsonValue> parseObject();
    };
}

#endif