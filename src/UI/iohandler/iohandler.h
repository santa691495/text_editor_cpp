#include <ncurses.h>
#include <string>
#include <vector>
#include "cmdstatus.h"
#include "cmdtype.h"

/*
	
IOHandler

	Responsible for resolving user input using external library functions
	( getch() from the ncurses library) into either a command or buffer input,
	and responsible for converting diagnostic data from CommandRunner into a
	format (primarily std::string) digestible by the Display object.


*/

#ifndef IO_HANDLER
#define IO_HANDLER

class IOHandler {
	private:
		std::string buffer_str;
		std::string cmd_str;
		bool cmd_mode = false;

	public:	

		IOHandler();
		void handle_input();
		std::string get_cmd_str();
		std::string get_buffer_str();
		
		std::string parse_cmd_status(CmdStatusObject cmd_status);	
		bool is_cmd_mode();		
};

#endif //IO_HANDLER
