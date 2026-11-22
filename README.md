# Harlinn.Math

A C++ math library.

## About

Harlinn.Math depends on [Harlinn.Common](https://github.com/Harlinn/Harlinn.Common).

Harlinn.Math, [Harlinn.System](https://github.com/Harlinn/Harlinn.System), 
and [Harlinn.Common](https://github.com/Harlinn/Harlinn.Common) are based on 
code that was originally published as part of the Windows-only [Harlinn.Windows](https://github.com/Harlinn/Harlinn.Windows) repository.

The project is in its early stages. `Harlinn.Common` currently compiles 
for all target platforms, but `Harlinn.Math` currently builds only on Windows.

My plan is to support the latest Windows, Linux, and macOS versions available on GitHub-hosted runners.

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

