#include <functional>
#include <unordered_map>
#include "cmd_obj.h"
#include "gapbuffer.h"
#include "filemanager.h"
#include "cmdrunner.h"
#include "cmdtype.h"
#include "cmdstatus.h"
#include "filestatus.h"

FileManager CommandRunner::get_fm(){
	FileManager fm = filemanager;
	return fm;
}

GapBuffer CommandRunner::get_gb(){
	GapBuffer gb = gapbuffer;
	return gb;
}

CommandRunner::CommandRunner(FileManager& fm, GapBuffer& gb, bool& run):
	filemanager(fm),
	gapbuffer(gb),
	running(run)
{
	handlers["w"] = [this](CommandObject& cmd) -> CmdStatusObject{	
		if(cmd.args.empty()){
			cmd.args.push_back(filemanager.get_current_file().string());
		}
		FileStatus file_status = filemanager.write_file(cmd.args[0], gapbuffer); 

		if(file_status == FileStatus::EXISTS){
			return CmdStatusObject(CmdType::write_exists, true);
		} else if(file_status == FileStatus::FAIL){
			return CmdStatusObject(CmdType::null, false);
		} else {
			return CmdStatusObject(CmdType::write_new, true);
		} 

	};

	handlers["o"] = [this](CommandObject& cmd)-> CmdStatusObject {

		FileStatus file_status;
		if(cmd.args.empty()){
			 file_status = filemanager.read_file(filemanager.get_current_file(), gapbuffer);
		} else {
			file_status = filemanager.read_file(cmd.args[0], gapbuffer);
		}

		if(file_status == FileStatus::EXISTS){
			return CmdStatusObject(CmdType::read, true);
		} else {
			return CmdStatusObject(CmdType::read, false);
		}
	};		

	handlers["q"] = [this](CommandObject& cmd) -> CmdStatusObject{
		bool quit_success = running;
		running = false;

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


