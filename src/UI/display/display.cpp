#include "display.h"
#include <ncurses.h>
#include <string>

// printw the current buffer

void Display::render_buffer(std::string& buffer_text){
	
	const char* c_text = buffer_text.c_str();
	printw("%s", c_text);
	refresh();
}

void Display::render_cmd_mode(bool& is_cmd_mode){
	
	if(!is_cmd_mode){
		return;
	}	
	
	int scr_height, scr_width;

	getmaxyx(stdscr, scr_height, scr_width);
		
	int win_height = 3;
	int win_width = scr_width - 3;
	
	int start_y = scr_height - 3;
	int start_x = 0;
	
	WINDOW* cmd_win = newwin(win_height, win_width, start_y, start_x);

	box(cmd_win, 0, 0);

	wmove(cmd_win, 1 , 1);
	
	wrefresh(cmd_win);	
	
	if(!is_cmd_mode){
		wclear(cmd_win);
		delwin(cmd_win);
	}
}

void Display::render_cmd_status(std::string& status_text, bool& cmd_mode){
		
	if(cmd_mode){
		return;
	}

	int scr_height, scr_width;

	getmaxyx(stdscr, scr_height, scr_width);
		
	int win_height = 1;
	int win_width = scr_width/4;
	
	int start_y = scr_height - 3;
	int start_x = scr_width / 4;
	
	WINDOW* status_win = newwin(win_height, win_width, start_y, start_x);
	
	const char* c_text = status_text.c_str();	

	wattron(status_win, A_STANDOUT);
	wprintw(status_win,"%s", c_text);
	wattroff(status_win, A_STANDOUT);

	wrefresh(status_win);

	//TODO: replace this with a timer 
	if(cmd_mode){
		wclear(status_win);
		delwin(status_win);
	}
}

