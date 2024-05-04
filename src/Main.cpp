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
    using MyBoolean = toyjson::data::BooleanField;
    using MyNumber = toyjson::data::NumberField;
    using MyWrapper = toyjson::data::AnyField;
    
    std::boolalpha(std::cout);

    MyBoolean foo {true};

    auto foo_boxed = foo.toBoxedValue();
    bool foo_value = std::any_cast<bool>(foo_boxed);

    if (!foo_value) {
        std::cerr << "Unexpected foo_value: " << foo_value << '\n';
        return 1;
    }

    MyNumber bar {42};
    MyWrapper wrapper_bar {bar};

    auto wrap_bar_boxed = wrapper_bar.unpackValue<MyNumber>();
    double bar_value = std::any_cast<double>(wrap_bar_boxed.toBoxedValue());

    if (bar_value != 42) {
        std::cerr << "Unexpected bar_value: " << bar_value << '\n';
        return 1;
    }

    std::cout << "OK\n";
}