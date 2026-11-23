# Harlinn.Math

A C++ math library.

## About

Harlinn.Math depends on [Harlinn.Common](https://github.com/Harlinn/Harlinn.Common).

Harlinn.Math and [Harlinn.Common](https://github.com/Harlinn/Harlinn.Common) are based on 
code that was originally published as part of my Windows-only [Harlinn.Windows](https://github.com/Harlinn/Harlinn.Windows) repository.

The project is in its early stages. 

`Harlinn.Common` currently compiles for all target platforms.

Tests compiles using MSVC, Clang, and GCC on Windows, but still needs some work before they succeed.

So far only x64 builds are supported, but I plan to support ARM64 as well.

My plan is to support the latest Windows, Linux, and MacOS versions.

## Build

To build:

```
cmake --preset default
cmake --build --preset default
ctest --preset default
```

For local development with sibling repositories:

```
cmake --preset local-dev
```

MSYS2 Clang with libc++ requires a Harlinn.Common checkout that provides the
`ConstantRange` fallback when `std::ranges::constant_range` is unavailable. Use
`local-dev` with an updated sibling checkout until that fix is available in the
fetched dependency.

