add_executable(HarlinnMathTests
    test_math.cpp
)

target_link_libraries(HarlinnMathTests PRIVATE
    HarlinnMath
    Catch2::Catch2WithMain
)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(HarlinnMathTests)
