cmake_minimum_required(VERSION 3.28)
project(HyperCPU VERSION 0.5.0 LANGUAGES CXX)

include(CheckIPOSupported)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(argparse REQUIRED)
find_package(eternal REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(re2 REQUIRED)
add_subdirectory(foreign/HPool)
include_directories(foreign/HPool)

check_ipo_supported(RESULT SUPPORTED OUTPUT ERR)

string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)

# TODO: Enable UBSan and fix all errors
if ("${CMAKE_BUILD_TYPE}" STREQUAL "debug")
    message(STATUS "Enabled debug flags")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "release")
    message(STATUS "Enabled release flags")

    if (SUPPORTED)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif ()
endif()

add_subdirectory(src)
add_subdirectory(tests)
