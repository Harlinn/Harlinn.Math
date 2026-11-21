cmake_minimum_required(VERSION 3.25)

project(HarlinnMath
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "Header-only math library for the Harlinn ecosystem"
)

option(HARLINN_MATH_CXX26 "Require C++26 instead of C++23" OFF)

if(HARLINN_MATH_CXX26)
    set(HARLINN_MATH_CXX_STANDARD 26)
else()
    set(HARLINN_MATH_CXX_STANDARD 23)
endif()

# ── Library target ───────────────────────────────────────────────
add_library(HarlinnMath INTERFACE)
add_library(Harlinn::Math ALIAS HarlinnMath)

target_include_directories(HarlinnMath INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(HarlinnMath INTERFACE cxx_std_${HARLINN_MATH_CXX_STANDARD})

# ── Dependencies ─────────────────────────────────────────────────
include(cmake/Dependencies.cmake)

# ── Tests ────────────────────────────────────────────────────────
include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

# ── Examples ─────────────────────────────────────────────────────
option(BUILD_EXAMPLES "Build example targets" OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ── Benchmarks ───────────────────────────────────────────────────
option(BUILD_BENCHMARKS "Build benchmark targets" OFF)
if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

# ── Install & Export ─────────────────────────────────────────────
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS HarlinnMath EXPORT HarlinnMathTargets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT HarlinnMathTargets
    FILE        HarlinnMathTargets.cmake
    NAMESPACE   Harlinn::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HarlinnMath
)

configure_package_config_file(
    cmake/HarlinnMathConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/HarlinnMathConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HarlinnMath
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/HarlinnMathConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/HarlinnMathConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/HarlinnMathConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HarlinnMath
)
