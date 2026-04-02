#include "iohandler.h"
#include "cmdtype.h"
#include "cmdstatus.h"
#include <ncurses.h>
#include <string>
#include <sstream>

#define CTRL(k) ((k) & 0x1f)

char IOHandler::get_input(){

	char input = getch();
	return input;
}



