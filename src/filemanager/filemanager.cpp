#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "gapbuffer.h"
#include "filemanager.h"

FileManager::FileManager(std::filesystem::path current_file){
	if(current_file.is_absolute()){
		this->current_file = current_file;
		return;
	}
	std::filesystem::path combined = std::filesystem::current_path() / current_file;
	this->current_file = std::filesystem::weakly_canonical(combined);
}

void FileManager::set_current_file(std::filesystem::path filepath){
	filepath = resolve_target_path(filepath);
	
	if(!file_exists(filepath)){
		return;
	}

	this->current_file = filepath;
}

std::filesystem::path FileManager::get_current_file(){
	return current_file;
}

std::filesystem::path FileManager::resolve_target_path(std::filesystem::path filepath){
	
	std::filesystem::path base = 
	current_file.empty() ? 
	std::filesystem::current_path() 
	: current_file.parent_path();

	std::filesystem::path combined = 
	filepath.is_absolute() ? filepath : base / filepath;
	
	return std::filesystem::weakly_canonical(combined);
}
//resolves AND checks if file exists
bool FileManager::file_exists(std::filesystem::path filepath){
	filepath = resolve_target_path(filepath);
		
	if(std::filesystem::exists(filepath)){
		return true;
	}

	return false;
}

void FileManager::write_file(std::filesystem::path filepath, GapBuffer& gapbuffer){
	filepath = resolve_target_path(filepath);
	
	std::ofstream outfile(filepath);
	
	if(!outfile){
		std::cerr << "Could not open file\n";
		return;
	}
	std::string buffer_text = gapbuffer.get_text();
	outfile << buffer_text;
}	


GapBuffer FileManager::read_file(std::filesystem::path filepath){
	filepath = resolve_target_path(filepath);
	
	std::ifstream infile(filepath);
	
	if(!infile){
		std::cerr << "Could not open file\n";
	}
	
	std::string input_line;
	GapBuffer temp_buffer;

	while(std::getline(infile, input_line, '\0')){
		for(auto ch : input_line){
			temp_buffer.insert(ch);
		}
	}

	infile.close();
	return temp_buffer;
}


