add_executable(gapbuffer_tests unittest.cpp case_after_grow/unittest.cpp)

target_link_libraries(gapbuffer_tests
	GTest::gtest_main
	gapbuffer
)

include(GoogleTest)
gtest_discover_tests(gapbuffer_tests)

target_compile_options(gapbuffer_tests PRIVATE 
	-g
	-O0
)
