#include <ncurses.h>
#include "gtest/gtest.h"
#include "iohandler.h"

TEST(IoHandler, GetInputChar){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    auto input_event = io_handler.get_input();

    endwin();

    ASSERT_EQ(input_event.input_ch, 'a');
    ASSERT_EQ(input_event.type, InputType::character);
}

TEST(IoHandler, GetInputCtrl){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    auto input_event = io_handler.get_input();

    endwin();

    ASSERT_EQ(input_event.input_ch, CTRL('c'));
    ASSERT_EQ(input_event.type, InputType::ctrl);
}

TEST(IoHandler, GetInputArrow){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    auto input_event = io_handler.get_input();

    endwin();

    ASSERT_EQ(input_event.input_ch, KEY_UP);
    ASSERT_EQ(input_event.type, InputType::arrow_up);
}

TEST(IoHandler, GetInputEnter){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    auto input_event = io_handler.get_input();

    endwin();

    ASSERT_EQ(input_event.input_ch, '\n');
    ASSERT_EQ(input_event.type, InputType::enter);
}

TEST(IoHandler, GetInputBackspace){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    auto input_event = io_handler.get_input();

    endwin();

    ASSERT_EQ(input_event.input_ch, KEY_BACKSPACE);
    ASSERT_EQ(input_event.type, InputType::backspace);
}

