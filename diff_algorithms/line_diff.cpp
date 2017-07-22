#include "line_diff.hpp"
#include "../colors.hpp"

#include<unordered_map>
#include<vector>
#include<fstream>

static std::unordered_map<std::size_t, std::string> all_lines;

std::vector<std::size_t> read_file(const char* filename) {
	std::ifstream file(filename);

	std::vector<std::size_t> lines;
	while(file) {
		std::string line;
		std::getline(file, line);
		auto hash_line = std::hash<std::string>()(line);
		lines.push_back(hash_line);
	}
}

void line_diff(const char*, const char*) {
}
