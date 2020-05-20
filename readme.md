# Test
C++ test project template.

## Dependencies
See [qis/toolchains](https://github.com/qis/toolchains) for vcpkg setup instructions.

```sh
vcpkg install fmt tbb
```

## Usage
Open the directory as a CMake project in Visual Studio or use [makefile](makefile) commands.

* `make` to build (debug)
* `make run` to build and run (debug)
* `make install` to install into `build/install` (release)
* `make format` to format code with [clang-format](https://llvm.org/builds/)
* `make clean` to remove build files

Add `config=release` to build in release mode.
