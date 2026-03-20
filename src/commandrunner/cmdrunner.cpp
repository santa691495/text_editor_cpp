#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include "cmd_obj.h"
#include "gapbuffer.h"
#include "filemanager.h"
#include "cmdrunner.h"

//TODO: add to handler functions
//the other operations needed to complete 
//the action (like UI class methods that switch the ui
const std::vector<std::string> CommandRunner::cmd_list = {"w", "o", "q"};

CommandRunner::CommandRunner(FileManager& fm, GapBuffer& gb, bool& run):
	filemanager(fm),
	gapbuffer(gb),
	running(run)
{
	handlers["w"] = [this](CommandObject& cmd){
		filemanager.write_file(cmd.args[0], gapbuffer);
	};

	handlers["o"] = [this](CommandObject& cmd){
		gapbuffer = filemanager.read_file(cmd.args[0]);
	};		

	handlers["q"] = [this](CommandObject& cmd){
		running = false;
	};

}

bool CommandRunner::is_cmd_valid(CommandObject& cmd){
	for(size_t i = 0; i < cmd_list.size(); ++i){
		if(cmd.type == cmd_list[i]) return true;
	}

	return false;
}

bool CommandRunner::register_cmd(CommandObject& cmd){
	
	if(!is_cmd_valid(cmd)){
		return false;
	}

	handlers[cmd.type];
	return true;
}


