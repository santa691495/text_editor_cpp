#include "gtest/gtest.h"
#include "display.h"
#include "iohandler.h"
#include "gapbuffer.h"
#include <ncurses.h>

TEST(ModifyBuffer, InsertOnly){
	// === setup ======================
	initscr();
	keypad(stdscr, TRUE);
	raw();	

	// ================================

	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "Copy This:";
	std::string expected_str = "Copy This:Copy This";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}

	std::string buffer_str = gap_buffer.get_text();

	display_handler.render_buffer(buffer_str);

	size_t input_loops = 9;
	
	for(size_t i = 0; i < input_loops; ++i){
		InputEvent input = io_handler.get_input();

		if(input.type == InputType::character){
			gap_buffer.insert(input.input_ch);
		}
	}

	// === teardown ======================

	endwin();

	// ===================================

	ASSERT_EQ(gap_buffer.get_text(), expected_str);
}

TEST(ModifyBuffer, MoveLeftAndInsert){
	// === setup ======================
	initscr();
	keypad(stdscr, TRUE);
	raw();	

	// ================================
	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "MoveLeftThenInsertA";
	std::string expected_str = "MoveLeftThenInsertAA";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}

	std::string buffer_str = gap_buffer.get_text();

	display_handler.render_buffer(init_buffer_str);

	size_t input_loops = 2;
	
	for(size_t i = 0; i < input_loops; ++i){
		InputEvent input = io_handler.get_input();

		if(input.type == InputType::character){
			gap_buffer.insert(input.input_ch);
		} else if(input.type == InputType::arrow_left){
			gap_buffer.move_left();
		}
	}


	// === teardown ======================

	endwin();

	// ===================================

	ASSERT_EQ(gap_buffer.get_text(), expected_str);

}

TEST(ModifyBuffer, MoveRightAndInsert){
	// === setup ======================
	initscr();
	keypad(stdscr, TRUE);
	raw();	

	// ================================

	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "MoveRightThenInsertA ";
	std::string expected_str = "MoveRightThenInsertA A";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}

	std::string buffer_str = gap_buffer.get_text();

	display_handler.render_buffer(init_buffer_str);

	size_t input_loops = 2;

	gap_buffer.move_left(); //to make cursor start at last char in buffer_str
	
	for(size_t i = 0; i < input_loops; ++i){
		InputEvent input = io_handler.get_input();

		if(input.type == InputType::character){
			gap_buffer.insert(input.input_ch);
		} else if(input.type == InputType::arrow_right){
			gap_buffer.move_right();
		}
	}
	// === teardown ======================
	endwin();

	// ===================================

	ASSERT_EQ(gap_buffer.get_text(), expected_str);
	
}



