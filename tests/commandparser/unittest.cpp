#include "gtest/gtest.h"
#include "cmdparser.h"
#include "cmd_obj.h"
#include <string>
#include <vector>
#include <sstream>

TEST(CommandParser, Parse){
	std::string input_cmd = "w myfile.txt";
	
	CommandObject expected_obj;
	expected_obj.type = "w";
	expected_obj.args.push_back("myfile.txt"); 
	
	CommandParser test_parser;
	
	CommandObject output_obj {test_parser.parse(input_cmd)};

	EXPECT_EQ(output_obj.type, expected_obj.type);
	EXPECT_EQ(output_obj.args[0], expected_obj.args[0]);
}
