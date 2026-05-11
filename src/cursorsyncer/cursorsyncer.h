#include "gapbuffer.h"
#include "display.h"    

#ifndef CURSOR_SYNCER
#define CURSOR_SYNCER

/*
    Cursor Syncer 

    Manages the synchronization of the 
    internal buffer gap and the cursor on
    the screen 
*/

class CursorSyncer {

    private:
        GapBuffer& gbuffer;
        Display& display;

    public:

        CursorSyncer(GapBuffer& gb, Display& dspl):
        gbuffer(gb),
        display(dspl)
        {} 

        void move_startln_down();
        void move_startln_up();
        void move_left();
        void move_right();
        void calibrate_startln_backspace();
        void calibrate_new_buffer();
};

#endif 