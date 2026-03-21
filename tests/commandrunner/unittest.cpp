#include "gapbuffer.h"
#include "filemanager.h"
#include "cmd_obj.h"
#include "cmdrunner.h"
#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

//must write to file
TEST(CommandRunner, RegisterCmdWrite){

	std::filesystem::path target_file = "testpath/testfile.txt";
	std::filesystem::path current_path = "unittest.cpp";
	FileManager filemanager(current_path);

	GapBuffer gapbuffer;
	
	std::string expected_text = "qwerty";
	for(char ch : expected_text){
		gapbuffer.insert(ch);
	}

	EXPECT_EQ(gapbuffer.get_text(), expected_text);
	EXPECT_EQ(filemanager.get_current_file(), "/home/dingdong/softwareprojects/text_editor_practice/build/tests/commandrunner/unittest.cpp" );

	bool running = true;
	
	CommandObject cmd;
	cmd.type = "w";
	cmd.args.push_back(target_file);
	
	CommandRunner test_cmdrunner(filemanager, gapbuffer, running);
	
	//WRITE TO THE FILE
	test_cmdrunner.run(cmd);
	
	//verify if written
	
	
	ASSERT_EQ(gapbuffer.get_text(), expected_text);
}




