# SimpleLog - A Minimal C++ Logging Library

![License](https://img.shields.io/badge/License-MIT-blue.svg)
![C++](https://img.shields.io/badge/C++-17+-brightgreen.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS%20%7C%20Arm-lightgrey.svg)
![Build](https://img.shields.io/badge/Build-CMake-success.svg)

## Features

- 🚀 **Library-header** with optional compiled library version
- 🎨 **Colored console output** (ERROR/WARN/INFO levels)
- ⏱️ **Precise timestamps** with millisecond resolution
- 🔒 **Thread-safe** logging with mutex protection
- 🌍 **Cross-platform** (Windows, Linux, macOS, Arm)
- 🏗️ **Modern C++17** implementation
- 📦 **CMake support** for easy integration

## Result
<img src=".git\simplelog\test.png" alt="SimpleLog Screenshot" width="600"/>

## Quick Start

### How Usage ? 
> After building the library, you can use it in your project like this:
```bash
./build/bin/logtest
```

```cpp
#include "simplelog.hpp"

int main() {
    LOG_INFO("Application started");
    LOG_WARN("Low memory detected: ", 1024, "MB available");
    LOG_ERROR("Failed to open file: ", "data.txt");
    return 0;
}
```

### Get Library
#### 1. **Download and extract**:

#### 2.Library Build
```bash
git clone https://github.com/Jin-OK/cpplog-simple.git
cd cpplog-simple
mkdir build && cd build
cmake .. 
cmake --build . --config Release
cmake --install .
```

2. **Use in your project**:
```cmake
find_package(simplelog REQUIRED)
target_link_libraries(your_target PRIVATE simplelog::simplelog)
```

## API Reference

### Logging Macros
| Macro | Description |
|-------|-------------|
| `LOG_INFO(...)` | Informational message (green) |
| `LOG_WARN(...)` | Warning message (yellow) |
| `LOG_ERROR(...)` | Error message (red) |


## Platform Support

| Platform | Tested | Notes |
|----------|--------|-------|
| Windows  | ✔️ | MSVC/MinGW |
| Linux    | ✔️ | GCC/Clang |
| macOS    | ✔️ | Clang |
| Arm      | ✔️ | Raspberry Pi Orange Pi |

## About the Author

I'm a hobbyist C++ developer who created this library to learn modern C++ concepts. SimpleLog represents my journey in understanding:

- PIMPL pattern
- CMake build systems
- Cross-platform development
- Thread safety
- Template metaprogramming

Feedback and contributions are welcome!

## License

MIT License - See [LICENSE](LICENSE) for details.

