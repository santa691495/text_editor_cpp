#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include "gapbuffer.h"

class FileManager {
	private:
		GapBuffer* current_buffer = nullptr;
	
	public: 
		
		FileManager(GapBuffer& current_buffer);
		std::filesystem::path resolve_path(std::filesystem::path filepath);
		bool file_exists(std::filesystem::path filepath);
		void write_file(std::filesystem::path filepath);
		GapBuffer read_file(std::filesystem::path filepath);
};
