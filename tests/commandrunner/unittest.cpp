#include "gapbuffer.h"
#include "filemanager.h"
#include "cmd_obj.h"
#include "cmdrunner.h"
#include "cmdtype.h"
#include "cmdstatus.h"
#include "gtest/gtest.h"
#include <string>
#include <filesystem>
#include <fstream>
//TODO: Rewrite tests to adjust for new diagnostics implementation for command runners
//must write to file
TEST(CommandRunner, RegisterCmdWrite){
	
	//prep deps
	std::filesystem::path current_file = "./dummy.txt";
	std::filesystem::path target_file = "./test_path/target.txt";

	FileManager filemanager(current_file);

	bool running = true;
	GapBuffer gapbuffer;
	
	std::string expected_text = "qwerty"; 	
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
	CmdStatusObject cmd_status = cmdrunner.run(cmd_obj);	
	
	bool is_file_read = filemanager.read_file(target_file, gapbuffer);
	ASSERT_TRUE(is_file_read);
	
	ASSERT_EQ(gapbuffer.get_text(), expected_text);
	EXPECT_TRUE(cmd_status.success);
	EXPECT_EQ(cmd_status.cmd_type, CmdType::write);
}

TEST(CommandRunner, RegisterCmdRead){
	std::filesystem::path current_file = "./dummy.txt";
	std::filesystem::path target_file = "./test_path/target.txt";

	FileManager filemanager(current_file);

	bool running = true;
	GapBuffer gapbuffer;
	
	//prep the file 
	std::ofstream out_file(target_file);
		
	ASSERT_TRUE(out_file.is_open());

	std::string expected_text = "qwerty";
	
	out_file << expected_text;
	out_file.close();
	
	CommandObject cmd_obj;
	cmd_obj.type = "o";
	cmd_obj.args.push_back(target_file);	

	CommandRunner cmdrunner(filemanager, gapbuffer, running);
	
	CmdStatusObject cmd_status = cmdrunner.run(cmd_obj);

	ASSERT_EQ(gapbuffer.get_text(), expected_text);
	EXPECT_TRUE(cmd_status.success);
	EXPECT_EQ(cmd_status.cmd_type, CmdType::read);
} 






