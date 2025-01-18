# Developer notes

## CMake

The project has been initialized with a [CMakeLists.txt](CMakeLists.txt)-based
configuration for building with CMake:

```console
# create the build directory and change into it
$ mkdir build && cd build

# generate the build files
$ cmake ..

# build the project
$ cmake --build .

# install the project to <repo>/build/cmake/dist
$ cmake --install .

# library also installs documentation as man pages
$ man -l ./dist/share/man/man3/boxmuller_randn.3
```

The CMake variables `BOXMULLER_BUILD_TESTS` and `BOXMULLER_BUILD_EXAMPLES` can be used to build the
tests and examples, respectively. By default they are built when this project is the top
project; when boxmuller is used as a dependency of a different project, the default is to build
neither the tests nor the examples, but each can be turned on by setting the beforementioned
variables. e.g like so:

```
cmake -DBOXMULLER_BUILD_TESTING=ON -DBOXMULLER_BUILD_EXAMPLES=ON ..
```

## Testing

Building and running the tests require that [Criterion](https://github.com/Snaipe/Criterion) is installed on the system, e.g. with

```console
$ sudo apt install libcriterion-dev
```

Run the tests with

```console
$ ./dist/bin/test_boxmuller -j1 --verbose
```

Or simply,

```console
$ ctest
```

## `clang-format`

The file `.clang-format` contains an initial configuration for (automatic) formatting with [clang-format](https://clang.llvm.org/docs/ClangFormat.html). Run the formatter with e.g.:

```console
# dry run on main.c
$ clang-format -Werror --dry-run main.c

# format in place all *.c and *.h files under ./src
$ clang-format -i `find ./src -type f -name '*.[c|h]'`
```
