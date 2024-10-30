
#include <iostream>

#include "SDLcircle.h"
#include "SDLsquare.h"

int main(int argc, char* args[]) {
	bool running = true;
	int input;
	while (running) {
		std::cout << "Enter 1 for circle, Enter 2 for square:" << std::endl;
		std::cin >> input;
		if (input == 1) {
			SDLcircle();
			running = false;
		}
		else if (input == 2) {
			SDLsquare();
			running = false;
		}
	}
	return 0;
}