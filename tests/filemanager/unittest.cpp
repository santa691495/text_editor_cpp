#include "gtest/gtest.h"
#include "gapbuffer.h"
#include "filemanager.h"
#include <string>
#include <filesystem>
#include <fstream>

TEST(FileManager, ResolvePathLower){
	std::filesystem::path current_file = std::filesystem::current_path() / "dummy.txt";
	std::filesystem::path target_path = "./test_folder/dummy_target.txt";
	std::filesystem::path expected_path = std::filesystem::current_path() / "test_folder/dummy_target.txt";

	GapBuffer test_buffer;
	FileManager test_fm(current_file);

	ASSERT_EQ(test_fm.resolve_target_path(target_path), expected_path);
}

TEST(FileManager, ResolvePathHigher){
	std::filesystem::path current_file = std::filesystem::current_path() / "test_folder/dummy_target.txt";
	std::filesystem::path target_path = "../dummy.txt";
	std::filesystem::path expected_path = std::filesystem::current_path() / "dummy.txt";
	
	GapBuffer test_buffer;
	FileManager test_fm(current_file);
	
	ASSERT_EQ(test_fm.resolve_target_path(target_path), expected_path);
}

TEST(FileManager, FileExists){
	std::filesystem::path current_file = std::filesystem::current_path() / "dummy.txt";
	std::filesystem::path target_path = "./test_folder/dummy_target.txt";
	
	GapBuffer test_buffer;
	FileManager test_fm(current_file);
	
	ASSERT_TRUE(test_fm.file_exists(target_path));
}
	
//text in target file must equal to text in gapbuffer
TEST(FileManager, WriteFile){
	std::filesystem::path target_path = "./test_folder/dummy_target.txt";
	std::filesystem::path current_file = std::filesystem::current_path() / "dummy.txt";
	
	std::string expected_text = "build/testsuccess";
		
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
	
	ASSERT_EQ(file_text, expected_text);
}

TEST(FileManager, ReadFile){
	std::filesystem::path target_path = "test_folder/dummy_target.txt";
	std::filesystem::path current_file = std::filesystem::current_path() / "dummy.txt";
	std::string file_text = "success";
	
	std::ofstream target_file(target_path);
	EXPECT_TRUE(target_file);

	target_file << file_text;

	target_file.close();

	//confirm it went into the file 
	std::ifstream target_infile(target_path);
	EXPECT_TRUE(target_infile);

	std::string actual_file_text;
	std::getline(target_infile, actual_file_text, '\0');	
	EXPECT_EQ(file_text, actual_file_text);

	FileManager test_fm(current_file);
	GapBuffer test_buffer;

	test_fm.read_file(target_path, test_buffer);
	
	ASSERT_EQ(file_text, test_buffer.get_text());
}

TEST(FileManager, GetCurrentFile){
	std::filesystem::path current_file = std::filesystem::current_path() / "dummy.txt";
	
	FileManager test_fm(current_file);
	
	ASSERT_EQ(test_fm.get_current_file(), current_file);
}

TEST(FileManager, SetCurrentFile){
	std::filesystem::path new_path = "./test_folder/dummy_target.txt";
	std::filesystem::path current_file = std::filesystem::current_path() / "dummy.txt";
	
	FileManager test_fm(current_file);
	
	test_fm.set_current_file(new_path);
		
	std::filesystem::path expected_path = std::filesystem::current_path() / "test_folder/dummy_target.txt";

	ASSERT_EQ(test_fm.get_current_file(), expected_path);
}

TEST(FileManager, Constructor){

	std::filesystem::path current_file = "../filemanager/dummy.txt";
	std::filesystem::path expected_path = std::filesystem::current_path() / "dummy.txt";
	
	FileManager test_fm(current_file);	

	ASSERT_EQ(test_fm.get_current_file(), expected_path);
}

