add_executable(modify_buffer_test integration.cpp)

target_link_libraries(modify_buffer_test
	GTest::gtest_main
	display
	iohandler
	gapbuffer
	cursorsyncer
	editorstate
	cmdparser
	cmdrunner
	${CURSES_LIBRARIES} tinfo
)

include(GoogleTest)
gtest_discover_tests(modify_buffer_test)

add_test(NAME modify_buffer_test COMMAND modify_buffer_test)