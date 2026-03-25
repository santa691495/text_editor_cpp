#include "gtest/gtest.h"
#include "iohandler.h"
#include "cmdtype.h"
#include "cmdstatus.h"
#include <string>
#include <ncurses.h>

//need to set up some ncurses environment for this test 
TEST(IOHandler, HandleInput){
	initscr();
	raw();
	keypad(stdscr, TRUE);
	timeout(2000);

	std::string expected_buffer_str = "buffertest";
	std::string expected_cmd_str = "cmdtest";
	
	IOHandler io_handler;
	
	io_handler.handle_input();		

	EXPECT_EQ(io_handler.get_buffer_str(), expected_buffer_str);
	EXPECT_EQ(io_handler.get_buffer_str(), expected_cmd_str);

	endwin();
}

TEST(IOHandler, ParseCmdStatus){
	CmdStatusObject rsuccess(CmdType::read, true);
	CmdStatusObject wfail(CmdType::write, false);
	std::string expected_rsuccess = "command success : read file";
	std::string expected_wfail  = "command failed : write file";

	IOHandler io_handler;
	
	EXPECT_EQ(io_handler.parse_cmd_status(rsuccess), expected_rsuccess);
	EXPECT_EQ(io_handler.parse_cmd_status(wfail), expected_wfail);
	
}
