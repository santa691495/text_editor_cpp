#include "gtest/gtest.h"
#include <ncurses.h>
#include "display.h"
#include <string>

//Manual testing for Display

TEST(Display, ManualCommandMode){
    initscr();
    
    Display display_handler;
    display_handler.render_cmd_mode();

    //print and check manually if it prints on desired area
    
    printw("%s", "This Must Be somewhere in the middle !");
    refresh();

    getch();

    clear();
    mvprintw(0,0, "Test passed? y/n:");
    char input = getch();
    
    clear();
    refresh();
    endwin();

    ASSERT_EQ(input, 'y');
}

TEST(Display, ManualCommandStatus){
    initscr();

    Display display_handler;
    CmdStatusObject cmd_status(CmdType::write, true);

    display_handler.render_cmd_status(cmd_status);

    getch();

    clear();
    mvprintw(0,0, "Test passed? y/n:");
    refresh();
    char input = getch();

    endwin();

    ASSERT_EQ(input, 'y');
}
