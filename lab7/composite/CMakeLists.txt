cmake_minimum_required(VERSION 3.29)
project(composite)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(composite main.cpp
        Canvas/ICanvas.h
        CommonTypes.h
        Shape/CShape.h
        Style/CStyle.h
        Shape/CTriangle.h
        Shape/CRectangle.h
        Shape/CEllipse.h
        Slide/CSlide.h
        CommandHandler.h
        CMenu.h
)

add_executable(${PROJECT_NAME}_test
        test/main.cpp
        Canvas/SVGCanvas.h
        Group/CShapeGroup.h
        Shape/IShape.h
        Style/IStyle.h
        Group/IShapeGroup.h
        Slide/ISlide.h
        Shape/IShapes.h
        Factory/CShapeFactory.h
        Factory/IShapeFactory.h
        test/ShapeGroupTest.cpp
)

target_link_libraries(${PROJECT_NAME}_test gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)