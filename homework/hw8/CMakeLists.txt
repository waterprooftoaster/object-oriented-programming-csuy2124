cmake_minimum_required(VERSION 3.10)
project(hw08 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hw07
        hw08.cpp
        Noble.cpp
        Warrior.cpp
        Lord.cpp
        PersonWithStrengthToFight.cpp
        Swordsman.cpp
        Wizard.cpp
        Archer.cpp
)