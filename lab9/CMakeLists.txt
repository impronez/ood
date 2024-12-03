cmake_minimum_required(VERSION 3.29)
project(lab9)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(lab9 main.cpp
        CoW.h
        Drawer/Drawer.h
        Image/Image.h
        Geom.h
        Tile/Tile.h
        Image/ImageService.h)

add_executable(${PROJECT_NAME}_test
        test/main.cpp)

target_link_libraries(${PROJECT_NAME}_test gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
