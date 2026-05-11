#include <ncurses.h>
#include <string> 
#include "gapbuffer.h"
#include "gtest/gtest.h"

TEST(GapBuffer, MoveStartlnUpNewLinesStacked){
	GapBuffer test_buffer;	

	std::string buffer_str = "aaaa\n\n\n\n\naaaa";
	std::string expected_str = "aaaa\n\n!\n\n\naaaa";

	for(char& ch : buffer_str){
		test_buffer.insert(ch);
	}	    

	test_buffer.move_startln_up();
	test_buffer.move_startln_up();
	test_buffer.move_startln_up();
	test_buffer.insert('!');

	ASSERT_EQ(test_buffer.get_text(), expected_str);
}

