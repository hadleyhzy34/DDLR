cmake_minimum_required(VERSION 3.0.0)
project(atomic VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
find_package(Threads REQUIRED)
include(CTest)
enable_testing()

add_executable(async src/async.cpp)
target_link_libraries(async Threads::Threads)

add_executable(async_1 src/async_1.cpp)
target_link_libraries(async_1 Threads::Threads)

add_executable(async_2 src/async_2.cpp)
target_link_libraries(async_2 Threads::Threads)

add_executable(future src/future.cpp)
target_link_libraries(future Threads::Threads)

add_executable(promise src/promise.cpp)
target_link_libraries(promise Threads::Threads)

add_executable(packaged_task src/packaged_task.cpp)
target_link_libraries(packaged_task Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
