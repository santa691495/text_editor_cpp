add_executable(quit_editor_test integration.cpp)

target_link_libraries(quit_editor_test
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
gtest_discover_tests(quit_editor_test)