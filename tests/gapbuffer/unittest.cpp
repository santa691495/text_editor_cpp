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

	EXPECT_EQ(test_buffer.get_text(), expected_text);
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

	EXPECT_EQ(test_buffer.get_text(), expected_text);
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

	EXPECT_EQ(test_buffer.get_text(), expected_text);
}


