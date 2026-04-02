#include "gtest/gtest.h"
#include "display.h"
#include "iohandler.h"
#include "gapbuffer.h"
#include <ncurses.h>

TEST(ModifyBuffer, InsertOnly){
	//setup ======================
	initscr();
	keypad(stdscr, TRUE);
	raw();	
	
	std::string buffer_text = "qwerty";
	std::string expected_text = "qwertya";
	
	Display display_handler;
	IOHandler io_handler;
	GapBuffer gap_buffer;		

	for(auto& ch : buffer_text){
		gap_buffer.insert(ch);
	}
	
	//======================	
			
	display_handler.render_buffer(buffer_text);
	io_handler.handle_input(); //input 'a' in the test		
	
	for(auto& ch : io_handler.get_buffer_str()){
		gap_buffer.insert(ch);
	}

	endwin();

	ASSERT_EQ(gap_buffer.get_text(), expected_text);

}
/*
TEST(ModifyBuffer, MoveHorizontalAndInsert){

}

TEST(ModifyBuffer, MoveVerticalAndInsert){

}	
*/
