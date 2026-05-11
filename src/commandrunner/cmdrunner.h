#include <string>
#include <functional>
#include <unordered_map>
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

		//to relate command type to lambda function wrapping the class method
		std::unordered_map<std::string, std::function<CmdStatusObject(CommandObject& cmd)>> handlers;
	
	public:
		FileManager get_fm();
		GapBuffer get_gb();
	
		CommandRunner(FileManager& fm, GapBuffer& gb, bool& run);	
		CmdStatusObject run(CommandObject& cmd);
};

#endif //COMMAND_RUNNER
