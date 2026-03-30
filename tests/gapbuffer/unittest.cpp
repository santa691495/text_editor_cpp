#include <string> 
#include <vector>
#include "gapbuffer.h"
#include "gtest/gtest.h"

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

	ASSERT_EQ(test_buffer.get_text(), expected_text);
}

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

	ASSERT_EQ(test_buffer.get_text(), expected_text);
}

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

	ASSERT_EQ(test_buffer.get_text(), expected_text);
}

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

	ASSERT_EQ(test_buffer.get_text(), expected_text);
}

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

	ASSERT_EQ(test_buffer.get_text(), expected_text);
}	

//TODO: add grow)() test ! URGENT !



