#include "gapbuffer.h"
#include "display.h"
#include <ncurses.h>
#include "gtest/gtest.h"
#include "cursorsyncer.h"

TEST(CursorSync, MoveStartlnDownNewLinesStacked){
    initscr();      

    GapBuffer test_gbuffer;
    Display test_display;
    CursorSyncer test_cursor_syncer(test_gbuffer, test_display);

    std::string init_buffer_str = "QWE\n\n\n\n\n\n\nRTY";
    std::string expected_buffer_str = "QWE\n\n\n!\n\n\n\nRTY";
    int expected_new_posx = 0;
    int expected_new_posy = 3;

    for(char& ch : init_buffer_str){
        test_gbuffer.insert(ch);
    }   

    for(char& ch : init_buffer_str){
        test_gbuffer.move_left();
    }

    move(0,0);

    test_cursor_syncer.move_startln_down();
    test_cursor_syncer.move_startln_down();
    test_cursor_syncer.move_startln_down();

    int new_posx, new_posy;
    getyx(stdscr, new_posy, new_posx);

    test_gbuffer.insert('!');

    endwin();   

    ASSERT_EQ(test_gbuffer.get_text(), expected_buffer_str);
    ASSERT_EQ(new_posx, expected_new_posx);
    ASSERT_EQ(new_posy, expected_new_posy);
}

TEST(CursorSync, MoveStartlnUpNewLinesStacked){
    initscr();  

    GapBuffer test_gbuffer;
    Display test_display;
    CursorSyncer test_cursor_syncer(test_gbuffer, test_display);

    std::string init_buffer_str = "QWE\n\n\n\n\n\n\nRTY";
    std::string expected_buffer_str = "QWE\n\n\n!\n\n\n\nRTY";
    int expected_new_posx = 0;
    int expected_new_posy = 3;

    for(char& ch : init_buffer_str){
        test_gbuffer.insert(ch);
    }

    move(7,4);

    test_cursor_syncer.move_startln_up();
    test_cursor_syncer.move_startln_up();
    test_cursor_syncer.move_startln_up();
    test_cursor_syncer.move_startln_up();

    int new_posx, new_posy;
    getyx(stdscr, new_posy, new_posx);

    test_gbuffer.insert('!');

    endwin();   

    ASSERT_EQ(test_gbuffer.get_text(), expected_buffer_str);
    ASSERT_EQ(new_posx, expected_new_posx);
    ASSERT_EQ(new_posy, expected_new_posy);
}       

TEST(CursorSync, MoveStartlnDownAndUpNewLinesStacked){
    initscr();  

    GapBuffer test_gbuffer;
    Display test_display;
    CursorSyncer test_cursor_syncer(test_gbuffer, test_display);

    std::string init_buffer_str = "QWE\n\n\n\n\n\n\nRTY";
    std::string expected_buffer_str = "!QWE\n\n\n\n\n\n\nRTY";
    int expected_new_posx = 0;
    int expected_new_posy = 0;

    for(char& ch : init_buffer_str){
        test_gbuffer.insert(ch);
    }   
    
    for(char& ch : init_buffer_str){
        test_gbuffer.move_left();
    }
    move(0,0);  

    int start_x, start_y;
    getyx(stdscr, start_y, start_x);
    EXPECT_EQ(start_y, 0);
    EXPECT_EQ(start_x, 0);

    test_cursor_syncer.move_startln_down();
    test_cursor_syncer.move_startln_down();
    test_cursor_syncer.move_startln_up();
    test_cursor_syncer.move_startln_up();

    int new_posx, new_posy;
    getyx(stdscr, new_posy, new_posx);

    test_gbuffer.insert('!');

    endwin();   

    ASSERT_EQ(test_gbuffer.get_text(), expected_buffer_str);
    ASSERT_EQ(new_posx, expected_new_posx);
    ASSERT_EQ(new_posy, expected_new_posy);
}