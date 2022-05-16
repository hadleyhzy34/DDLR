cmake_minimum_required(VERSION 3.0.0)
project(sharing_thread VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
find_package(Threads REQUIRED)
include(CTest)
enable_testing()

add_executable(singleton_mode src/singleton.cpp)
target_link_libraries(singleton_mode Threads::Threads)

add_executable(singleton_thread src/singleton_thread.cpp)
target_link_libraries(singleton_thread Threads::Threads)

add_executable(call_once_thread src/call_once_thread.cpp)
target_link_libraries(call_once_thread Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
