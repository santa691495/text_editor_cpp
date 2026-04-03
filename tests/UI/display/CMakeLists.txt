add_executable(display_tests unittest.cpp)

target_link_libraries(display_tests
	display
	GTest::gtest_main
	${CURSES_LIBRARIES} tinfo
)
