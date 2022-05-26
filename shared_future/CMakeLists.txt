cmake_minimum_required(VERSION 3.0.0)
project(shared_future VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
find_package(Threads REQUIRED)
include(CTest)
enable_testing()

add_executable(future_status src/future_status.cpp)
target_link_libraries(future_status Threads::Threads)

add_executable(shared_future src/shared_future.cpp)
target_link_libraries(shared_future Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
