cmake_minimum_required(VERSION 3.0.0)
project(sharing_thread VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
include(CTest)
enable_testing()

add_executable(sharing_thread src/main.cpp)
target_link_libraries(sharing_thread Threads::Threads)

add_executable(stack_lock src/main2.cpp)
target_link_libraries(stack_lock Threads::Threads)

add_executable(multiple_locks src/main4.cpp)
target_link_libraries(multiple_locks Threads::Threads)

add_executable(read_write_mutex src/main5.cpp)
target_link_libraries(read_write_mutex Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
