#include "cmdtype.h"

#ifndef CMD_STATUS_OBJECT
#define CMD_STATUS_OBJECT


/*
	CmdStatusObject	

	object containing diagnostic data related to a command
	executed by a CommandRunner object.

 
*/

struct CmdStatusObject {
	CmdType cmd_type;
	bool success;

	CmdStatusObject(CmdType type, bool state): cmd_type(type), success(state) {}
};

#endif 
