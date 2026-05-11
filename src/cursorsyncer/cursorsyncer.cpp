#include "cursorsyncer.h"
#include "display.h"
#include "gapbuffer.h"

void CursorSyncer::move_startln_down(){
    if(gbuffer.move_startln_down()){
        display.move_cursor_startln_down();
    }
}

void CursorSyncer::move_startln_up(){
    if(gbuffer.move_startln_up()){
        display.move_cursor_startln_up();
    }
}

void CursorSyncer::move_left(){
    if(!gbuffer.is_at_line_start()){
        display.move_cursor_left();
        gbuffer.move_left();
    }
}

void CursorSyncer::move_right(){
    if(!gbuffer.is_at_line_edge()){
        display.move_cursor_right();
        gbuffer.move_right();
    }
}   

void CursorSyncer::calibrate_startln_backspace(){
    display.move_cursor_startln_up();
    while(!gbuffer.is_at_line_start()){
        gbuffer.move_left();
    }
}

void CursorSyncer::calibrate_new_buffer(){
    move(0,0);
    gbuffer.move_to_start();   
}