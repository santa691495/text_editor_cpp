#include "gapbuffer.h"
#include "display.h"    

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
};
