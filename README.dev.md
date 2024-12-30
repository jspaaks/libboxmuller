# Developer notes

## CMake

The project has been initialized with a [CMakeLists.txt](CMakeLists.txt)-based
configuration for building with CMake:

```console
# change into the build directory
$ cd build/cmake

# generate the build files
$ cmake ../..

# build the project
$ cmake --build .

# install the project to <repo>/build/cmake/dist
$ cmake --install .

# run programs to see what they do, e.g.
$ ./dist/bin/linear-regression-ssr-bgd-artificial

# matrix library also installs documentation as man pages
$ man -l ./dist/share/man/man3/matrix.3
```


## Testing

Building and running the tests require that [Criterion](https://github.com/Snaipe/Criterion) is installed on the system, e.g. with

```console
$ sudo apt install libcriterion-dev
```

Run the tests with

```console
$ ./dist/bin/test_boxmuller -j1 --verbose
$ ./dist/bin/test_matrix -j1 --verbose
```

## `clang-format`

The file `.clang-format` contains an initial configuration for (automatic) formatting with [clang-format](https://clang.llvm.org/docs/ClangFormat.html). Run the formatter with e.g.:

```console
# dry run on main.c
$ clang-format -Werror --dry-run main.c

# format in place all *.c and *.h files under ./src
$ clang-format -i `find ./src -type f -name '*.[c|h]'`
```

## TODO

1. add gradient check https://www.youtube.com/watch?v=h7iBpEHGVNc&t=3503s as a unit test
1. add minibatching https://www.youtube.com/watch?v=h7iBpEHGVNc&t=3776s
1. add multistart
1. consider making the test binaries startable from ctest: https://cmake.org/cmake/help/v3.28/command/add_test.html