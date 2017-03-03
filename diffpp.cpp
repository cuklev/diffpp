#include<iostream>
#include<fstream>
#include<vector>

std::string read_file(const char* filename) {
	std::ifstream file(filename);

	return std::string(std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());
}

enum {
	BOTH,
	FIRST,
	SECOND
} current_color;

int main(int argc, char** argv) {
	if(argc != 3) {
		std::cerr << "Give two files\n";
		return 1;
	}

	auto str1 = read_file(argv[1]);
	auto str2 = read_file(argv[2]);

	std::vector<std::vector<int>> dp(str1.size() + 1, std::vector<int>(str2.size() + 1));
	for(unsigned i = str1.size(); i > 0; --i)
		for(unsigned j = str2.size(); j > 0; --j)
			dp[i - 1][j - 1] = str1[i - 1] == str2[j - 1] ? dp[i][j] + 1 : std::max(dp[i][j - 1], dp[i - 1][j]);

	for(unsigned i = 0, j = 0; i < str1.size() && j < str2.size();) {
		if(i < str1.size() && j < str2.size() && str1[i] == str2[j]) {
			// color normal
			if(current_color != BOTH) {
				current_color = BOTH;
				std::cout << "\033[0m";
			}
			std::cout << str1[i];
			++i; ++j;
		}
		else if(i == str1.size() || dp[i][j] != dp[i + 1][j]) {
			// color red
			if(current_color != SECOND) {
				current_color = SECOND;
				std::cout << "\033[0;31m";
			}
			std::cout << str2[j];
			++j;
		} else {
			// color green
			if(current_color != FIRST) {
				current_color = FIRST;
				std::cout << "\033[0;32m";
			}
			std::cout << str1[i];
			++i;
		}
	}
}
