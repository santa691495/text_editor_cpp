add_executable(write_file_test integration.cpp)

target_link_libraries(write_file_test
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
gtest_discover_tests(write_file_test)

add_test(NAME write_file_test COMMAND write_file_test)

# create file for testing, if not yet created
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/test_folder")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/test_folder/test_file.txt")