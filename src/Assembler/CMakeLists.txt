add_executable(hcasm
  Main.cpp
  Core/BinaryTransformer.cpp
  Core/Compiler.cpp
  Core/Parsers.cpp
  Core/StatementCompilers.cpp
  Core/Tokenizers.cpp
)
target_include_directories(hcasm PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(hcasm PUBLIC argparse::argparse eternal::eternal spdlog::spdlog)

