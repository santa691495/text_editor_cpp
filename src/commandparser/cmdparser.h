#include <string>
#include <sstream>
#include <vector>
#include "cmd_obj.h"
/*	
	Command parser transforms I/O input starting with ':'
	character. 

	responsiblity: Recieving strings from I/O,
	processing the contents of the strings, outputting
	a CommandParser Object.

	FLOW

Recieve string
|
|	"o myfile.txt"
V
Parse the string
|
|	"o", "myfile.txt"
V
Determine the command object attributes
|
|	type=open_file; parameter=myfile.txt	
V
Return the cmd object
|
|
*

Q: Do we do everything in a single method? 
A: We can split them up into multiple methods:

	- parsing (splitting up the type and param ONLY)
	- pass the values onto the make
*/

#ifndef COMMAND_PARSER
#define COMMAND_PARSER

class CommandParser {
	
	public:
		CommandObject parse(std::string command);
};

#endif //COMMAND_PARSER
