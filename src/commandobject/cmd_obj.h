#include <string>

#ifndef COMMAND_OBJECT
#define COMMAND_OBJECT

struct CommandObject {
	std::string type;
	std::vector<std::string> args;
};

#endif //COMMAND_OBJECT

