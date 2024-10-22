// Zorkish.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Adventure.h"

using namespace std;


int main(int argc, char* argv[])
{
    Adventure adventure(argv[1]);
    cout << "Welcome to Zorkish: Adventure" << endl;
    while (adventure.running) {
        adventure.gameRender();
        adventure.gameInput();
    }
	cout << "Thanks for playing!" << endl;
}

