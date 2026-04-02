#include "gtest/gtest.h"
#include <ncurses.h>
#include "display.h"
#include <string>

TEST(Display, RenderBuffer){

	std::string buffer_str = "TEST\nSUCCESS\npress any key to stop"
		" this test.";

	Display display_obj;

	initscr();		
	
	display_obj.render_buffer(buffer_str);	
	getch();

	clear();	
	printw("%s", "test passed? y/n : ");
	refresh();	

	char test_status = getch();
	clear();

	endwin();

	ASSERT_EQ(test_status, 'y');	
}

TEST(Display, RenderCommandMode){
	
	std::string buffer_str = "TEST COMMAND MODE\npress any key twice to stop command"
		" mode in this test.";

	initscr();

	Display display_obj;	
	display_obj.render_buffer(buffer_str);
	display_obj.render_cmd_mode();

	getch();
	getch();
	
	clear();
	printw("%s", "test passed? y/n : ");
	refresh();

	char test_status = getch();
	
	clear();
	endwin();

	ASSERT_EQ(test_status, 'y');	
}

TEST(Display, RenderCommandStatus){

	CmdStatusObject cmd_status(CmdType::write, true);
		
	std::string buffer_str = "TEST COMMAND STATUS\npress any key to stop"
		" this test."
		"\n\ntest must show the status"
		" string provided in the test.";

	std::string status_str = "success : write ";

	Display display_obj;
	display_obj.render_buffer(buffer_str);
	
	display_obj.render_cmd_status(cmd_status);

	getch();
	
	clear();
	printw("%s", "test passed? y/n : ");
	refresh();

	char test_status = getch();
	
	clear();
	endwin();

	ASSERT_EQ(test_status, 'y');	
}
















