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
		GapBuffer():
		buffer{std::vector<char>(init_buffer_size)},
		gap_start{&buffer[0]},
		gap_end{buffer.data() + buffer.size()}

		{}
	
		void insert(char data);
		void move_left();
		void move_right();
		void grow();	
		bool is_growable();

		std::string get_text();	
		size_t get_current_size(); //todo
		void backspace();
		void clear();	

	private:
		void move_right_newline();
		void move_left_newline();
};

#endif //GAP_BUFFER
