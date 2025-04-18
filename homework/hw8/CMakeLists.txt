cmake_minimum_required(VERSION 3.30)
project(hw8)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(hw8
        Archer.cpp
        Archer.h
        hw08.cpp
        Lord.cpp
        Lord.h
        Noble.cpp
        Noble.h
        PersonWithStrengthToFight.cpp
        PersonWithStrengthToFight.h
        Protector.cpp
        Protector.h
        Swordsman.cpp
        Swordsman.h
        Warrior.cpp
        Warrior.h
        Wizard.cpp
        Wizard.h)
