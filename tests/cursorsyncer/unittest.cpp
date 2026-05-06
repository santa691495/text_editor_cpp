#include "gapbuffer.h"
#include "display.h"
#include <ncurses.h>
#include "gtest/gtest.h"
#include "cursorsyncer.h"

TEST(CursorSync, CalibrateNewBuffer){
    initscr();  

    GapBuffer test_gbuffer;
    Display test_display;
    CursorSyncer test_cursor_syncer(test_gbuffer, test_display);

    std::string init_buffer_str = "QWE\nRTY";
    std::string expected_buffer_str = "!QWE\nRTY";
    int expected_new_posx = 0;
    int expected_new_posy = 0;

    for(char& ch : init_buffer_str){
        test_gbuffer.insert(ch);
    }

    test_cursor_syncer.calibrate_new_buffer();

    int new_posx, new_posy;
    getyx(stdscr, new_posy, new_posx);

    test_gbuffer.insert('!');

    endwin();   

    ASSERT_EQ(test_gbuffer.get_text(), expected_buffer_str);
    ASSERT_EQ(new_posx, expected_new_posx);
    ASSERT_EQ(new_posy, expected_new_posy);

}

TEST(CursorSync, MoveStartlnUp){
    initscr();  

    GapBuffer test_gbuffer;
    Display test_display;
    CursorSyncer test_cursor_syncer(test_gbuffer, test_display);

    std::string init_buffer_str = "QWE\nRTY";
    std::string expected_buffer_str = "!QWE\nRTY";
    int expected_new_posx = 0;
    int expected_new_posy = 0;

    for(char& ch : init_buffer_str){
        test_gbuffer.insert(ch);
    }

    move(1,3);

    test_cursor_syncer.move_startln_up();

    int new_posx, new_posy;
    getyx(stdscr, new_posy, new_posx);

    test_gbuffer.insert('!');

    endwin();   

    ASSERT_EQ(test_gbuffer.get_text(), expected_buffer_str);
    ASSERT_EQ(new_posx, expected_new_posx);
    ASSERT_EQ(new_posy, expected_new_posy);
}

TEST(CursorSync, MoveStartlnDown){
    initscr();      

    GapBuffer test_gbuffer;
    Display test_display;
    CursorSyncer test_cursor_syncer(test_gbuffer, test_display);

    std::string init_buffer_str = "QWE\nRTY";
    std::string expected_buffer_str = "QWE\n!RTY";
    int expected_new_posx = 0;
    int expected_new_posy = 1;

    for(char& ch : init_buffer_str){
        test_gbuffer.insert(ch);
    }   

    for(char& ch : init_buffer_str){
        test_gbuffer.move_left();
    }

    move(0,0);

    test_cursor_syncer.move_startln_down();

    int new_posx, new_posy;
    getyx(stdscr, new_posy, new_posx);

    test_gbuffer.insert('!');

    endwin();   


    ASSERT_EQ(test_gbuffer.get_text(), expected_buffer_str);
    ASSERT_EQ(new_posx, expected_new_posx);
    ASSERT_EQ(new_posy, expected_new_posy);
    
}

TEST(CursorSync, MoveLeft){
    initscr();      

    GapBuffer test_gbuffer;
    Display test_display;
    CursorSyncer test_cursor_syncer(test_gbuffer, test_display);

    std::string init_buffer_str = "QWE\nRTY";
    std::string expected_buffer_str = "QWE\nRT!Y";
    int expected_new_posx = 2;
    int expected_new_posy = 1;

    for(char& ch : init_buffer_str){
        test_gbuffer.insert(ch);
    }   

    move(1,3);

    test_cursor_syncer.move_left();

    int new_posx, new_posy;
    getyx(stdscr, new_posy, new_posx);

    test_gbuffer.insert('!');

    endwin();   

    EXPECT_EQ(new_posy, expected_new_posy);
    EXPECT_EQ(new_posx, expected_new_posx);
    ASSERT_EQ(test_gbuffer.get_text(), expected_buffer_str);
}

TEST(CursorSync, MoveRight){
    initscr();      

    GapBuffer test_gbuffer;
    Display test_display;
    CursorSyncer test_cursor_syncer(test_gbuffer, test_display);

    std::string init_buffer_str = "QWE\nRTY";
    std::string expected_buffer_str = "Q!WE\nRTY";
    int expected_new_posx = 1;
    int expected_new_posy = 0;

    for(char& ch : init_buffer_str){
        test_gbuffer.insert(ch);
    }   

    for(char& ch : init_buffer_str){
        test_gbuffer.move_left();
    }   

    move(0,0);

    test_cursor_syncer.move_right();

    int new_posx, new_posy;
    getyx(stdscr, new_posy, new_posx);

    test_gbuffer.insert('!');

    endwin();   

    ASSERT_EQ(test_gbuffer.get_text(), expected_buffer_str);
    ASSERT_EQ(new_posx, expected_new_posx);
    ASSERT_EQ(new_posy, expected_new_posy);
}   