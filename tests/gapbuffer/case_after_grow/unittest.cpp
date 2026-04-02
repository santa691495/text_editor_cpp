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

TEST(GapBuffer, IsGrowableAfterGrowNot){
	GapBuffer test_buffer;
	size_t max_size = test_buffer.get_current_size();	

	for(size_t i = 0; i < max_size; ++i){
		test_buffer.insert('a');
	}	

	test_buffer.grow();
	test_buffer.insert('a');

	EXPECT_FALSE(test_buffer.is_growable());
}		

TEST(GapBuffer,  IsGrowableAfterGrow){
	GapBuffer test_buffer;
	size_t max_size = test_buffer.get_current_size();	

	for(size_t i = 0; i < max_size; ++i){
		test_buffer.insert('a');
	}

	test_buffer.grow();

	size_t new_max_size = max_size * 2;
	
	for(size_t i = 0; i < max_size; ++i){
		test_buffer.insert('a');
	}

	EXPECT_TRUE(test_buffer.is_growable());
}

TEST(GapBuffer, ClearAfterGrow){
	std::string buffer_text = "qwertyuiop";
	GapBuffer test_buffer;
	
	for(char& ch : buffer_text){
		test_buffer.insert(ch);
	}	

	test_buffer.grow();
	test_buffer.clear();

	ASSERT_EQ(test_buffer.get_text(), "");
}



