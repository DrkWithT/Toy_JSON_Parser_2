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

namespace toyjson::utils {
    [[nodiscard]] std::string readFile(std::string_view file_path_sv) {
        std::ifstream reader {file_path_sv};

        reader.seekg(std::ios::end);
        size_t length = reader.tellg();
        reader.seekg(std::ios::beg);

        auto buffer = std::make_unique<char[]>(length + 1);
        std::fill(buffer.get(), buffer.get() + length, '\0');

        if (reader.read(buffer.get(), length).good())
            return std::string {buffer.get()};

        return std::string {};
    }
}