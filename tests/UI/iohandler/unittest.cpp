#include <ncurses.h>
#include "gtest/gtest.h"
#include "inputtype.h"
#include "iohandler.h"


TEST(IoHandler, GetInputChar){
    IOHandler io_handler;

    initscr();
    raw();
    keypad(stdscr, TRUE);

    InputEvent test_input = io_handler.get_input('a');

    endwin();

    ASSERT_EQ(test_input.type, InputType::character);
    ASSERT_EQ(test_input.input_ch, 'a');
}

TEST(IoHandler, GetInputCtrl){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    InputEvent test_input = io_handler.get_input(CTRL('c'));

    endwin();
    
    ASSERT_EQ(test_input.type, InputType::ctrl);
}

TEST(IoHandler, GetInputArrow){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    printw("%s", "Press 'arrow-up' ");
    refresh();

    InputEvent test_input = io_handler.get_input(KEY_UP);

    endwin();
    
    ASSERT_EQ(test_input.type, InputType::arrow_up);
    ASSERT_EQ(test_input.input_ch, KEY_UP); 
}

TEST(IoHandler, GetInputEnter){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    InputEvent test_input = io_handler.get_input('\n');

    endwin();

    ASSERT_EQ(test_input.type, InputType::enter);
    ASSERT_EQ(test_input.input_ch, '\n');
}

TEST(IoHandler, GetInputBackspace){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    InputEvent test_input = io_handler.get_input(KEY_BACKSPACE);

    endwin();

    ASSERT_EQ(test_input.type, InputType::backspace);
    ASSERT_EQ(test_input.input_ch, KEY_BACKSPACE);
}


