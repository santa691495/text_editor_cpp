#include <string> 
#include <vector>
#include "gapbuffer.h"
#include "gtest/gtest.h"

TEST(GapBuffer, ConsecutiveInsertion){
	char x  {'a'};
	char y  {'b'};
	char z  {'c'};
	
	GapBuffer test_buffer;
	
	test_buffer.insert(x);
	test_buffer.insert(y);
	test_buffer.insert(z);
	
	EXPECT_EQ(test_buffer.get_text(), x+y+z);
}

TEST(GapBuffer, MovementLeft){
	GapBuffer test_buffer;

	test_buffer.insert('a');
	test_buffer.insert('b');
	
	test_buffer.move_left();
	
	test_buffer.insert('c');
		
	EXPECT_EQ(test_buffer.get_text(), "acb");
}

TEST(GapBuffer, MovementRight){
	GapBuffer test_buffer;

	test_buffer.insert('a');
	test_buffer.insert('b');
	
	test_buffer.move_left();
	test_buffer.move_left();
	test_buffer.move_right();
	
	test_buffer.insert('c');
		
	EXPECT_EQ(test_buffer.get_text(), "acb");
}


