#include <ncurses.h>
#include <string>
#include "cmdstatus.h"
	
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

//TODO: handle arrow left and arrow right
class Display {
	private:

		WINDOW* cmd_status_win;
		WINDOW* cmd_mode_win;

	public:

		Display();

		void render_buffer(std::string& buffer_text);
		void render_cmd_mode();
		void render_cmd_status(CmdStatusObject& cmd_status);
		void move_cursor_left();
		void move_cursor_right();

		~Display();
		
	private:

		WINDOW* get_cmd_mode_win();
		std::string format_cmd_status(CmdStatusObject& cmd_status);
};

#endif //DISPLAY
