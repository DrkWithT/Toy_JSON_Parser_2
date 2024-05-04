#ifndef FILEUTILS_HPP
#define FILEUTILS_HPP

#include <string>
#include <string_view>

namespace toyjson::utils {
    [[nodiscard]] std::string readFile(std::string_view file_path_sv);
}

#endif