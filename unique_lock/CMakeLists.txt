cmake_minimum_required(VERSION 3.0.0)
project(sharing_thread VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)
find_package(Threads REQUIRED)
include(CTest)
enable_testing()

add_executable(unique_lock src/unique_lock.cpp)
target_link_libraries(unique_lock Threads::Threads)

add_executable(try_lock src/try_lock.cpp)
target_link_libraries(try_lock Threads::Threads)

add_executable(owns_lock src/owns_lock.cpp)
target_link_libraries(owns_lock Threads::Threads)

add_executable(defer_lock src/defer_lock.cpp)
target_link_libraries(defer_lock Threads::Threads)

add_executable(release_lock src/release.cpp)
target_link_libraries(release_lock Threads::Threads)

add_executable(move_mutex src/move_mutex.cpp)
target_link_libraries(move_mutex Threads::Threads)

add_executable(rtn_mutex src/rtn_mutex.cpp)
target_link_libraries(rtn_mutex Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
