#include <string>
#include <sstream>
#include <vector>
#include "cmdparser.h"
#include "cmd_obj.h"
	
CommandObject CommandParser::parse(std::string command){
	std::stringstream ss(command);

	std::string type;
	std::vector<std::string> args;
	
	ss >> type;
	std::string param;
	while(ss >> param){
		args.push_back(param);
	}

	CommandObject cmdobj;
	cmdobj.type = type;
	cmdobj.args = args;

	return cmdobj;
}
