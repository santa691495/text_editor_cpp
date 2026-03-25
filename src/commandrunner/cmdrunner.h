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
		
	responsible for interpreting CommandObject objects
	and running commands associated with the command object, such as
	writing, reading, and exiting the editor, to name a few.
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
