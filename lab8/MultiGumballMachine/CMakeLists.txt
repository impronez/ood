cmake_minimum_required(VERSION 3.29)
project(MultiGumballMachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(MultiGumballMachine main.cpp
        Machine/CMultiGumballMachine.h)
