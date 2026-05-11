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

	clear();
	endwin();

	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}	

TEST(Display, MoveDownAtBottom){
	Display display_obj;

	int expected_new_posx;
	int expected_new_posy;
	
	initscr();

	//windows are index 0 based, so subtract one
	int screen_max_y = getmaxy(stdscr) - 1;

	move(0,0);
	move(screen_max_y, 0);

	display_obj.move_cursor_startln_down();

	int current_x, current_y;
	getyx(stdscr, current_y, current_x);

	clear();
	endwin();

	expected_new_posx = 0;
	expected_new_posy = screen_max_y;

	ASSERT_EQ(current_x, expected_new_posx);
	ASSERT_EQ(current_y, expected_new_posy);
}	

TEST(Display, MoveDownNotAtBottom){
	Display display_obj;

	int expected_new_posx = 0;
	int expected_new_posy = 1;
	
	initscr();
	display_obj.move_cursor_startln_down();

	int current_x, current_y;
	getyx(stdscr, current_y, current_x);

	clear();
	endwin();

	ASSERT_EQ(current_y, expected_new_posy);
	ASSERT_EQ(current_x, expected_new_posx);
}	

TEST(Display, MoveUpAtTop){
	Display display_obj;

	int expected_new_posx = 0;
	int expected_new_posy = 0;
	
	initscr();	

	display_obj.move_cursor_startln_up();

	int current_x, current_y;
	getyx(stdscr, current_y, current_x);

	clear();
	endwin();

	ASSERT_EQ(current_y, expected_new_posy);
	ASSERT_EQ(current_x, expected_new_posx);
}	

TEST(Display, MoveUpNotAtTop){
	Display display_obj;

	int expected_new_posx = 0;
	int expected_new_posy = 0;
	
	initscr();	

	move(1,0);

	display_obj.move_cursor_startln_up();

	int current_x, current_y;
	getyx(stdscr, current_y, current_x);

	clear();
	endwin();

	ASSERT_EQ(current_y, expected_new_posy);
	ASSERT_EQ(current_x, expected_new_posx);
}	




















