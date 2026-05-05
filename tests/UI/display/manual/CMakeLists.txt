add_executable(display_tests_manual manual.cpp)

target_link_libraries( display_tests_manual
	display
	GTest::gtest_main
	${CURSES_LIBRARIES} tinfo
)
