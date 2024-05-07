add_executable(toyjson Main.cpp)

add_subdirectory(utils)
add_subdirectory(data)
add_subdirectory(frontend)

target_link_libraries(toyjson PRIVATE utils PRIVATE data PRIVATE frontend)
