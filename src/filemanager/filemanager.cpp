#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include "gapbuffer.h"

FileManager::FileManager(GapBuffer& current_buffer){
	this->current_buffer = current_buffer;
}

std::filesystem::path FileManager::resolve_path(std::filesystem::path filepath){
	if(filepath.is_absolute()){
		return filepath;
	}

	std::filesystem::path resolved = filepath.parent_path() / filepath;
	return resolved;
}

bool FileManager::file_exists(std::filesystem::path filepath){
	filepath = resolve_path(filepath);
		
	if(std::filesystem::exists(filepath)){
		return true;
	}

	return false;
}

void FileManager::write_file(std::filesystem::path filepath){
	filepath = resolve_path(filepath);
	
	std::ofstream outfile(filepath);
	
	if(!outfile){
		std::cerr << "Could not open file\n";
		return;
	}
	outfile << buffer_text;
	outfile.close();
}	


GapBuffer FileManager::read_file(std::filesystem::path filepath){
	filepath = resolve_path(filepath);
	
	std::ifstream infile(filepath);
	
	if(!infile){
		std::cerr << "Could not open file\n";
	}
	
	std::string input_line;
	GapBuffer temp_buffer;

	while(std::getline(infile, input_line)){
		for(auto ch : input_line){
			temp_buffer.insert(ch);
		}
	}

	infile.close();
	return temp_buffer;
}


