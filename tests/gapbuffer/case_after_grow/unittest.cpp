#include "gtest/gtest.h"
#include "gapbuffer.h"
#include <string>
	
TEST(GapBuffer, GetTextAfterGrow){
	GapBuffer test_buffer;
	std::string expected_text = "qwerty";
	
	for(char& ch : expected_text){
		test_buffer.insert(ch);
	}	

	test_buffer.grow();	

	ASSERT_EQ(test_buffer.get_text(), expected_text);
}

TEST(GapBuffer, InsertionAfterGrow){
	std::string buffer_text = "qwerty";
	std::string expected_text = "qwertyu";
	
	GapBuffer test_buffer;	
	
	for(char& ch : buffer_text){
		test_buffer.insert(ch);
	}

	test_buffer.grow();	
	test_buffer.insert('u');
	
	ASSERT_EQ(test_buffer.get_text(), expected_text);
}	

/*
TEST(GapBuffer, BackspaceAfterGrow){

}

TEST(GapBuffer, BackspaceEmptyAfterGrow){

}

TEST(GapBuffer, MovementAfterGrow){

}

TEST(GapBuffer, MoveCursorAfterGrow){

}

TEST(GapBuffer, IsGrowableAfterGrowNegative){

}		

TEST(GapBuffer,  IsGrowableAfterGrowPositive){

}

TEST(GapBuffer, GetTextAfterGrow){

}	
*/



