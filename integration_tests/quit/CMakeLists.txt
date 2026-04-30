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

add_test(NAME quit_editor_test COMMAND quit_editor_test)
