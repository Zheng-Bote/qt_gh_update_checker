cmake_minimum_required(VERSION 3.23)

project(qt_gh_update_checker
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

# Header-only library
add_library(qt_gh_update_checker INTERFACE)
target_include_directories(qt_gh_update_checker INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(qt_gh_update_checker INTERFACE
    Qt6::Core
    Qt6::Network
)

# CLI tool
add_executable(qt_gh-update-checker src/cli_main.cpp)
target_link_libraries(qt_gh-update-checker
    qt_gh_update_checker
)

# Tests
enable_testing()

add_executable(test_basic tests/test_basic.cpp)
target_link_libraries(test_basic
    qt_gh_update_checker
)
add_test(NAME basic_update_check COMMAND test_basic)
