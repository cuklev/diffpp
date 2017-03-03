#include "colors.hpp"

#include<iostream>
#include<fstream>
#include<vector>

std::string read_file(const char* filename) {
	std::ifstream file(filename);

	return std::string(std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());
}

enum DiffType {
	CHAR_DIFF,
	LINE_DIFF
};

int main(int argc, char** argv) {
	DiffType diff_type = CHAR_DIFF;

	std::vector<const char*> filenames;
	for(int i = 1; i < argc; ++i) {
		std::string param(argv[i]);
		if(param ==  "--line-diff") {
			diff_type = LINE_DIFF;
		} else if(param == "--char-diff") {
			diff_type = CHAR_DIFF;
		} else if(filenames.size() < 2) {
			filenames.push_back(argv[i]);
		} else {
			std::cerr << "You are giving me too many files\n";
			return 1;
		}
	}

	auto str1 = read_file(filenames[0]);
	auto str2 = read_file(filenames[1]);

	std::vector<std::vector<int>> dp(str1.size() + 1, std::vector<int>(str2.size() + 1));
	for(unsigned i = str1.size(); i > 0; --i)
		for(unsigned j = str2.size(); j > 0; --j)
			dp[i - 1][j - 1] = str1[i - 1] == str2[j - 1] ? dp[i][j] + 1 : std::max(dp[i][j - 1], dp[i - 1][j]);

	for(unsigned i = 0, j = 0; i < str1.size() && j < str2.size();) {
		if(i < str1.size() && j < str2.size() && str1[i] == str2[j]) {
			// color normal
			update_color(BOTH);
			std::cout << str1[i];
			++i; ++j;
		}
		else if(i == str1.size() || dp[i][j] != dp[i + 1][j]) {
			// color red
			update_color(SECOND);
			std::cout << str2[j];
			++j;
		} else {
			// color green
			update_color(FIRST);
			std::cout << str1[i];
			++i;
		}
	}
}
