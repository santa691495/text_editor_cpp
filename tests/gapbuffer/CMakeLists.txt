add_executable(gapbuffer_tests ${CMAKE_CURRENT_SOURCE_DIR}/unittest.cpp)

target_link_libraries(gapbuffer_tests
	GTest::gtest_main
	gapbuffer
)

include(GoogleTest)
gtest_discover_tests(gapbuffer_tests)

