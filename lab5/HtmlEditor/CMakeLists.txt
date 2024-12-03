cmake_minimum_required(VERSION 3.29)
project(HTMLEditor)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(HTMLEditor main.cpp
        Document/IDocument.h
        Document/Paragraph/IParagraph.h
        Document/Image/IImage.h
        Document/CDocumentItem.h
        Document/CConstDocumentITem.h
        Document/Command/ICommand.h
        Document/Command/InsertParagraphCommand.h
        Document/CDocument.h
        Document/History/History.h
        Document/Image/CImage.h
        Document/Paragraph/CParagraph.h
        Document/Command/CCommand.h
        Menu/Menu.h
        CommandHandler/CommandHandler.h
        Document/Command/DeleteItemCommand.h
        Document/Command/InsertImageCommand.h
        Document/Command/ReplaceTextCommand.h
        Document/Command/ResizeImageCommand.h
        Document/Command/SetTitleCommand.h
        Utils/HtmlUtils.h
        Utils/FileUtils.h
)

add_executable(${PROJECT_NAME}Test
        test/SetTitleCommandTest.cpp
        test/ResizeImageCommandTests.cpp
        test/ReplaceTextCommandTest.cpp
        test/InsertImageCommandTests.cpp
        test/HistoryTest.cpp
        test/HistoryTest.cpp
        test/DeleteItemCommandTest.cpp
        test/CMenuTest.cpp
        test/CDocumentTest.cpp
        test/main.cpp
        test/InsertParagraphCommandTest.cpp
)

target_link_libraries(${PROJECT_NAME}Test gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)