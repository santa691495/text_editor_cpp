add_executable(filemanager_tests unittest.cpp)

target_link_libraries( filemanager_tests
	GTest::gtest_main
	gapbuffer
	filemanager
)

include(GoogleTest)
gtest_discover_tests(filemanager_tests)
