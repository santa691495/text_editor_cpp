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



















