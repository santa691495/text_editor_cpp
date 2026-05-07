#include "gapbuffer.h"
#include "display.h"
#include "iohandler.h"
#include "cmdparser.h"
#include "cmdrunner.h"
#include "filemanager.h"
#include "editorstate.h"
#include "cursorsyncer.h"
#include "editorcore.h"


int main () {

    GapBuffer gbuffer;
    FileManager fm;
    IOHandler io;
    CommandParser cmdparser;
    Display dspl;   
    EditorState state;

    //setup
    initscr();
    raw();
    keypad(stdscr, TRUE);

    EditorCore editorcore(dspl, io, cmdparser, fm, gbuffer, state);
    editorcore.run();

    //teardown
    endwin();

    return 0;
}
