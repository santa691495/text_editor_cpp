#include "iohandler.h"
#include "inputtype.h"
#include "inputevent.h"
#include <ncurses.h>

#define CTRL(k) ((k) & 0x1f)

InputEvent IOHandler::get_input() {

	int ch = getch();
	InputEvent input;
	input.input_ch = ch;

	switch (ch) {
	case CTRL('c'):
			input.type = InputType::ctrl;
		break;

	case KEY_ENTER:
			input.type = InputType::enter;
		break;
	
	case KEY_BACKSPACE:
			input.type = InputType::backspace;
		break;

	case KEY_UP:
			input.type = InputType::arrow_right;
		break;
		
	case KEY_DOWN:
			input.type = InputType::arrow_right;
		break;

	case KEY_LEFT:
			input.type = InputType::arrow_right;
		break;

	case KEY_RIGHT:
			input.type = InputType::arrow_right;
		break;
	
	default:
			input.type = InputType::character;
		break;
	}

	return input;
}



