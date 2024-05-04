/**
 * @file Main.cpp
 * @author DrkWithT
 * @brief Entry point of testing program.
 * @date 2024-05-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <any>
#include <iostream>
#include "data/Value.hpp"

int main() {
    using JsonNull = toyjson::data::NullField;
    using JsonBoolean = toyjson::data::BooleanField;
    using JsonNumber = toyjson::data::NumberField;
    using JsonString = toyjson::data::StringField;
    using JsonArray = toyjson::data::ArrayField;
    using JsonObject = toyjson::data::ObjectField;

    JsonNull v_null {};
    JsonBoolean v_bool {true};
    JsonNumber v_num {69.0};
    JsonString v_str {"Hello"};
    JsonArray v_array {};
    JsonObject v_obj {};

    auto a_null = v_null.toBoxedValue();

    if (a_null.has_value()) {
        std::cerr << "Unexpected value from v_null\n";
        return 1;
    }

    auto a_bool = v_bool.toBoxedValue();
    auto raw_bool = std::any_cast<bool>(a_bool);

    if (!raw_bool) {
        std::cerr << "Unexpected false from v_bool\n";
        return 1;
    }

    auto a_num = v_num.toBoxedValue();
    auto raw_double = std::any_cast<double>(a_num);

    if (raw_double != 69.0) {
        std::cerr << "Unexpected value from v_double\n";
        return 1;
    }

    auto a_str = v_str.toBoxedValue();
    auto raw_string = std::any_cast<std::string>(a_str);

    if (raw_string != "Hello") {
        std::cerr << "Unexpected value from v_str\n";
        return 1;
    }

    auto v_arr_empty = v_array.isEmpty();

    if (!v_arr_empty) {
        std::cerr << "Unexpected array size from v_arr\n";
        return 1;
    }

    auto v_obj_empty = v_obj.isEmpty();

    if(!v_obj_empty) {
        std::cerr << "Unexpected object size from v_obj\n";
        return 1;
    }

    auto v_obj_dud_found = v_obj.hasProperty("foo");

    if (v_obj_dud_found) {
        std::cerr << "Unexpected result from v_obj.hasProperty()\n";
        return 1;
    }
}