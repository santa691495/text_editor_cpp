#include <vector>
#include <string>

#ifndef GAP_BUFFER
#define GAP_BUFFER
	
/*
 GapBuffer

	Responsible for manipulating the state of the program's text buffer 
	implementation using a gap buffer, the primary data structure used to 
	store editable text. 

*/
class GapBuffer {
	private:
		std::vector<char> buffer;
		static constexpr size_t init_buffer_size = 4000;
		char* gap_start = nullptr;
		char* gap_end = nullptr;

	public:
		GapBuffer();
	
		void insert(char data);
		void move_left();
		void move_right();
		void move_cursor(size_t index);
		void grow();
		std::string get_text();	
		size_t get_current_size(); 
		void backspace();
		void clear();	
};

#endif //GAP_BUFFER
