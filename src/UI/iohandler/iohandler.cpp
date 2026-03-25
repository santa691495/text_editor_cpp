#include "iohandler.h"
#include <ncurses.h>
#include <string>
#include <sstream>

#define CTRL(k) ((k) & 0x1f)	
IOHandler::IOHandler(){
	buffer_str.reserve(2000);
	cmd_str.reserve(2000);
}

void IOHandler::handle_input(){
	
	char input_ch;
	bool cmd_mode;
	//stops when input is timed out
	while(input_ch = getch()){
		buffer_str.push_back(input_ch);

		if(input_ch == CTRL('c')) cmd_mode = true;

		if(cmd_mode){
			if(input_ch = '\n'){
				cmd_mode = false;
				break;
			}
			cmd_str.push_back(input_ch);
		}
	}

}

std::string IOHandler::get_cmd_str(){
	return cmd_str;
}

std::string IOHandler::get_buffer_str(){
	return buffer_str;
}







