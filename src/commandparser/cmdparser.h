#include <string>
#include <sstream>
#include <vector>
#include "cmd_obj.h"

#ifndef COMMAND_PARSER
#define COMMAND_PARSER

class CommandParser {
	
	public:
		CommandObject parse(std::string command);
};

#endif //COMMAND_PARSER
