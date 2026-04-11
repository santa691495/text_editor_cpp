#include "gtest/gtest.h"
#include <ncurses.h>
#include "display.h"

//Manual testing for Display

TEST(Display, ManualCommandMode){
    initscr();

    Display display_handler;
    display_handler.render_cmd_mode();

    printw("%s", "This Must Be somewhere in the middle !");
    refresh();

    getch();
    getch();

    clear();
    mvprintw(0,0, "Test passed? y/n:");
    refresh();
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

    clear();
    endwin();

    ASSERT_EQ(input, 'y');
}

TEST(Display, MoveCursor){
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    Display display_handler;

    clear();
    printw("%s", "This is sample text for Cursor movement test");
    refresh();

    for(int i = 0; i < 10; ++i){
        int in = getch();

        if(in == KEY_LEFT){
            int curs_y, curs_x;

            getyx(stdscr, curs_y, curs_x);

            move(curs_y, curs_x-1);
            refresh();

        } else if (in == KEY_RIGHT){
            int curs_y, curs_x;

            getyx(stdscr, curs_y, curs_x);

            move(curs_y, curs_x+1);
            refresh();
        } else {
            break;
        }
    }

    clear();
    mvprintw(0,0, "Test passed? y/n:");
    refresh();
    int input = getch();

    endwin();

    ASSERT_EQ(input, 'y');
}
