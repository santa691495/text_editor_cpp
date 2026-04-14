#include "display.h"
#include "cmdstatus.h"
#include <ncurses.h>
#include <string>

Display::Display(){

	int scr_height, scr_width;

	getmaxyx(stdscr, scr_height, scr_width);
		
	int win_height = 1;
	int win_width = scr_width/4;
	
	int start_y = scr_height - 3;
	int start_x = scr_width / 2 - (win_width / 2);

	cmd_status_win = newwin(win_height, win_width, start_y, start_x);
}

void Display::render_cmd_mode(){
	
	clear();

	//calculate bottom
	int scr_height, scr_width;
	getmaxyx(stdscr, scr_height, scr_width);

	move(scr_height/2, scr_width/2);
	refresh();
}

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

void Display::save_cursor_pos(){
	getyx(stdscr, curs_saved_y, curs_saved_x);
}

void Display::fix_cursor_pos(){
	move(curs_saved_y, curs_saved_x);
	refresh();
}

void Display::render_buffer(std::string& buffer_text){
	clear();

	const char* c_text = buffer_text.c_str();
	printw("%s", c_text);

	refresh();
}

void Display::render_cmd_status(CmdStatusObject& cmd_status){
	
	wclear(cmd_status_win);

	std::string status_text = format_cmd_status(cmd_status);
	
	const char* c_text = status_text.c_str();	

	wattron(cmd_status_win, A_STANDOUT);
	wprintw(cmd_status_win,"%s", c_text);
	wattroff(cmd_status_win, A_STANDOUT);

	wrefresh(cmd_status_win);

}

Display::~Display(){
	delwin(cmd_status_win);
}

void Display::move_cursor_left(){
	int curs_y, curs_x;

	getyx(stdscr, curs_y, curs_x);

	move(curs_y, curs_x-1);
	refresh();
}

void Display::move_cursor_right(){
	int curs_y, curs_x;

	getyx(stdscr, curs_y, curs_x);

	move(curs_y, curs_x+1);
	refresh();
}



