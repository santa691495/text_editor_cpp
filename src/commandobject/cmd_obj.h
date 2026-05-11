#include <string>
#include <vector>

#ifndef COMMAND_OBJECT
#define COMMAND_OBJECT
/*
CommandObject

	Contains command information for CommandRunner class
	to digest

*/
struct CommandObject {
	std::string type;
	std::vector<std::string> args;
};

#endif //COMMAND_OBJECT

