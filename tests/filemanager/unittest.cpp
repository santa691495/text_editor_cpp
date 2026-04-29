#include "gtest/gtest.h"
#include "gapbuffer.h"
#include "filemanager.h"
#include <string>
#include <filesystem>
#include <fstream>

//TODO : Write tests for when nothing is passed to constructor, test all other functions in this state 

TEST(FileManager, ResolvePathLower){
	std::filesystem::path current_file = "/home/dingdong/softwareprojects/text_editor_practice/tests/filemanager/dummy_root.txt";
	std::filesystem::path target_path = "./test_path/dummy_target.txt";
	std::filesystem::path expected_path = "/home/dingdong/softwareprojects/text_editor_practice/tests/filemanager/test_path/dummy_target.txt";

	GapBuffer test_buffer;
	FileManager test_fm(current_file);

	ASSERT_EQ(test_fm.resolve_target_path(target_path), expected_path);
}

TEST(FileManager, ResolvePathHigher){
	std::filesystem::path current_file = "/home/dingdong/softwareprojects/text_editor_practice/tests/filemanager/test_path/dummy_target.txt";
	std::filesystem::path target_path = "../dummy_root.txt";
	std::filesystem::path expected_path = "/home/dingdong/softwareprojects/text_editor_practice/tests/filemanager/dummy_root.txt";
	
	GapBuffer test_buffer;
	FileManager test_fm(current_file);
	
	ASSERT_EQ(test_fm.resolve_target_path(target_path), expected_path);
}

TEST(FileManager, FileExists){
	std::filesystem::path current_file = "/home/dingdong/softwareprojects/text_editor_practice/tests/filemanager/dummy_root.txt";
	std::filesystem::path target_path = "./test_path/dummy_target.txt";
	
	GapBuffer test_buffer;
	FileManager test_fm(current_file);
	
	ASSERT_TRUE(test_fm.file_exists(target_path));
}
	
//text in target file must equal to text in gapbuffer
TEST(FileManager, WriteFile){
	std::filesystem::path target_path = "./test_path/dummy_target.txt";
	std::filesystem::path current_file = "/home/dingdong/softwareprojects/text_editor_practice/tests/filemanager/dummy_root.txt";
	
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
	
	ASSERT_EQ(file_text, expected_text);
}

TEST(FileManager, ReadFile){
	std::filesystem::path target_path = "./test_path/dummy_target.txt";
	std::filesystem::path current_file = "/home/dingdong/softwareprojects/text_editor_practice/tests/filemanager/dummy_root.txt";
	std::string file_text = "TestSuccess";
	
	std::ofstream target_file(target_path);
	target_file << file_text;

	FileManager test_fm(current_file);
	GapBuffer test_buffer;

	test_fm.read_file(target_path, test_buffer);
	
	ASSERT_EQ(file_text, test_buffer.get_text());
}

TEST(FileManager, GetCurrentFile){
	std::filesystem::path current_file = "/home/dingdong/softwareprojects/text_editor_practice/tests/filemanager/dummy_root.txt";
	
	FileManager test_fm(current_file);
	
	ASSERT_EQ(test_fm.get_current_file(), current_file);
}

TEST(FileManager, SetCurrentFile){
	std::filesystem::path new_path = "./test_path/dummy_target.txt";
	std::filesystem::path current_file = "/home/dingdong/softwareprojects/text_editor_practice/tests/filemanager/dummy_root.txt";
	
	FileManager test_fm(current_file);
	
	test_fm.set_current_file(new_path);
		
	std::filesystem::path expected_path = "/home/dingdong/softwareprojects/text_editor_practice/tests/filemanager/test_path/dummy_target.txt";

	ASSERT_EQ(test_fm.get_current_file(), expected_path);
}

TEST(FileManager, Constructor){

	std::filesystem::path current_file = "../filemanager/dummy.txt";
	std::filesystem::path expected_path = "/home/dingdong/softwareprojects/text_editor_practice/build/tests/filemanager/dummy.txt";
	
	FileManager test_fm(current_file);	

	ASSERT_EQ(test_fm.get_current_file(), expected_path);
}

// FileManager class must be able to resolve the relative path correctly 
// THIS IS A BUGGGGG!!!!!!!! RAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH
TEST(FileManager, ConstructorNoDefault){
	std::filesystem::path current_file = "";
	std::filesystem::path expected_path = "/home/dingdong/softwareprojects/text_editor_practice/build/tests/filemanager/dummy.txt";	
	std::filesystem::path target_path_relative = "dummy.txt";

	EXPECT_TRUE(std::filesystem::exists(expected_path));

	FileManager test_fm(current_file);	
	test_fm.set_current_file(target_path_relative);

	ASSERT_EQ(test_fm.get_current_file(), expected_path);
}

// THE BUG EXPLAINED 
// constructor turns "" into /home/.../filemanager, sets as current file 
// FileManager::set_current_file() turns the current file into 
// /home/.../tests , which is the parent of .../filemanager.  
// The path was OK on the first resolution, the second resolution destroyed it
// The misconception is that the first resolvution will resolve to 
// a normal file and NOT a folder, which in this case, it did resolve to a folder
// and our assumption is that the parent path would always be the 
// current directory of the file.
// But in our case which the default resolved to a folder,
// it resolves the path to its parent.
//
// In order to solve this we must check whether the passed path 
// passed to the constructor is a file or a folder. In order to determine,
// we must resolve it once. If its a file, then 
// resolve the path normally. Else, set the current file as "".
// RESOLUTION COUNTER : 1
//
// alternative solution: modify resolve_target_path() directly
// to check if current_file() is a file. if true, then set the base 
// to parent_file. else, set the base to the current_path().
// proceed normally. The problem with this solution though is
// it assigns current_file() to an invalid path, not simple
// RESOLUTION COUNTER : 0
// 	


