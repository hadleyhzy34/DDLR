cmake_minimum_required(VERSION 3.0.0)
project(atomic VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
find_package(Threads REQUIRED)
include(CTest)
enable_testing()

add_executable(atomic src/atomic.cpp)
target_link_libraries(atomic Threads::Threads)

add_executable(atomic_example src/atomic_example.cpp)
target_link_libraries(atomic_example Threads::Threads)

add_executable(atomic_example1 src/atomic_example1.cpp)
target_link_libraries(atomic_example1 Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
