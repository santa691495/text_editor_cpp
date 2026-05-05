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

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dummy.txt" "dummy")   
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/test_folder/dummy_target.txt" " ")