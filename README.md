# DDLR
a distributed deep learning framework for robotics application

# Multi-thread processing

## C++ Threads compilation using CMAKE
```
cmake_minimum_required(VERSION 3.15)
project(hello)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(hello main.cpp)
target_link_libraries(hello Threads::Threads)
```

### Reference:
[1]: https://stackoverflow.com/questions/30734136/cmake-linking-error-pthread-enable-multithreading-to-use-stdthread-operation: "CMake Linking Error pthread"
[1]: https://cprieto.com/posts/2021/03/cmake-and-threads.html "Cmake and Threads"

