#include "cmdruntype.h"

#ifndef CMD_RUN_STATUS
#define CMD_RUN_STATUS
	
struct CmdStatusObject {
	CmdRunType cmd_type;
	bool success;

	CmdStatusObject(CmdRunType cmd_type, bool success);
};

#endif 
