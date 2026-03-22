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
	
	//prep deps
	std::filesystem::path current_file = "./dummy.txt";
	std::filesystem::path target_file = "./test_path/target.txt";

	FileManager filemanager(current_file);

	bool running = true;
	GapBuffer gapbuffer;
	
	std::string expected_text = "qwerty"; //target and gap must have this
	for(char ch : expected_text){
		gapbuffer.insert(ch);
	}

	//prep command 
	CommandObject cmd_obj;
	cmd_obj.type = "w";
	cmd_obj.args.push_back(target_file);
	
	ASSERT_TRUE(filemanager.file_exists(target_file));
	ASSERT_TRUE(filemanager.file_exists(current_file));

	//prep runner
	CommandRunner cmdrunner(filemanager, gapbuffer, running);
	
	//le run command
	cmdrunner.run(cmd_obj);
		
	//le verify
	bool is_file_read = filemanager.read_file(target_file, gapbuffer);
	ASSERT_TRUE(is_file_read);

	ASSERT_EQ(gapbuffer.get_text(), expected_text);
}




