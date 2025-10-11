add_library(pog-hpp INTERFACE)
target_include_directories(pog-hpp INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_precompile_headers(pog-hpp INTERFACE Pog.hpp)
