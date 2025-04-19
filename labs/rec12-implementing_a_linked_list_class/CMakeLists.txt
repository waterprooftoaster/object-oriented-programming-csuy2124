cmake_minimum_required(VERSION 3.30)
project(rec12_implementing_a_linked_list_class)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(rec12_implementing_a_linked_list_class
    List.cpp
    List.h
    rec12.cpp)
