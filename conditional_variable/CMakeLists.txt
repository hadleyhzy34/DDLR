cmake_minimum_required(VERSION 3.0.0)
project(conditional_variable VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
find_package(Threads REQUIRED)
include(CTest)
enable_testing()

add_executable(condition_variable src/condition_variable.cpp)
target_link_libraries(condition_variable Threads::Threads)

add_executable(notify_all src/notify_all.cpp)
target_link_libraries(notify_all Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
