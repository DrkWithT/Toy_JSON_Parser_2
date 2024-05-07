cmake_minimum_required(VERSION 3.16)

project(ToyJSONParser2 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(DEBUG_MODE TRUE)

if (DEBUG_MODE)
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -g -O0)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -O2)
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_HOME_DIRECTORY}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/build")

# enable_testing()
include_directories("${CMAKE_HOME_DIRECTORY}/include")
add_subdirectory(src)
# add_subdirectory(unit_tests)
