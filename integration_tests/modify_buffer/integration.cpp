#include "gtest/gtest.h"
#include <ncurses.h>
#include "display.h"
#include "inputtype.h"
#include "iohandler.h"
#include "cmdrunner.h"
#include "cmdparser.h"
#include "gapbuffer.h"
#include "cursorsyncer.h"
#include "editorstate.h"
#include <string>
#include <vector>

TEST(ModifyBuffer, InsertOnly){
	// === setup ======================
	initscr();
	keypad(stdscr, TRUE);
	raw();	

	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "Copy This:";
	std::string expected_str = "Copy This:Copy This";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}

	display_handler.render_buffer(init_buffer_str);
	std::string insert_str = "Copy This";

	for(char& ch : insert_str){
		ungetch(ch);
		InputEvent input = io_handler.get_input();

		EXPECT_EQ(input.input_ch, ch);
		EXPECT_EQ(input.type, InputType::character);

		if(input.type == InputType::character){
			gap_buffer.insert(input.input_ch);
		}
		
		std::string buffer_str = gap_buffer.get_text();
		display_handler.render_buffer(buffer_str);
	} 

	// === get internal buffer output ====
	move(0,0);

	char buffer_internal[50];
	innstr(buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);

	// === teardown ======================

	endwin();
	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}
//FIXME
TEST(ModifyBuffer, MoveLeftAndInsert){
	// === setup ======================
	initscr();
	keypad(stdscr, TRUE);
	raw();	

	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "MoveLeftThenInsertA";
	std::string expected_str = "MoveLeftThenInsertAA";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}

	std::vector<int> input_chars = {KEY_LEFT, 'A'};

	display_handler.render_buffer(init_buffer_str);

	for(int& ch : input_chars){
		ungetch(ch);
		InputEvent input = io_handler.get_input();

		if(input.type == InputType::character){
			gap_buffer.insert(input.input_ch);
		} else if (input.type == InputType::arrow_left){
			display_handler.move_cursor_left();
			gap_buffer.move_left();
		}

		std::string buffer_str = gap_buffer.get_text();
		display_handler.render_buffer(buffer_str);
	}

	// === get internal buffer output ====
	move(0,0);

	char buffer_internal[50];
	innstr(buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);

	// === teardown ======================

	endwin();

	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}

TEST(ModifyBuffer, MoveRightAndInsert){
	// === setup ======================
	initscr();
	keypad(stdscr, TRUE);
	raw();	

	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "MoveRightThenInsertA ";
	std::string expected_str = "MoveRightThenInsertA A";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}


	std::vector<int> input_chars = {KEY_RIGHT, 'A'};

	display_handler.render_buffer(init_buffer_str);

	for(int& ch : input_chars){
		ungetch(ch);
		InputEvent input = io_handler.get_input();

		if(input.type == InputType::character){
			gap_buffer.insert(input.input_ch);
		} else if (input.type == InputType::arrow_right){
			display_handler.move_cursor_right();
			gap_buffer.move_right();
		}

		std::string buffer_str = gap_buffer.get_text();
		display_handler.render_buffer(buffer_str);
	}

	// === get internal buffer output ====
	move(0,0);

	char buffer_internal[50];
	innstr(buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);

	// === teardown ======================
	endwin();

	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}

TEST(ModifyBuffer, Backspace){
	// === setup ======================
	initscr();
	keypad(stdscr, TRUE);
	raw();	

	IOHandler io_handler;
	GapBuffer gap_buffer;
	Display display_handler;

	std::string init_buffer_str = "DeleteAllOfMe";
	std::string expected_str = "";

	for(char& ch : init_buffer_str){
		gap_buffer.insert(ch);
	}

	display_handler.render_buffer(init_buffer_str);

	for(char& ch : init_buffer_str){
		ungetch(KEY_BACKSPACE);
		InputEvent input = io_handler.get_input();

		if (input.type == InputType::backspace){
			gap_buffer.backspace();
		}

		std::string buffer_str = gap_buffer.get_text();
		display_handler.render_buffer(buffer_str);
	}

	// === get internal buffer output ====
	move(0,0);

	char buffer_internal[50];
	innstr(buffer_internal, expected_str.size());

	std::string buffer_internal_stdstr(buffer_internal);

	// === teardown ======================
	endwin();

	// ===================================

	ASSERT_EQ(buffer_internal_stdstr, expected_str);
}

TEST(ModifyBuffer, InsertMoveUpInsert){
 //SETUP -----------------------	
	std::string buffer_str = "A \n\n\nBCD \n EF\n";
	std::string expected_buffer_str = "A \n\n\nBCD \n!!!!! EF\n!!!!!";

    initscr();
    raw();
    keypad(stdscr, TRUE);

    EditorState editor_state;

    Display display_handler;
    IOHandler io_handler;
    GapBuffer gbuffer;
    FileManager filemanager(""); //we do not need a test file in this test
    
    CommandRunner cmd_runner(filemanager, gbuffer,editor_state.running);
    CommandParser cmd_parser;	

	CursorSyncer cursor_syncer(gbuffer, display_handler);

    //simulation input
	std::string input_str = "!!!!!";
    std::vector<InputEvent>  test_inputs;
	for(char ch : input_str){
		test_inputs.push_back({InputType::character, ch});
	}

    test_inputs.push_back({InputType::arrow_up, 'c'});

	for(char ch : input_str){
		test_inputs.push_back({InputType::character, ch});
	}

    test_inputs.push_back({InputType::ctrl, 'c'});
    test_inputs.push_back({InputType::character, 'q'});
    test_inputs.push_back({InputType::enter, '\n'});

    size_t input_counter = 0;
    //PROCESS ----------------------

     while(editor_state.running){

        std::string cmd_input_str;

        if(editor_state.cmd_mode){
            display_handler.render_cmd_mode();
        }

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
				gbuffer.insert('\n');
                break;

            case InputType::unknown:

                break;
            }
            
        }
    }

    endwin();

}

TEST(ModifyBuffer, InsertMoveDownInsert){

}	

TEST(ModifyBuffer, InsertUpInsertDownInsert){

}