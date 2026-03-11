#include <string> 
#include <vector>
#include "gapbuffer.h"
#include "gtest/gtest.h"
//passed
TEST(GapBuffer, ConsecutiveInsertion){
	char x  ='a';
	char y  ='b';
	char z  ='c';
	
	GapBuffer test_buffer;
	
	test_buffer.insert(x);
	test_buffer.insert(y);
	test_buffer.insert(z);
	
	std::string expected_text;
	expected_text += x;
	expected_text += y;
	expected_text += z;

	EXPECT_EQ(test_buffer.get_text(), expected_text);
}
//passed
TEST(GapBuffer, MovementLeft){
	GapBuffer test_buffer;

	char x  ='a';
	char y  ='b';
	char z  ='c';

	test_buffer.insert(x);
	test_buffer.insert(y);
	
	test_buffer.move_left();
	
	test_buffer.insert(z);
	
	std::string expected_text;
	expected_text += x;
	expected_text += z;
	expected_text += y;

	EXPECT_EQ(test_buffer.get_text(), expected_text);
}
//passed
TEST(GapBuffer, MovementRight){
	GapBuffer test_buffer;

	char x  ='a';
	char y  ='b';
	char z  ='c';

	test_buffer.insert(x);
	test_buffer.insert(y);

	test_buffer.move_left();
	test_buffer.move_left();
	test_buffer.move_right();
		
	test_buffer.insert(z);
	
	std::string expected_text;
	expected_text += x;
	expected_text += z;
	expected_text += y;

	EXPECT_EQ(test_buffer.get_text(), expected_text);
}
//passed
//FIXME: make expected_text the sum of default and inserted to make it more dynamic
TEST(GapBuffer, MoveCursorRight){
	GapBuffer test_buffer;
	std::string default_text = "qwertyuiop";
	std::string inserted_text = "abc";
	std::string expected_text = "qwertyabcuiop";

	for(auto ch : default_text){
		test_buffer.insert(ch);
	}
	
	size_t insertion_index = 6;
	test_buffer.move_cursor(insertion_index);

	for(auto ch : inserted_text){
		test_buffer.insert(ch);
	}

	EXPECT_EQ(test_buffer.get_text(), expected_text);
}
//passed
TEST(GapBuffer, MoveCursorLeft){
	GapBuffer test_buffer;
	std::string default_text = "qwertyuiop";
	std::string inserted_text = "abc";
	std::string expected_text = "qabcwertyuiop";

	for(auto ch : default_text){
		test_buffer.insert(ch);
	}
	
	size_t init_index = 6;
	size_t insertion_index = 1;
	test_buffer.move_cursor(init_index);
	test_buffer.move_cursor(insertion_index);
	
	for(auto ch : inserted_text){
		test_buffer.insert(ch);
	}

	EXPECT_EQ(test_buffer.get_text(), expected_text);
}

TEST(GapBuffer, Grow){
	GapBuffer test_buffer;
	
	//growth happens when the buffer is filled 
	//must check if the previous text is still preserved by adding
	//more text after the growth then checking
	
	for(size_t i = 0; i < 4000; ++i){
		test_buffer.insert('A');
	}

	test_buffer.grow();
	test_buffer.insert('B');
	
	size_t target_index = 4000;
	std::string buffer_text = test_buffer.get_text();
	
	EXPECT_EQ(buffer_text[target_index], 'B');
}

TEST(GapBuffer, Backspace){
	GapBuffer test_buffer;
	
	std::string default_text = "abc";
	std::string expected_text = "ab";
	for(auto ch : default_text){
		test_buffer.insert(ch);
	}
	
	test_buffer.backspace();
	
	EXPECT_EQ(test_buffer.get_text(), expected_text);
}


