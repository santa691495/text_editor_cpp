#include <string> 
#include <vector>
#include "gapbuffer.h"
#include <gtest/gtest.h>

TEST(GapBuffer, ConsecutiveInsertion){
	char x = 'a';
	char y = 'b';
	char z = 'c';
	
	GapBuffer test_buffer;
	
	test_buffer.insert(x);
	test_buffer.insert(y);
	test_buffer.insert(z);
	
	EXPECT_EQ(test_buffer.get_text(), x+y+z);
}
//movement correctly moves the chars to left and right
TEST(GapBuffer, ConsecutiveMovementLeft){

}

TEST(GapBuffer, ConsecutiveMovementRight){

}

TEST(GapBuffer, ConsecutiveMoveCursor){

}

TEST(GapBuffer, RandomMoveCursor){

}


