add_library(hcasm-core
    Core/BinaryTransformer.cpp
    Core/Compiler.cpp
    Core/Parsers.cpp
    Core/StatementCompilers.cpp
    Core/Tokenizers.cpp
)
target_include_directories(hcasm-core PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(hcasm-core PUBLIC
    eternal::eternal
    spdlog::spdlog
    re2::re2
    argparse::argparse
    hcpu-common
)

add_executable(hcasm
  Main.cpp
)
target_link_libraries(hcasm PUBLIC
    hcasm-core
)
