#include "gtest/gtest.h"
#include "gapbuffer.h"
#include "filemanager.h"
#include <string>
#include <filesystem>
#include <fstream>

TEST(FileManagerNoConstructor, SetCurrentFile){
	std::filesystem::path current_file = "";
	std::filesystem::path expected_path = std::filesystem::current_path() / "dummy.txt";	
	std::filesystem::path target_path_relative = "./dummy.txt";

	EXPECT_TRUE(std::filesystem::exists(expected_path));

	FileManager test_fm(current_file);	
	test_fm.set_current_file(target_path_relative);

	ASSERT_EQ(test_fm.get_current_file(), expected_path);
}

TEST(FileManagerNoConstructor, BrokenConstructorPath){
	std::filesystem::path current_file = "./absdasndka/aslkdals/afn.txt"; 
	std::filesystem::path expected_path = "";	

	EXPECT_FALSE(std::filesystem::exists(current_file));

	FileManager test_fm(current_file);	

	ASSERT_EQ(test_fm.get_current_file(), expected_path);
}   

TEST(FileManagerNoConstructor, WriteFile){
	std::filesystem::path target_path = "../filemanager/dummy.txt";
	std::filesystem::path current_file = "";
	
	std::string expected_text = "TestSuccess";
		
	GapBuffer test_buffer;
	for(auto ch : expected_text){
		test_buffer.insert(ch);
	}	

	FileManager test_fm(current_file);
	test_fm.write_file(target_path, test_buffer);
	
	target_path = test_fm.resolve_target_path(target_path);

	std::ifstream target_file(target_path);
	
	EXPECT_TRUE(target_file.is_open());

	std::string file_text; 
	std::getline(target_file, file_text, '\0');

    //truncate the file
    std::ofstream truncate_file(target_path);   
    truncate_file.close();
	
	ASSERT_EQ(file_text, expected_text);
}   

TEST(FileManagerNoConstructor, ReadFile){
	std::filesystem::path target_path = "../filemanager/dummy.txt";
	std::filesystem::path current_file = "";
	std::string file_text = "TestSuccess";
	
	std::ofstream target_file(target_path);
	target_file << file_text;
    target_file.close();

    std::ifstream check_target_file(target_path);
    std::string current_file_text; 
    std::getline(check_target_file, current_file_text, '\0');
    EXPECT_EQ(file_text, current_file_text);

	FileManager test_fm(current_file);
	GapBuffer test_buffer;

	test_fm.read_file(target_path, test_buffer);

    //truncate the file
    std::ofstream truncate_file(target_path);   
    truncate_file.close();
    
	ASSERT_EQ(file_text, test_buffer.get_text());
}

