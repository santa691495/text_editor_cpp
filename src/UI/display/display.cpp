#include "display.h"
#include "cmdstatus.h"
#include <ncurses.h>
#include <string>

std::string Display::format_cmd_status(CmdStatusObject& cmd_status){

	std::string cmd_str;

	if(cmd_status.success){
		cmd_str += "success : ";
	} else {
		cmd_str += "failed : ";
	}

	switch (cmd_status.cmd_type)
	{
	case CmdType::write:
			cmd_str += "write ";
		break;

	case CmdType::read:
			cmd_str += "read ";
		break;

	case CmdType::quit:
			cmd_str += "quit ";
		break;
	
	case CmdType::null:
			cmd_str += "null ";
		break;
	
	}

	return cmd_str;

}

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

void Display::render_cmd_status(CmdStatusObject& cmd_status){

	std::string status_text = format_cmd_status(cmd_status);

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

}

