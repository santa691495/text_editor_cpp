#include "gtest/gtest.h"
#include <ncurses.h>
#include "display.h"
#include <string>

TEST(Display, RenderBuffer){

	std::string expected_str = "TEST SUCCESS ";

	Display display_obj;

	initscr();		
	
	display_obj.render_buffer(expected_str);	



	move(0,0);

	char buffer_internal[50];
	innstr(buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);

	endwin();

	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}

TEST(Display, RenderCommandMode){

	std::string expected_str = "TestRenderCommandMode";

	initscr();

	Display display_obj;	
	display_obj.render_cmd_mode();

	WINDOW* cmd_mode_win = display_obj.get_cmd_mode_win();

	//save starting pos of cursor in the window 
	//for checking internal buffer later
	int curs_y, curs_x;
	getyx(cmd_mode_win, curs_y, curs_x);

	wprintw(cmd_mode_win, "%s", expected_str.c_str());

	char buffer_internal[50];
	mvwinnstr(cmd_mode_win, curs_y, curs_x, buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);
	
	endwin();

	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}

TEST(Display, RenderCommandStatus){
	CmdStatusObject cmd_status(CmdType::write, true);
	std::string expected_str = "success : write ";
	std::string buffer_str = "";

	initscr();

	Display display_obj;
	display_obj.render_buffer(buffer_str);
	display_obj.render_cmd_status(cmd_status);

	WINDOW* cmd_status_win = display_obj.get_cmd_status_win();

	wmove(cmd_status_win, 0, 0);
	wrefresh(cmd_status_win);

	char buffer_internal[50];
	winnstr(cmd_status_win, buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);

	endwin();

	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}

















