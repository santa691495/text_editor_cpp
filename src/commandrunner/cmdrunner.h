#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <utility>
#include "cmdtype.h"
#include "cmdstatus.h"
#include "cmd_obj.h"
#include "gapbuffer.h"
#include "filemanager.h"
/*
Command Runner
	Resonsible for interpreting CommandObject objects to call methods
	related to the currently bound gapbuffer and filemanager to the IOHandler
	object, and manipulate state related to the program (e.g. whether the program is running
	or not).		
*/

#ifndef COMMAND_RUNNER
#define COMMAND_RUNNER

class CommandRunner {
	private:
		FileManager& filemanager;
		GapBuffer& gapbuffer;
		bool& running;

		static const std::vector<std::string> cmd_list;

		//to relate command type to lambda function wrapping the class method
		std::unordered_map<std::string, std::function<CmdStatusObject(CommandObject& cmd)>> handlers;
	
	public:
		FileManager get_fm();
		GapBuffer get_gb();
		std::vector<std::string> get_cmd_list();
	
		CommandRunner(FileManager& fm, GapBuffer& gb, bool& run);	
		CmdStatusObject run(CommandObject& cmd);
};

#endif //COMMAND_RUNNER
