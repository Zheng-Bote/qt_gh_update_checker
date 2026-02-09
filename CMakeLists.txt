cmake_minimum_required(VERSION 3.23)

# cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
# cmake --build build --config Release -j$(nproc)
# sudo cmake --install build

project(qt_gh_update_checker
        VERSION 1.0.0
        DESCRIPTION "header-only C++23 Qt6 library and CLI tool for checking GitHub repository updates."
        HOMEPAGE_URL "https://github.com/Zheng-Bote/qt_gh_update_checker"
        LANGUAGES CXX)

cmake_minimum_required(VERSION 3.20)
project(qt_gh_update_checker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(Qt6 6.9 REQUIRED COMPONENTS Core Network)

# ---------------------------------------------------------
# Header-only library
# ---------------------------------------------------------
add_library(qt_gh_update_checker INTERFACE)

target_include_directories(qt_gh_update_checker INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(qt_gh_update_checker INTERFACE
    Qt6::Core
    Qt6::Network
)

# ---------------------------------------------------------
# CLI tool
# ---------------------------------------------------------
add_executable(qt_gh-update-checker src/cli_main.cpp)

target_link_libraries(qt_gh-update-checker
    qt_gh_update_checker
)

# ---------------------------------------------------------
# Installation: headers + library + CLI
# ---------------------------------------------------------
install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    TARGETS qt_gh_update_checker
    EXPORT qt_gh_update_checkerTargets
)

install(
    TARGETS qt_gh-update-checker
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    EXPORT qt_gh_update_checkerTargets
    FILE qt_gh_update_checkerTargets.cmake
    NAMESPACE qt_gh_update_checker::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qt_gh_update_checker
)

# ---------------------------------------------------------
# CMake package config
# ---------------------------------------------------------
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/qt_gh_update_checkerConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/qt_gh_update_checkerConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qt_gh_update_checker
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/qt_gh_update_checkerConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qt_gh_update_checker
)

# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------
enable_testing()

add_executable(test_basic tests/test_basic.cpp)

target_link_libraries(test_basic
    qt_gh_update_checker
)

add_test(NAME basic_update_check COMMAND test_basic)
