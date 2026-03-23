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

//TODO for today: implement error handling then run tests again
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

CommandRunner::CommandRunner(FileManager& fm, GapBuffer& gb, bool& run):
	filemanager(fm),
	gapbuffer(gb),
	running(run)
{
	handlers["w"] = [this](CommandObject& cmd) -> bool {	
		if(cmd.args.empty()){
			cmd.args[0] = filemanager.get_current_file();
		}
		return filemanager.write_file(cmd.args[0], gapbuffer);
	};

	handlers["o"] = [this](CommandObject& cmd)-> bool {
		return filemanager.read_file(cmd.args[0], gapbuffer);
	};		

	handlers["q"] = [this](CommandObject& cmd) -> bool{	
		if(running == false){
			return false;
		}
	
		running = false;
		return true;
	};

}
//TODO: implement error handling then run tests again
bool CommandRunner::run(CommandObject& cmd){
	auto it = handlers.find(cmd.type);

	if(it != handlers.end()){
		return it->second(cmd);
	}

	return false;
}	


