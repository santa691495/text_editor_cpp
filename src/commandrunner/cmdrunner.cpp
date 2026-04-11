#include <string>
#include <functional>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <utility>
#include "cmd_obj.h"
#include "gapbuffer.h"
#include "filemanager.h"
#include "cmdrunner.h"
#include "cmdtype.h"
#include "cmdstatus.h"

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
	handlers["w"] = [this](CommandObject& cmd) -> CmdStatusObject{	
		if(cmd.args.empty()){
			cmd.args[0] = filemanager.get_current_file();
		}
		bool is_written = filemanager.write_file(cmd.args[0], gapbuffer);

		CmdStatusObject write_status(CmdType::write, is_written);
		return write_status;
	};

	handlers["o"] = [this](CommandObject& cmd)-> CmdStatusObject {

		bool is_read;
		if(cmd.args.empty()){
			is_read = filemanager.read_file(filemanager.get_current_file(), gapbuffer);
		} else {
			is_read = filemanager.read_file(cmd.args[0], gapbuffer);
		}
		
		CmdStatusObject read_status(CmdType::read, is_read);
		return read_status;
	};		

	handlers["q"] = [this](CommandObject& cmd) -> CmdStatusObject{
		bool quit_success;
		if(!running){	
			quit_success = false;
		}	else {
			running = false;
			quit_success = true;
		}

		CmdStatusObject quit_status(CmdType::quit, quit_success);
		return quit_status;
	};
}

CmdStatusObject CommandRunner::run(CommandObject& cmd){
	auto it = handlers.find(cmd.type);

	if(it != handlers.end()){
		return it->second(cmd);
	}
	
	CmdStatusObject failed(CmdType::null, false);
	
	return failed;
}	


