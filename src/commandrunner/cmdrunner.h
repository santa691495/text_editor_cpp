#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
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
		std::unordered_map<std::string, std::function<void(CommandObject& cmd)> > handlers;
	
	public:
	
		CommandRunner(FileManager& fm, GapBuffer& gb, bool& run);	
		bool is_cmd_valid(CommandObject& cmd);
		bool register_cmd(CommandObject& cmd);
};

#endif //COMMAND_RUNNER
