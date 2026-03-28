#include <ncurses.h>
#include <string>
	
/*
	==================================
	DISPLAY

	Responsible for using ncurses functions
	to display the current buffer, command being written,
	and status of commands from the io handler. display takes
	input from gapbuffer object to render the screen,
	and from iohandler to display command as it is being
	written on a separate mini window within the TUI, as well as 
	display status messages from command execution.

	==================================
*/
#ifndef DISPLAY
#define DISPLAY

class Display {
	public:
		
		void render_buffer(std::string& buffer_text);
		void render_cmd_mode(bool& is_cmd_mode);
		void render_cmd_status(std::string& status_text, bool& is_cmd_mode);
	
};

#endif //DISPLAY
