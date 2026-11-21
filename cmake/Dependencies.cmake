include(FetchContent)

# ── Harlinn.Common ──────────────────────────────────────────────
set(HARLINN_COMMON_SOURCE_DIR "" CACHE PATH
    "Path to a local Harlinn.Common checkout (skip FetchContent)")

if(HARLINN_COMMON_SOURCE_DIR)
    if(NOT TARGET HarlinnCommon)
        add_subdirectory(
            "${HARLINN_COMMON_SOURCE_DIR}"
            "${CMAKE_BINARY_DIR}/_local/HarlinnCommon"
        )
    endif()
else()
    if(NOT TARGET HarlinnCommon)
        FetchContent_Declare(HarlinnCommon
            GIT_REPOSITORY https://github.com/Harlinn/Harlinn.Common.git
            GIT_TAG        main
        )
        FetchContent_MakeAvailable(HarlinnCommon)
    endif()
endif()

target_link_libraries(HarlinnMath INTERFACE HarlinnCommon)

# ── Catch2 (tests only) ─────────────────────────────────────────
if(BUILD_TESTING)
    if(NOT TARGET Catch2::Catch2WithMain)
        FetchContent_Declare(Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v3.7.1
        )
        FetchContent_MakeAvailable(Catch2)
    endif()
endif()

# ── Google Benchmark (benchmarks only) ───────────────────────────
if(BUILD_BENCHMARKS)
    if(NOT TARGET benchmark::benchmark)
        FetchContent_Declare(googlebenchmark
            GIT_REPOSITORY https://github.com/google/benchmark.git
            GIT_TAG        v1.9.1
        )
        set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googlebenchmark)
    endif()
endif()
