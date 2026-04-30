add_executable(open_file_test integration.cpp)

target_link_libraries(open_file_test
    GTest::gtest_main
    display
    iohandler
    cmdparser
    cmdrunner
    filemanager
    iohandler
    editorstate
    ${CURSES_LIBRARIES} tinfo
)

include(GoogleTest)
gtest_discover_tests(open_file_test)

add_test(NAME open_file_test COMMAND open_file_test)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/test_folder/test_file.txt" "File Open Success!")