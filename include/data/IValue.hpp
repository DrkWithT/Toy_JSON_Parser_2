#ifndef IVALUE_HPP
#define IVALUE_HPP

#include <any>

namespace toyjson::data {

    enum class JsonType {
        j_null,
        j_boolean,
        j_number,
        j_string,
        j_array,
        j_object,
        j_any
    };

    class IJsonValue {
    public:
        virtual ~IJsonValue() = default;

        [[nodiscard]] virtual JsonType getType() const = 0;
        [[nodiscard]] virtual std::any toBoxedValue() const = 0;
    };
}

#endif