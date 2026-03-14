#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include "gapbuffer.h"

#ifndef FILE_MANAGER
#define FILE_MANAGER

class FileManager {
	private:
		std::filesystem::path current_file = "";

	public:
		FileManager(std::filesystem::path current_file);
		void set_current_file();
		void get_current_file();
		std::filesystem::path resolve_target_path(std::filesystem::path filepath); 
		bool file_exists(std::filesystem::path filepath);
		void write_file(std::filesystem::path filepath, GapBuffer& gapbuffer);
		GapBuffer read_file(std::filesystem::path filepath);
};

#endif //FILE_MANAGER
