cmake_minimum_required(VERSION 3.5)
project(StateServer)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)

add_executable(StateServer main.cpp includes/ConnectionServer.h ConnectionServer.cpp includes/StateServer.h StateServer.cpp)
target_link_libraries (StateServer ${CMAKE_THREAD_LIBS_INIT} rt)