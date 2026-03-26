#include "gtest/gtest.h"
#include "iohandler.h"
#include "cmdtype.h"
#include "cmdstatus.h"
#include <string>
#include <ncurses.h>

//need to set up some ncurses environment for this test 
//TODO: fix tests and handle input function 
TEST(IOHandler, HandleInput){
	initscr();
	raw();
	keypad(stdscr, TRUE);

	std::string expected_buffer_str = "b";
	std::string expected_cmd_str = "c";
	
	IOHandler io_handler;
	
	//first input
	printw( "--- TEST HANDLE INPUT ---");
	printw( " ! check source for expected output");
	printw( " buffer input (enter b): ");

	refresh();
	io_handler.handle_input();
	clear();

	printw(" command input (use CTRL + e , just click once!): ");
	
	refresh();
	io_handler.handle_input();
	clear();		
	
	EXPECT_TRUE(io_handler.is_cmd_mode());

	printw(" command input (enter 'c'): ");

	refresh();
	io_handler.handle_input();
	clear();

	printw(" command input (press ENTER): ");

	refresh();
	io_handler.handle_input();
	clear();


	EXPECT_TRUE(!io_handler.is_cmd_mode());
	
	printw("Expected string: %s \n", expected_buffer_str.c_str());
	printw("Recieved string: %s \n", io_handler.get_buffer_str().c_str());

	printw("Expected string: %s \n", expected_cmd_str.c_str());
	printw("Recieved string: %s \n", io_handler.get_cmd_str().c_str());
	
	printw("\n\n\nPress any character to exit. ");

	refresh();		
	getch();
	endwin();

	EXPECT_EQ(io_handler.get_buffer_str(), expected_buffer_str);
	EXPECT_EQ(io_handler.get_cmd_str(), expected_cmd_str);

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
