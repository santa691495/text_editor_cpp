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

