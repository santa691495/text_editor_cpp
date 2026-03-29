#include <string>
#include <sstream>
#include <vector>
#include "cmd_obj.h"

/* 
 
 CommandParser

 	Responsible for converting command strings in the form 
	of a std::string into a CommandObject object.
 
 */
#ifndef COMMAND_PARSER
#define COMMAND_PARSER

class CommandParser {
	
	public:
		CommandObject parse(std::string command);
};

#endif //COMMAND_PARSER
