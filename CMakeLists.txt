cmake_minimum_required(VERSION 3.16)

project(ToyJSONParser2 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DEBUG_MODE OFF CACHE BOOL "Compile with debug symbols")

if (DEBUG_MODE)
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -g -Og)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -O2)
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_HOME_DIRECTORY}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/build")

# enable_testing()
include_directories("${CMAKE_HOME_DIRECTORY}/include")
add_subdirectory(src)
# add_subdirectory(unit_tests)
