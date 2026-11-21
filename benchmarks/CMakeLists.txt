add_executable(HarlinnMathBenchmarks
    bench_example.cpp
)

target_link_libraries(HarlinnMathBenchmarks PRIVATE
    HarlinnMath
    benchmark::benchmark
    benchmark::benchmark_main
)
