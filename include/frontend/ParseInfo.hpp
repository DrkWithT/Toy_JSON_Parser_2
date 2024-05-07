#ifndef PARSE_INFO
#define PARSE_INFO

#include <string_view>

namespace toyjson::frontend {
    enum class ParseStatus {
        err_none,
        err_unknown_token,
        err_misplaced_token,
        err_general
    };

    [[nodiscard]] constexpr std::string_view toErrorName(ParseStatus status) {
        using std::operator""sv;

        if (status == ParseStatus::err_unknown_token)
            return "Unknown token error"sv;
        else if (status == ParseStatus::err_misplaced_token)
            return "Misplaced token error"sv;
        else if (status == ParseStatus::err_general)
            return "General error"sv;

        return "OK"sv;
    }
}

#endif