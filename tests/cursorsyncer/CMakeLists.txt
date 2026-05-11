add_executable(cursorsyncer_tests unittest.cpp newlines_stacked/unittest.cpp)

target_link_libraries(cursorsyncer_tests 
    cursorsyncer
    gapbuffer
    display
    GTest::gtest_main
    ${CURSES_LIBRARIES} tinfo
)   

include(GoogleTest)
gtest_discover_tests(cursorsyncer_tests)

target_compile_options(cursorsyncer_tests PRIVATE 
	-g
	-O0
)

