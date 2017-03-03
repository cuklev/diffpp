#include "diff_algorithms/char_diff.hpp"
#include "diff_algorithms/line_diff.hpp"

#include<iostream>
#include<vector>

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

	switch(diff_type) {
		case CHAR_DIFF:
			char_diff(filenames[0], filenames[1]);
			break;

		case LINE_DIFF:
			line_diff(filenames[0], filenames[1]);
			break;
	}
}
