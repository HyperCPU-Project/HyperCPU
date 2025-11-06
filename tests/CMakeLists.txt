add_library(fixtures INTERFACE)
target_include_directories(fixtures INTERFACE ${PROJECT_SOURCE_DIR}/tests)
target_precompile_headers(fixtures INTERFACE fixtures.hpp gtest.hpp)

add_subdirectory(Integration)
add_subdirectory(Modular)

if (DEFINED INSTALL_TESTS)
    install(
        TARGETS
            integration-tests
            modular-tests
        DESTINATION
            opt/hcpu/tests
    )
endif()