#include "colors.hpp"

#include<iostream>

static const char* COLORS[] = {
	"\033[0m",    // normal
	"\033[0;32m", // green
	"\033[0;31m"  // red
};

static Coloring current_color = BOTH;

void update_color(Coloring new_color) {
	if(current_color != new_color) {
		current_color = new_color;
		std::cout << COLORS[new_color];
	}
}
