cmake_minimum_required(VERSION 3.29)
project(MultiGumballMachine)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(MultiGumballMachine main.cpp
        Machine/CMultiGumballMachine.h
        CommandHandler.h
        Menu.h
        Machine/CNaiveMultiGumballMachine.h)

add_executable(${PROJECT_NAME}_test
        test/main.cpp
        test/MultiGumballMachineTest.cpp
        test/NaiveMultiGumballMachineTest.cpp
        test/StatesTest.cpp
)

target_link_libraries(${PROJECT_NAME}_test gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)