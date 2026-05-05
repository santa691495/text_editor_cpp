add_executable(display_tests unittest.cpp)
target_link_libraries(display_tests
	display
	GTest::gtest_main
	${CURSES_LIBRARIES} tinfo
)	

include(GoogleTest)
gtest_discover_tests(display_tests)


target_compile_options(display_tests PRIVATE 
	-Wall
	-Werror
	-g
	-O0
)
