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
#include "utils/FileUtils.hpp"
#include "data/Value.hpp"
#include "frontend/Parser.hpp"

int main() {
    using MyJsonAny = toyjson::data::AnyField;
    using MyJsonObj = toyjson::data::ObjectField;
    using MyParser = toyjson::frontend::Parser;

    const char* name = "./tests/test_flat.json";
    
    auto flat_content = toyjson::utils::readFile(name);

    MyParser parser {flat_content};

    auto result = parser.parseToADT(name);
    auto result_root = result.getRoot()->toBoxedValue();
    MyJsonAny root_wrapper = std::any_cast<MyJsonAny>(result_root);
    MyJsonObj root_obj = root_wrapper.unpackValue<MyJsonObj>();

    if (root_obj.isEmpty()) {
        std::cerr << "Result unexpectedly empty!\n";
        return 1;
    }

    if (root_obj.getPropertyCount() != 6) {
        std::cerr << "Unexpected property count of result!\n";
        return 1;
    }

    if (!root_obj.hasProperty("age")) {
        std::cerr << "Result missing age property!\n";
        return 1;
    }
}