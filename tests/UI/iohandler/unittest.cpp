#include <ncurses.h>
#include "gtest/gtest.h"
#include "iohandler.h"

TEST(IoHandler, GetInputChar){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    printw("%s", "Press 'a' ");
    refresh();

    auto input_event = io_handler.get_input();

    clear();
    refresh();
    endwin();

    ASSERT_EQ(input_event.input_ch, 'a');
    ASSERT_EQ(input_event.type, InputType::character);
}

TEST(IoHandler, GetInputCtrl){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    printw("%s", "Press 'ctrl+c' ");
    refresh();

    auto input_event = io_handler.get_input();
    clear();
    refresh();

    endwin();
    

    ASSERT_EQ(input_event.input_ch, CTRL('c'));
    ASSERT_EQ(input_event.type, InputType::ctrl);
}

TEST(IoHandler, GetInputArrow){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    printw("%s", "Press 'arrow-up' ");
    refresh();

    auto input_event = io_handler.get_input();
    clear();
    refresh();

    endwin();

    ASSERT_EQ(input_event.input_ch, KEY_UP);
    ASSERT_EQ(input_event.type, InputType::arrow_up);
}

TEST(IoHandler, GetInputEnter){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    printw("%s", "Press 'enter' ");
    refresh();

    auto input_event = io_handler.get_input();
    clear();
    refresh();

    endwin();

    ASSERT_EQ(input_event.input_ch, '\n');
    ASSERT_EQ(input_event.type, InputType::enter);
}

TEST(IoHandler, GetInputBackspace){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    printw("%s", "Press 'backspace' ");
    refresh();

    auto input_event = io_handler.get_input();
    clear();
    refresh();
    endwin();

    ASSERT_EQ(input_event.input_ch, KEY_BACKSPACE);
    ASSERT_EQ(input_event.type, InputType::backspace);
}

TEST(IoHandler, GetCmdInput){
    IOHandler io_handler;
    
    initscr();
    raw();
    keypad(stdscr, TRUE);

    printw("%s", "Press 'c' then press enter.");
    refresh();

    WINDOW* cmd_mode_win = newwin(5, 10, 10, 2);
    wmove(cmd_mode_win, 2, 2);
    box(cmd_mode_win, 0 ,0);

    wrefresh(cmd_mode_win);

    int input_c = io_handler.get_cmd_input(cmd_mode_win);
    int input_enter = io_handler.get_cmd_input(cmd_mode_win);

    delwin(cmd_mode_win);
    endwin();

    ASSERT_EQ(input_c, 'c');
    ASSERT_EQ(input_enter, '\n');
}

