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
		bool is_at_line_edge();
		bool is_at_line_start();
		void move_to_start();

		bool move_startln_up();
		bool move_startln_down();

		void grow();	
		bool is_growable();

		std::string get_text();	
		size_t get_current_size(); //todo
		void backspace();
		void clear();	

	private:
		bool move_right_line();
		bool move_left_line();
		void move_right_loop(size_t steps);
};

#endif //GAP_BUFFER 
