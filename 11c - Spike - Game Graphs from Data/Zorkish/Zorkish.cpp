// Zorkish.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Adventure.h"

using namespace std;

bool running = true;

int main(int argc, char* argv[])
{
    Adventure adventure(argv[1]);
    cout << "Welcome to Zorkish: Adventure" << endl;
    while (running) {
        adventure.gameRender();
        string option = adventure.gameInput();
		running = adventure.gameUpdate(option);
    }
	cout << "Thanks for playing!" << endl;
}

