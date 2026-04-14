#include "gtest/gtest.h"
#include <ncurses.h>
#include "display.h"
#include "inputtype.h"
#include "iohandler.h"
#include "cmdrunner.h"
#include "cmdparser.h"
#include "gapbuffer.h"
#include "filemanager.h"
#include "editorstate.h"
#include <string>
#include <filesystem>
#include <fstream>

//TODO: this test should just go to command mode already
// buffer should delete itself once q is entered 
TEST(QuitEditor, QuitEditor){
    //SETUP -----------------------
    initscr();
    raw();
    keypad(stdscr, TRUE);

    EditorState editor_state;

    Display display_handler;
    IOHandler io_handler;
    GapBuffer gbuffer;
    FileManager filemanager("./test_file.txt");
    
    CommandRunner cmd_runner(filemanager, gbuffer,editor_state.running);
    CommandParser cmd_parser;

    //PROCESS ----------------------

     while(editor_state.running){

        std::string cmd_input_str;
        //this while loop should be its own class 

        if(editor_state.cmd_mode){
            display_handler.render_cmd_mode();
        }

        while(editor_state.cmd_mode){
            //this should be its own function ===
            InputEvent input = io_handler.get_input();
            
            if(input.input_ch != '\n'){
                cmd_input_str += input.input_ch;
                continue;
            }

            CommandObject cmd = cmd_parser.parse(cmd_input_str);
            CmdStatusObject cmd_status = cmd_runner.run(cmd);

            editor_state.cmd_mode = false;
            // ===============================
        }

        if(!editor_state.running){
            break;  
        }
        //this while loop should be its own class as well
        while(!editor_state.cmd_mode){
            std::string buffer_text = gbuffer.get_text();   
            display_handler.render_buffer(buffer_text);
            display_handler.fix_cursor_pos();

            InputEvent input = io_handler.get_input();
            //This should be its own function ===
            switch (input.type) {

            case InputType::ctrl:
                editor_state.cmd_mode = true;
                break;

            case InputType::unknown:

                break;
            }
            //============================
        }

    }



    // TEARDOWN --------------------
    clear();
    refresh();
    endwin();

    ASSERT_TRUE(true);
}