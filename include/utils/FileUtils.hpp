#ifndef FILEUTILS_HPP
#define FILEUTILS_HPP

#include <string>

namespace toyjson::utils {
    [[nodiscard]] std::string readFile(const std::string& file_path_str);
}

#endif