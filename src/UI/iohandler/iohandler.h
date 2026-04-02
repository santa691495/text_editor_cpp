#include <ncurses.h>
#include "inputevent.h"

#define CTRL(k) ((k) & 0x1f)

/*
	
IOHandler

	Responsible for resolving user input using external library functions
	( getch() from the ncurses library), returning an InputEvent struct 
	containing the input and its type represented by an InputType enum.

*/

#ifndef IO_HANDLER
#define IO_HANDLER

class IOHandler {
	public:	

		InputEvent get_input();
};

#endif //IO_HANDLER
