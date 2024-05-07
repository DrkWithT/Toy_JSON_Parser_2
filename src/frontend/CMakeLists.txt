add_library(frontend "")

# TODO: add PRIVATE Parser.cpp to sources!
target_sources(frontend PRIVATE Token.cpp PRIVATE Lexer.cpp PRIVATE Parser.cpp)
