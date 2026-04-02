#include <ncurses.h>
#include "inputevent.h"

/*
	
IOHandler

	Responsible for resolving user input using external library functions
	( getch() from the ncurses library) into either a command or buffer input,
	and responsible for converting diagnostic data from CommandRunner into a
	format (primarily std::string) digestible by the Display object.


*/

#ifndef IO_HANDLER
#define IO_HANDLER
//TODO:
// IOHandler must be stateless and only handle input.
//it must not store state.
// editor state could be stored elsewhere
// parsing must be handled by display
//needs to return what type of input (make input event struct with enum class Type)

class IOHandler {
	public:	

		IOHandler();
		InputEvent get_input();
};

#endif //IO_HANDLER
