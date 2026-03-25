add_executable(iohandler_tests unittest.cpp)

target_link_libraries(iohandler_tests
	GTest::gtest_main
	iohandler
	cmdtype
	cmdstatus
	${CURSES_LIBRARIES}
)

include(GoogleTest)
gtest_discover_tests(iohandler_tests)
