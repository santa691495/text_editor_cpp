#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "gapbuffer.h"
#include "filemanager.h"
#include "filestatus.h"

FileManager::FileManager(std::filesystem::path filepath){
 	auto target_file = resolve_target_path(filepath);
	
	if(!std::filesystem::exists(target_file)){
		return;
	}	

	if(!std::filesystem::is_regular_file(target_file)){
		return;
	}

	this->current_file = target_file;
}

void FileManager::set_current_file(std::filesystem::path filepath){
 	auto target_file = resolve_target_path(filepath);
	
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
	
	try {
		return std::filesystem::weakly_canonical(combined);
	} catch (...) {
		return combined;
	}
}

bool FileManager::file_exists(std::filesystem::path filepath){
	auto resolved_path = resolve_target_path(filepath);
	return std::filesystem::exists(resolved_path) && std::filesystem::is_regular_file(resolved_path);
}

FileStatus FileManager::write_file(std::filesystem::path filepath, GapBuffer& gapbuffer){
	filepath = resolve_target_path(filepath);

	bool is_new_file = !file_exists(filepath) ? true : false;
	
	std::ofstream outfile(filepath, std::ios::trunc);
	
	if(!outfile){
		std::cerr << "Could not open file\n";
		return FileStatus::FAIL;
	}
	std::string buffer_text = gapbuffer.get_text();
	outfile << buffer_text;

	if(is_new_file){
		return FileStatus::NEW;
	}
	return FileStatus::EXISTS;
}	

FileStatus FileManager::read_file(std::filesystem::path filepath, GapBuffer& gapbuffer){
	filepath = resolve_target_path(filepath);
	
	if(!file_exists(filepath)){
		return FileStatus::NOT_EXISTS;
	}
	
	std::ifstream infile(filepath);
	
	if(!infile){
		std::cerr << "Could not open file: " << filepath << "\n";
		return FileStatus::FAIL;
	}
		
	std::string input_line;
	std::getline(infile, input_line, '\0');

	gapbuffer.clear();
	for(auto& ch : input_line){
		gapbuffer.insert(ch);
	}

	set_current_file(filepath);
	infile.close();

	return FileStatus::EXISTS;
}


