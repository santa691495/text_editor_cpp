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

TEST(OpenFile, OpenFile){

    std::filesystem::path target_rel_path = "test_folder/test_file.txt";
    std::filesystem::path target_abs_path = std::filesystem::current_path() / target_rel_path;

    std::ofstream out_test_file(target_rel_path);
    std::string file_text = "This Is The Correct Text!";

    out_test_file << file_text; 
    out_test_file.close();

    initscr();
    raw();
    keypad(stdscr, TRUE);

    EditorState editor_state;

    Display display_handler;
    IOHandler io_handler;
    GapBuffer gbuffer;
    FileManager filemanager("");
    
    CommandRunner cmd_runner(filemanager, gbuffer,editor_state.running);
    CommandParser cmd_parser;

    //simulation input 
    std::vector<InputEvent>  test_inputs;

    test_inputs.push_back({InputType::ctrl, 'c'});
    test_inputs.push_back({InputType::character, 'o'});
    test_inputs.push_back({InputType::character, ' '});

    std::string target_rel_path_str = target_rel_path;
    for(char ch : target_rel_path_str){
        test_inputs.push_back({InputType::character, ch});
    }

    test_inputs.push_back({InputType::enter, '\n'});
    test_inputs.push_back({InputType::ctrl, 'c'});
    test_inputs.push_back({InputType::character, 'q'});
    test_inputs.push_back({InputType::enter, '\n'});

    size_t input_counter = 0;

    //for thy assertion later !!!
    std::string buffer_text_during_test;
    std::filesystem::path current_filepath_during_test = "";
    //=======

    while(editor_state.running){


        if(editor_state.cmd_mode){
            display_handler.render_cmd_mode();
        }
        
        std::string cmd_input_str;
        while(editor_state.cmd_mode){
            
            InputEvent input = test_inputs[input_counter];
            if(input_counter < test_inputs.size()){
                ++input_counter;
            }
            
            if(input.input_ch != '\n'){
                cmd_input_str += input.input_ch;
                continue;
            }

            CommandObject cmd = cmd_parser.parse(cmd_input_str);
            CmdStatusObject cmd_status = cmd_runner.run(cmd);

            editor_state.cmd_mode = false;
        }

        if(!editor_state.running){
            break;  
        }
        
        while(!editor_state.cmd_mode){
            std::string buffer_text = gbuffer.get_text();   
            display_handler.render_buffer(buffer_text);
            display_handler.fix_cursor_pos();

            //simulated input here 
            InputEvent input = test_inputs[input_counter];
            if(input_counter < test_inputs.size()){
                ++input_counter;
            }

            //for thy assertions later !!!
            if(gbuffer.get_text() != ""){
                buffer_text_during_test = gbuffer.get_text();
                current_filepath_during_test = filemanager.get_current_file();
            }

            //This should be its own function ===
            switch (input.type) {

            case InputType::arrow_left:
                display_handler.move_cursor_left();
                display_handler.save_cursor_pos();
                editor_state.cursor_left_next_refresh = true;
                gbuffer.move_left();
                break;

            case InputType::arrow_right:
                display_handler.move_cursor_right();
                display_handler.save_cursor_pos();
                editor_state.cursor_right_next_refresh = true;
                gbuffer.move_right();
                break;

            case InputType::character:
                gbuffer.insert(input.input_ch);
                display_handler.save_cursor_pos();
                break;

            case InputType::backspace:
                gbuffer.backspace();
                display_handler.save_cursor_pos();
                break;

            case InputType::ctrl:
                editor_state.cmd_mode = true;
                break;

            case InputType::enter:
                
                break;

            case InputType::unknown:

                break;
            }
            
        }
    }
    
    endwin();

    //check gapbuffer if correct
    ASSERT_EQ(buffer_text_during_test, file_text);
    ASSERT_EQ(current_filepath_during_test, target_abs_path);
}