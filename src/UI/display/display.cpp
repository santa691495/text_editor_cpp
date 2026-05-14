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

void Display::render_cmd_mode(std::string& buffer_text){
	clear();

	int scr_height, scr_width;
	getmaxyx(stdscr, scr_height, scr_width);	

	move(scr_height/2, scr_width/2);

	const char* c_text = buffer_text.c_str();
	printw("%s", c_text);

	refresh();
}

void Display::render_cmd_mode(){
	clear();

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
			cmd_str += "unknown ";
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

void Display::render_cmd_status(CmdStatusObject cmd_status){
	wclear(cmd_status_win);

	std::string status_text = format_cmd_status(cmd_status);
	
	const char* c_text = status_text.c_str();	

	wattron(cmd_status_win, A_STANDOUT);
	wprintw(cmd_status_win,"%s", c_text);
	wattroff(cmd_status_win, A_STANDOUT);

	wrefresh(cmd_status_win);
}

void Display::render_cmd_status(){
	std::string status_text = format_cmd_status(saved_cmd_status);
	const char* c_text = status_text.c_str();	

	int max_y;
	max_y = getmaxy(stdscr);

	move(max_y-1, 0);

	clrtoeol();
	attron(A_STANDOUT);
	printw("%s", c_text);
	attroff(A_STANDOUT);

	refresh();
}

void Display::save_cmd_status(CmdStatusObject cmd_status){
	saved_cmd_status = cmd_status;
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

bool Display::is_cursor_height_max(){
	int current_y, current_x;
	getyx(stdscr, current_y, current_x);

	int max_y = getmaxy(stdscr);

	if(current_y == max_y){
		return true;
	} 

	return false;
}

bool Display::is_cursor_height_min(){
	int current_y, current_x;
	getyx(stdscr, current_y, current_x);

	if(current_y == 0){
		return true;
	} 

	return false;
}

void Display::move_cursor_startln_up(){
	if(is_cursor_height_min()){
		return;
	}

	int curs_y, curs_x;
	getyx(stdscr, curs_y, curs_x);

	move(curs_y-1, 0);
}

void Display::move_cursor_startln_down(){
	if(is_cursor_height_max()){
		return;
	}

	int curs_y, curs_x;
	getyx(stdscr, curs_y, curs_x);

	move(curs_y+1, 0);
}





