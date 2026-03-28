#include "display.h"
#include <ncurses.h>
#include <string>

// printw the current buffer

void Display::render_buffer(std::string& buffer_text){
	
	const char* c_text = buffer_text.c_str();
	printw("%s", c_text);
}

void Display::render_cmd_mode(bool& is_cmd_mode){
	
	if(!is_cmd_mode){
		return;
	}	
	
	int scr_height, scr_width;

	getmaxyx(stdscr, scr_height, scr_width);
		
	int win_height = 3;
	int win_width = scr_width;
	
	int start_y = scr_height - 3;
	int start_x = 0;
	
	WINDOW* cmd_win = newwin(win_height, win_width, start_y, start_x);

	box(cmd_win, 0, 0);

	wmove(cmd_win, start_y + 1, start_x + 1);
	
	refresh();	
	
	if(!is_cmd_mode){
		clear();
		delwin(cmd_win);
	}
}

void Display::render_cmd_status(std::string& status_text, bool& cmd_mode){
	
	int scr_height, scr_width;

	getmaxyx(stdscr, scr_height, scr_width);
		
	int win_height = 1;
	int win_width = scr_width;
	
	int start_y = scr_height - 3;
	int start_x = scr_width / 2;
	
	WINDOW* status_win = newwin(win_height, win_width, start_y, start_x);

	const char* c_text = status_text.c_str();
	wprintw(status_win,"%s", c_text);

	//TODO: replace this with a timer 
	if(cmd_mode){
		delwin(status_win);
	}
}

