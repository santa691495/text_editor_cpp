#include <ncurses.h>
#include <string>
#include "cmdstatus.h"
#include "cmdtype.h"
	
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


//TODO: make the cursor go up or down to the start of each line.
//up should go to the start of line on up, then 
// down should go to start of line on bottom
// it should also check if the line is already at max or min height


class Display {
	private:

		WINDOW* cmd_status_win;

		int curs_saved_y;
		int curs_saved_x;
		CmdStatusObject saved_cmd_status = CmdStatusObject(CmdType::null, false);

	public:

		Display();

		void render_buffer(std::string& buffer_text);
		void render_cmd_status(CmdStatusObject cmd_status);
		void render_cmd_status();
		void render_cmd_mode(std::string& buffer_text);
		void render_cmd_mode();
		void save_cmd_status(CmdStatusObject cmd_status);
		void move_cursor_left();
		void move_cursor_right();
		void move_cursor_startln_up();
		void move_cursor_startln_down();
		void save_cursor_pos();
		void fix_cursor_pos();

		~Display();
		
	private:

		bool is_cursor_height_min();
		bool is_cursor_height_max();
		std::string format_cmd_status(CmdStatusObject& cmd_status);
};

#endif //DISPLAY
