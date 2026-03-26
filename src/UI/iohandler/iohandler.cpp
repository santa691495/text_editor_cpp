#include "iohandler.h"
#include "cmdtype.h"
#include "cmdstatus.h"
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

	input_ch = getch();

	if(input_ch == ERR){
		return;
	}
	
	if(cmd_mode){
		if(input_ch == '\n'){
			cmd_mode = false;
			return;
		}
		cmd_str.push_back(input_ch);
		return;
	}

	if(input_ch == CTRL('e')){
		cmd_mode = true;
		return;
	}	

	buffer_str.push_back(input_ch);
}

std::string IOHandler::get_cmd_str(){
	return cmd_str;
}

std::string IOHandler::get_buffer_str(){
	return buffer_str;
}	

//enough for now, include more info about the commands once 
//the text editor's core features work
std::string IOHandler::parse_cmd_status(CmdStatusObject cmd_status){
	std::string type_string;
	std::string success_string;
	
	if(cmd_status.success){
		success_string = "command success : ";
	} else {
		success_string = "command failed : ";
	}
	
	if(cmd_status.cmd_type == CmdType::write){
		type_string = "write file";
	} else if(cmd_status.cmd_type == CmdType::read){
		type_string = "read file";
	} else if(cmd_status.cmd_type == CmdType::quit){
		type_string = "exit";
	}
	
	std::string cmd_status_string = success_string + type_string;
	return cmd_status_string;
}

bool IOHandler::is_cmd_mode(){
	return cmd_mode;
}





