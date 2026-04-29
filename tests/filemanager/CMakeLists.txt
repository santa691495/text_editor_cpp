add_executable(filemanager_tests unittest.cpp)

target_link_libraries( filemanager_tests
	GTest::gtest_main
	gapbuffer
	filemanager
)

target_compile_options(filemanager_tests PRIVATE 
	-Wall
	-Werror
	-g
	-O0
)

include(GoogleTest)
gtest_discover_tests(filemanager_tests)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dummy.txt" "dummy")   
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/test_folder/dummy_target.txt" " ")