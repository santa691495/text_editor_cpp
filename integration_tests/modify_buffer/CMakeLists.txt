add_executable(modify_buffer_test integration.cpp)

target_link_libraries(modify_buffer_test
	GTest::gtest_main
	display
	iohandler
	gapbuffer
)

