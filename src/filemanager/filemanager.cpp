#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "gapbuffer.h"
#include "filemanager.h"

FileManager::FileManager(std::filesystem::path current_file){
 	auto target_file = resolve_target_path(current_file);
	
	if(!std::filesystem::exists(target_file)){
		return;
	}	

	if(!std::filesystem::is_regular_file(target_file)){
		return;
	}

	this->current_file = target_file;
}

void FileManager::set_current_file(std::filesystem::path filepath){
 	auto target_file = resolve_target_path(current_file);
	
	if(!std::filesystem::exists(target_file)){
		return;
	}	

	if(!std::filesystem::is_regular_file(target_file)){
		return;
	}

	this->current_file = target_file;
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
	auto resolved_path = resolve_target_path(filepath);

	return std::filesystem::exists(resolved_path);
}

bool FileManager::write_file(std::filesystem::path filepath, GapBuffer& gapbuffer){
	filepath = resolve_target_path(filepath);
	
	std::ofstream outfile(filepath);
	
	if(!outfile){
		std::cerr << "Could not open file\n";
		return false;
	}
	std::string buffer_text = gapbuffer.get_text();
	outfile << buffer_text;
	return true;
}	

bool FileManager::read_file(std::filesystem::path filepath, GapBuffer& gapbuffer){
	filepath = resolve_target_path(filepath);
	
	std::ifstream infile(filepath);
	
	if(!infile){
		std::cerr << "Could not open file\n";
		return false;
	}
		
	gapbuffer.clear();
	std::string input_line;
	
	while(std::getline(infile, input_line, '\0')){
		for(auto& ch : input_line){
			gapbuffer.insert(ch);
		}
	}

	infile.close();
	return true;
}


