# Data Structures and Algorithms in C++

This is a joint project with [terra](https://github.com/terra2o), implementing
some data structures and algorithms in C++.

## Prerequisites

1. GNUMake (3.81+)
2. CMake (3.31+)
3. Ninja (1.11.1+)
4. Clang (17+) or GCC (14+)

## Usage

Because this library relies on C++23 Modules (`.cppm`), it is distributed via
source-level integration to ensure Built Module Interface (BMI) compiler
compatibility. Add the following to your `CMakeLists.txt`:
```cmake
include(FetchContent)
FetchContent_Declare(
    dsa-cpp
    GIT_REPOSITORY https://github.com/jayshozie/dsa-cpp.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(dsa-cpp)

# Link to your target
target_link_libraries(YourProject PRIVATE dsa-cpp)
target_compile_features(YourProject PRIVATE cxx_std_23)
```

In your C++ source files, import the data structures you need:
```cpp
import dsa.linear.DynamicArray;

int main()
{
    dsa::DynamicArray<int> arr;
    arr.pushBack(42);
    return 0;
}
```

## Local Development

To clone and build the library locally (defaults to release build):
```bash
~/ $ git clone git@github.com:jayshozie/dsa-cpp
~/ $ cd dsa-cpp
~/dsa-cpp $ make
~/dsa-cpp $ make test # run the internal test suite
```

## License

This project is licensed under [GNU General Public License v3](./LICENSE).
