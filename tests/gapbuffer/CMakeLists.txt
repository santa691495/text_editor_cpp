add_executable(gapbuffer_tests unittest.cpp)

target_link_libraries( gapbuffer_tests
	gapbuffer
	gtest
)
