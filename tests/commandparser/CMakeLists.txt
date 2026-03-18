add_executable(cmdparser_tests unittest.cpp)

target_link_libraries( cmdparser_tests 
	cmd_obj
	cmdparser
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cmdparser_tests)
