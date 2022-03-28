# DDLR
a distributed deep learning framework for robotics application

# Multi-thread processing

## Basic thread initialization

```
std::thread obj(func);
obj.join();
```

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
[1]: [CMake Linking Error pthread](https://cprieto.com/posts/2021/03/cmake-and-threads.html)

[2]: [Cmake and Threads](https://cprieto.com/posts/2021/03/cmake-and-threads.html)

### basic thread initialization

#### func

```
std::thread obj(func);
obj.join();
```

#### class

```
std::thread 
```

#### lamda expression


