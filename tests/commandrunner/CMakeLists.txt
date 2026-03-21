add_executable(cmdrunner_tests unittest.cpp)

target_link_libraries(cmdrunner_tests 
	GTest::gtest_main
	gapbuffer
	filemanager
	cmd_obj
	cmdrunner
)	

include(GoogleTest)
gtest_discover_tests(cmdrunner_tests)

