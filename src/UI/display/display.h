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


//TODO: Rework display
// - remove the separate window for command input (print on same window instead, on the bottom)
// - remove the fix and save cursor positions
// - render command mode should clear the screen and
//	 only show the command input while on command mode !

class Display {
	private:

		WINDOW* cmd_status_win;

		int curs_current_y;
		int curs_current_x;

	public:

		Display();

		void render_buffer(std::string& buffer_text);
		void render_cmd_status(CmdStatusObject& cmd_status);
		void render_cmd_mode();
		void move_cursor_left();
		void move_cursor_right();

		~Display();
		
	private:

		std::string format_cmd_status(CmdStatusObject& cmd_status);
};

#endif //DISPLAY
