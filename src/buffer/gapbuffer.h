#include <vector>
#include <string>

#ifndef GAP_BUFFER
#define GAP_BUFFER

class GapBuffer {
	private:
		std::vector<char> buffer;
		static constexpr int init_buffer_size = 4000;
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
		void move_cursor(size_t index);
		void grow();
		std::string get_text();
		void backspace();

};

#endif //GAP_BUFFER
