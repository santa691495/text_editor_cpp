#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include "cmd_obj.h"
#include "gapbuffer.h"
#include "filemanager.h"
#include "cmdrunner.h"

//TODO: add to handler functions
//the other operations needed to complete 
//the action (like UI class methods that switch the ui
const std::vector<std::string> CommandRunner::cmd_list = {"w", "o", "q"};

FileManager CommandRunner::get_fm(){
	FileManager fm = filemanager;
	return fm;
}

GapBuffer CommandRunner::get_gb(){
	GapBuffer gb = gapbuffer;
	return gb;
}

std::vector<std::string> CommandRunner::get_cmd_list(){
	return cmd_list;
}
//FIXME: add error handling for writing and others --> DOING THIS NOW
CommandRunner::CommandRunner(FileManager& fm, GapBuffer& gb, bool& run):
	filemanager(fm),
	gapbuffer(gb),
	running(run)
{
	handlers["w"] = [this](CommandObject& cmd){	
		if(cmd.args.empty()){
			cmd.args[0] = filemanager.get_current_file;
		}
		filemanager.write_file(cmd.args[0], gapbuffer);
	};

	handlers["o"] = [this](CommandObject& cmd){
		filemanager.read_file(cmd.args[0], gapbuffer);
	};		

	handlers["q"] = [this](CommandObject& cmd){
		running = false;
	};

}

//iterates through the handlers
void CommandRunner::run(CommandObject& cmd){
	auto it = handlers.find(cmd.type);

	if(it != handlers.end()){
		it->second(cmd);
	}

	return;
}	


