cmake_minimum_required(VERSION 3.10)
project(hw07_multifile LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)git
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hw07
        hw07.cpp
        Noble.cpp
        Warrior.cpp
)