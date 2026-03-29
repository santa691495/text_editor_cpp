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
	
	bool cmd_mode = true;	

	std::string buffer_str = "TEST COMMAND MODE\npress any key to stop command"
		" mode in this test.";

	initscr();

	Display display_obj;	
	display_obj.render_buffer(buffer_str);
	display_obj.render_cmd_mode(cmd_mode);

	getch();	
	
	clear();
	printw("%s", "test passed? y/n : ");
	refresh();

	char test_status = getch();
	
	endwin();

	ASSERT_EQ(test_status, 'y');	
}
