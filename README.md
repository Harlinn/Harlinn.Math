# Harlinn.Math

A header-only C++ math library.

## About

Harlinn.Math depends on [Harlinn.Common](https://github.com/Harlinn/Harlinn.Common).
Both projects are based on code originally published in the Windows-only
[Harlinn.Windows](https://github.com/Harlinn/Harlinn.Windows) repository.

The project is in its early stages. Currently, only x64 builds are supported;
ARM64 and macOS support are planned. CI covers Windows with MSVC, MSYS2
CLANG64 Clang and MSYS2 UCRT64 GCC, and Ubuntu with GCC and Clang matrix jobs.
Each Ubuntu job installs and selects the newest versioned compiler available
from the runner's configured apt repositories. For local builds, select the
intended compiler explicitly as shown below.

## Numerical behavior

- Three-dimensional `AngleBetween` and `ScalarAngleBetween` accept non-unit
  vectors and return radians. A zero or nonfinite vector yields NaN.
- Real-scalar subtraction and division with a quaternion follow quaternion
  algebra: `s - q` negates the vector part, and `s / q` multiplies the
  quaternion inverse by `s`. This replaces the earlier componentwise division.
  Division by a zero or nonfinite quaternion, or with a nonfinite scalar,
  returns NaN components.
- Quaternion `Slerp` takes unit quaternions and chooses the shortest rotation
  arc, so its endpoint may be the negation of the supplied second quaternion.

## Prerequisites

- A C++23 compiler and standard library, CMake 3.25 or newer, Ninja, and Git.
- An x64 machine with AVX2 and FMA support for the SIMD tests.
- Network access for CMake to fetch Harlinn.Common and Catch2 on first configure.
  Harlinn.Common is fetched from its `main` branch and Catch2 from `v3.7.1`.

The default preset configures a Debug build with tests enabled in `build/default`.
CMake caches the compiler in the build directory: use a separate build directory
for each compiler or configuration, rather than switching compilers in an
existing directory.

## Windows

### MSVC

Install Visual Studio with the C++ desktop development workload, CMake, and Ninja.
From an **x64 Native Tools Command Prompt**, in the repository root:

```bat
cmake --preset msvc
cmake --build build\msvc
ctest --test-dir build\msvc --output-on-failure
```

### MSYS2 GCC and Clang

Install [MSYS2](https://www.msys2.org/) and open the shell corresponding to the
compiler. Use UCRT64 for GCC or CLANG64 for Clang; these environments have
separate toolchains and C++ libraries.

In the **MSYS2 UCRT64** shell, install the tools and build with GCC:

```sh
pacman -S --needed git mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
CC=gcc CXX=g++ cmake --preset default
cmake --build --preset default
ctest --preset default
```

In the **MSYS2 CLANG64** shell, install the tools and build with Clang:

```sh
pacman -S --needed git mingw-w64-clang-x86_64-clang mingw-w64-clang-x86_64-cmake mingw-w64-clang-x86_64-ninja
CC=clang CXX=clang++ cmake --preset default
cmake --build --preset default
ctest --preset default
```

Both examples use `build/default`; use separate build directories if building
with both compilers. MSYS2 Clang with libc++ requires a Harlinn.Common checkout
that provides the `ConstantRange` fallback when `std::ranges::constant_range`
is unavailable. If necessary, use the local checkout option below with an
updated Harlinn.Common checkout.

## Linux

On Ubuntu, install the build tools:

```sh
sudo apt update
sudo apt install git cmake ninja-build g++ clang
```

From the repository root, configure, build, and run tests with GCC:

```sh
CC=gcc CXX=g++ cmake -S . -B build/linux-gcc -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/linux-gcc
ctest --test-dir build/linux-gcc --output-on-failure
```

For Clang, use a separate build directory:

```sh
CC=clang CXX=clang++ cmake -S . -B build/linux-clang -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/linux-clang
ctest --test-dir build/linux-clang --output-on-failure
```

Ubuntu GCC 14.2 and Clang 20.1 have been tested locally. Other compiler and
standard-library versions may have different C++23 support.

## Local Harlinn.Common checkout

To use a sibling `Harlinn.Common` checkout instead of fetching it:

```sh
cmake --preset local-dev
cmake --build build/local-dev
ctest --test-dir build/local-dev --output-on-failure
```

For a checkout elsewhere, pass `-DHARLINN_COMMON_SOURCE_DIR=<path>` when
configuring a build directory. Catch2 is still fetched when tests are enabled.

