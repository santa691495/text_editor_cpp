#include "gtest/gtest.h"
#include <ncurses.h>
#include "display.h"
#include "inputtype.h"
#include "iohandler.h"
#include "cmdrunner.h"
#include "cmdparser.h"
#include "gapbuffer.h"
#include "cursorsyncer.h"
#include <string>
#include <vector>

TEST(ModifyBuffer, InsertOnly){
	initscr();
	keypad(stdscr, TRUE);
	raw();	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "Copy This:";
	std::string expected_str = "Copy This:Copy This";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}

	display_handler.render_buffer(init_buffer_str);
	std::string insert_str = "Copy This";

	for(char& ch : insert_str){
		ungetch(ch);
		InputEvent input = io_handler.get_input();

		EXPECT_EQ(input.input_ch, ch);
		EXPECT_EQ(input.type, InputType::character);

		if(input.type == InputType::character){
			gap_buffer.insert(input.input_ch);
		}
		
		std::string buffer_str = gap_buffer.get_text();
		display_handler.render_buffer(buffer_str);
	} 

	move(0,0);

	char buffer_internal[50];
	innstr(buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);

	endwin();
	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}

TEST(ModifyBuffer, MoveLeftAndInsert){
	initscr();
	keypad(stdscr, TRUE);
	raw();	

	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "MoveLeftThenInsertA";
	std::string expected_str = "MoveLeftThenInsertAA";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}

	std::vector<int> input_chars = {KEY_LEFT, 'A'};

	display_handler.render_buffer(init_buffer_str);

	for(int& ch : input_chars){
		ungetch(ch);
		InputEvent input = io_handler.get_input();

		if(input.type == InputType::character){
			gap_buffer.insert(input.input_ch);
		} else if (input.type == InputType::arrow_left){
			display_handler.move_cursor_left();
			gap_buffer.move_left();
		}

		std::string buffer_str = gap_buffer.get_text();
		display_handler.render_buffer(buffer_str);
	}

	move(0,0);

	char buffer_internal[50];
	innstr(buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);

	endwin();

	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}

TEST(ModifyBuffer, MoveRightAndInsert){
	initscr();
	keypad(stdscr, TRUE);
	raw();	

	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "MoveRightThenInsertA ";
	std::string expected_str = "MoveRightThenInsertA A";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}

	std::vector<int> input_chars = {KEY_RIGHT, 'A'};

	display_handler.render_buffer(init_buffer_str);

	for(int& ch : input_chars){
		ungetch(ch);
		InputEvent input = io_handler.get_input();

		if(input.type == InputType::character){
			gap_buffer.insert(input.input_ch);
		} else if (input.type == InputType::arrow_right){
			display_handler.move_cursor_right();
			gap_buffer.move_right();
		}

		std::string buffer_str = gap_buffer.get_text();
		display_handler.render_buffer(buffer_str);
	}

	move(0,0);

	char buffer_internal[50];
	innstr(buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);

	endwin();

	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}

TEST(ModifyBuffer, Backspace){
	initscr();
	keypad(stdscr, TRUE);
	raw();	

	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "DeleteAllOfMe";
	std::string expected_str = "";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}

	display_handler.render_buffer(init_buffer_str);

	for(char& ch : init_buffer_str){
		ungetch(KEY_BACKSPACE);
		InputEvent input = io_handler.get_input();

		if (input.type == InputType::backspace){
			gap_buffer.backspace();
		}

		std::string buffer_str = gap_buffer.get_text();
		display_handler.render_buffer(buffer_str);
	}

	move(0,0);

	char buffer_internal[50];
	innstr(buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);

	endwin();

	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}
