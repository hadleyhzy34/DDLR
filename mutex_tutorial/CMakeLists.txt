cmake_minimum_required(VERSION 3.0.0)
project(sharing_thread VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
include(CTest)
enable_testing()

add_executable(mutex_basics src/mutex_basics.cpp)
target_link_libraries(mutex_basics Threads::Threads)

add_executable(mutex_guard src/mutex_lock_guard.cpp)
target_link_libraries(mutex_guard Threads::Threads)

add_executable(mutex_deadlock src/mutex_deadlock.cpp)
target_link_libraries(mutex_deadlock Threads::Threads)

add_executable(mutex_solve src/mutex_solve.cpp)
target_link_libraries(mutex_solve Threads::Threads)

add_executable(mutex_adapt src/mutex_adapt.cpp)
target_link_libraries(mutex_adapt Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
