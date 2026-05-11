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

TEST(GapBuffer, Grow){
	GapBuffer test_buffer;
	size_t expected_size = test_buffer.get_current_size() * 2;
	
	test_buffer.grow();
	ASSERT_EQ(expected_size, test_buffer.get_current_size());

}

TEST(GapBuffer, Backspace){
	GapBuffer test_buffer;
	std::string buffer_str = "qwerty";
	std::string expected_string = "qwert";
		
	for(char& ch : buffer_str){
		test_buffer.insert(ch);
	}

	test_buffer.backspace();		
	ASSERT_EQ(test_buffer.get_text(), expected_string);
}	

TEST(GapBuffer, BackspaceEmpty){
	GapBuffer test_buffer;
	std::string expected_string = "";
		
	test_buffer.backspace();		
	ASSERT_EQ(test_buffer.get_text(), expected_string);
}

TEST(GapBuffer, IsGrowablePositive){
	GapBuffer test_buffer;	
	size_t max_size =  test_buffer.get_current_size();

	for(size_t i = 0; i < max_size; ++i){
		test_buffer.insert('a');
	}	

	ASSERT_TRUE(test_buffer.is_growable());
}	

TEST(GapBuffer, IsGrowableNegative){
	GapBuffer test_buffer;	
	size_t max_size =  test_buffer.get_current_size();

	for(size_t i = 1; i < max_size; ++i){
		test_buffer.insert('a');
	}	

	ASSERT_FALSE(test_buffer.is_growable());
}	

TEST(GapBuffer, MoveStartlnUp){
	GapBuffer test_buffer;	
	bool can_move_up;

	std::string buffer_str = "aaaa\naaaaa";
	std::string expected_str = "Baaaa\naaaaa";

	for(char& ch : buffer_str){
		test_buffer.insert(ch);
	}	

	//taget location is at the start of the line, so dont move
	can_move_up = test_buffer.move_startln_up();
	test_buffer.insert('B');

	EXPECT_TRUE(can_move_up);
	ASSERT_EQ(test_buffer.get_text(), expected_str);
}

TEST(GapBuffer, MoveStartlnDown){
	GapBuffer test_buffer;	
	bool can_move_down;

	std::string buffer_str = "a\na";
	std::string expected_str = "a\nBa";

	for(char& ch : buffer_str){
		test_buffer.insert(ch);
	}	

	for(char ch : buffer_str){
		test_buffer.move_left();
	}

	can_move_down = test_buffer.move_startln_down();
	test_buffer.insert('B');

	EXPECT_TRUE(can_move_down);
	ASSERT_EQ(test_buffer.get_text(), expected_str);
}	

TEST(GapBuffer, MoveStartlnDownAtBottom){
	GapBuffer test_buffer;	
	bool can_move_down;
	size_t max_size =  test_buffer.get_current_size();

	std::string buffer_str = "\na";
	std::string expected_str = "\naB";

	for(char& ch : buffer_str){
		test_buffer.insert(ch);
	}	

	//taget location is at the start of the line, so dont move
	can_move_down = test_buffer.move_startln_down();
	test_buffer.insert('B');

	EXPECT_FALSE(can_move_down);
	ASSERT_EQ(test_buffer.get_text(), expected_str);
}	

TEST(GapBuffer, MoveUpStartlnAtTop){
	GapBuffer test_buffer;	
	bool can_move_up;
	size_t max_size =  test_buffer.get_current_size();

	std::string buffer_str = "a\na";
	std::string expected_str = "Ba\na";

	for(char& ch : buffer_str){
		test_buffer.insert(ch);
	}	

	for(char& ch : buffer_str){
		test_buffer.move_left();
	}

	//taget location is at the start of the line, so dont move
	can_move_up = test_buffer.move_startln_up();
	test_buffer.insert('B');

	EXPECT_FALSE(can_move_up);
	ASSERT_EQ(test_buffer.get_text(), expected_str);
}

