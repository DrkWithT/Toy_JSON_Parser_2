/**
 * @file FileUtils.cpp
 * @author DrkWithT
 * @brief Implements file utilities.
 * @date 2024-05-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <algorithm>
#include <memory>
#include <fstream>
#include "utils/FileUtils.hpp"

namespace toyjson::utils {
    [[nodiscard]] std::string readFile(const std::string& file_path_str) {
        std::ifstream reader {file_path_str};

        reader.seekg(0, reader.end);
        size_t length = reader.tellg();
        reader.seekg(0, reader.beg);

        auto buffer = std::make_unique<char[]>(length + 1);
        std::fill(buffer.get(), buffer.get() + length, '\0');

        if (reader.read(buffer.get(), length).good())
            return std::string {buffer.get()};

        return std::string {};
    }
}