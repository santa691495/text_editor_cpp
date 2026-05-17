#ifndef CMD_TYPE
#define CMD_TYPE
/*
 	Cmdtype

	object used for diagnostics that contains constants related to the type 
	of command runner operation



*/
enum class CmdType { write_new, write_exists, read, quit, null };

#endif 
