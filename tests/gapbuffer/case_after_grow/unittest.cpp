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


TEST(GapBuffer, BackspaceAfterGrow){
	std::string buffer_text = "qwertyu";
	std::string expected_text = "qwerty";
	
	GapBuffer test_buffer;	
	
	for(char& ch : buffer_text){
		test_buffer.insert(ch);
	}

	test_buffer.grow();	
	test_buffer.backspace();
	
	ASSERT_EQ(test_buffer.get_text(), expected_text);
}

TEST(GapBuffer, BackspaceEmptyAfterGrow){
	std::string expected_text = "";
	
	GapBuffer test_buffer;	
	
	test_buffer.grow();	
	test_buffer.backspace();
	
	ASSERT_EQ(test_buffer.get_text(), expected_text);
}

TEST(GapBuffer, MovementAfterGrow){
	std::string init_buffer_text = "qwerty";
	std::string expected_text = "qwertayb";
	GapBuffer test_buffer;

	test_buffer.grow();		
	
	for(char& ch : init_buffer_text){
		test_buffer.insert(ch);
	}
		
	test_buffer.move_left();
	test_buffer.insert('a');

	test_buffer.move_right();
	test_buffer.insert('b');

	ASSERT_EQ(test_buffer.get_text(), expected_text);

}

/*
TEST(GapBuffer, IsGrowableAfterGrowNegative){

}		

TEST(GapBuffer,  IsGrowableAfterGrowPositive){

}

TEST(GapBuffer, GetTextAfterGrow){

}	
*/



