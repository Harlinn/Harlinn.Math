add_executable(HarlinnMathTests
    test_math.cpp
    ConstexprMathTests.cpp
    LineTests.cpp
    MathMatrixTests.cpp
    MathTests.cpp
    MathScalarCoverageTests.cpp
    MathVector2DoubleTests.cpp
    MathVector2FloatTests.cpp
    MathVector3DoubleTests.cpp
    MathVector3FloatTests.cpp
    MathVector4DoubleTests.cpp
    MathVector4FloatTests.cpp
    QuaternionTests.cpp
    SegmentTests.cpp
    SIMDByteTests.cpp
    SIMDDoubleTests.cpp
    SIMDFloatTests.cpp
    SIMDInt32Tests.cpp
    SquareMatrix2FloatTests.cpp
    SquareMatrix3Tests.cpp
    SquareMatrix4FloatTests.cpp
    Transform3DTests.cpp
    TruncTests.cpp
)

target_link_libraries(HarlinnMathTests PRIVATE
    HarlinnMath
    Catch2::Catch2WithMain
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(HarlinnMathTests PRIVATE -mavx2 -mfma)
    if(MINGW)
        target_compile_options(HarlinnMathTests PRIVATE -mstackrealign)
    endif()
endif()

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(HarlinnMathTests)
