#include <string>

#ifndef COMMAND_OBJECT
#define COMMAND_OBJECT
/*
CommandObject

	primary object interpreted by Command Runner for
	command execution that contains the
	type (std::string) of the command and the arguments
	(std::vector<std::string>) of the command. 


*/
struct CommandObject {
	std::string type;
	std::vector<std::string> args;
};

#endif //COMMAND_OBJECT

