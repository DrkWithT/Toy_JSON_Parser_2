add_library(frontend "")

# TODO: add PRIVATE ToyJsonParser.cpp to sources!
target_sources(frontend PRIVATE ToyJsonToken.cpp PRIVATE ToyJsonLexer.cpp)
