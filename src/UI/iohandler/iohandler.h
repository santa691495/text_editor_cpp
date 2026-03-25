#include <ncurses.h>
#include <string>
#include <vector>
//io handler just waits for input thats it 
//also catches output from subsystems 
//	for example, run() returns false, then 
//	IO makes an error string for display to show

#ifndef IO_HANDLER
#define IO_HANDLER

class IOHandler {
	private:
		std::string buffer_str;
		std::string cmd_str;

	public:	

		IOHandler();
		void handle_input();
		std::string get_cmd_str();
		std::string get_buffer_str();
		
};

#endif //IO_HANDLER
