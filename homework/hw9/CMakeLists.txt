cmake_minimum_required(VERSION 3.30)
project(hw9)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(hw9
    hw09.cpp
    polynomial.cpp
    polynomial.h)
