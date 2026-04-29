#include <filesystem>
#include "gapbuffer.h"

#ifndef FILE_MANAGER
#define FILE_MANAGER
/*

FileManager
	
	Responsible for using STL functions from the <fstream> and <filesystem>
	headers to execute file operations related to importing text from a
	GapBuffer object onto a file and exporting text from a file onto a
	GapBuffer object.

*/
class FileManager {
	private:
		std::filesystem::path current_file;

	public:
		FileManager(std::filesystem::path filepath = "");

		void set_current_file(std::filesystem::path filepath);
		std::filesystem::path get_current_file();

		std::filesystem::path resolve_target_path(std::filesystem::path filepath); 
		bool file_exists(std::filesystem::path filepath);
		bool write_file(std::filesystem::path filepath, GapBuffer& gapbuffer);
		bool read_file(std::filesystem::path filepath, GapBuffer& gapbuffer);
};

#endif //FILE_MANAGER
