# CLI

Library for creating command-line applications in C++.

# Prerequisites&nbsp;:vertical_traffic_light:

- [Git][git]
- [CMake][cmake]
- C++ compiler
    - Windows: [MSVC][msvc] (Bundled with [Visual Studio][msvs])
    - MacOS: [Clang][clang] (Bundled with [Xcode][xcode])
    - Linux: [GCC][gcc]

# Getting started&nbsp;:runner:

This example will use the following project structure

```
:project/
├─ CMakeLists.tsx
├─ lib/
│  ├─ cli/
├─ src/
│  ├─ main.cpp
```

### 1. Clone the library source code

```bash
cd ./lib
git clone https://github.com/taardal/cli
```

### 2. Add the library to the CMake project

```cmake
# ./CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(cli-app)

add_executable(${PROJECT_NAME} src/main.cpp)

set(CLI_DIR lib/cli)
add_subdirectory(${CLI_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${CLI_DIR}/include)
target_link_libraries(${PROJECT_NAME} cli)
```

### 3. Create the app 

```cpp
// ./src/main.cpp

#include <cli.h>
#include <iostream>

int main(int argc, char* argv[]) {
    CLI::Command helloCommand;
    helloCommand.Name = "hello";
    helloCommand.Usage = "Say hello";
    helloCommand.Action = [](const CLI::Context& context) -> void {
        std::cout << "Hello World";   
    };
    CLI::App app;
    app.Name = "app";
    app.Usage = "CLI App";
    app.Commands = {
        helloCommand
    };
    app.Run(argc, argv);
    return 0;
}
```

### 4. Build the app binary

```bash
# Generate project files to "build" folder
cmake -S . -B build

# Build binary using generated files
cmake --build build
```

### 4. Run the app

```bash
./build/cli-app
```

Output:
```
NAME:
    app - CLI App

USAGE:
    app [global options] command [command options] [arguments...]

COMMANDS:
    hello      Say hello
    help, h    Show available commands and options

GLOBAL OPTIONS:
    --help, -h    Show help
```


[clang]: http://clang.org/
[cmake]: https://cmake.org/
[gcc]: https://gcc.gnu.org/
[git]: https://git-scm.com
[msvc]: https://visualstudio.microsoft.com/vs/features/cplusplus/
[msvs]: https://visualstudio.microsoft.com/
[xcode]: https://developer.apple.com/xcode/