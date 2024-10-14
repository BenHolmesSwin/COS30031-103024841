/*

Ben Holmes 103024841
GridWorld Simple
Game Spec is 30031's Gridworld spec
*/

#include <iostream>
#include <array>
#include <list>

using namespace std;

//hard coded map data,
// # is wall
// D is death
// S is start
// ' ' is empty
// G is gold
char map[8][8]{
	{'#','#','#','#','#','#','#','#'},
	{'#',' ',' ',' ',' ',' ','G','#'},
	{'#',' ','D','#',' ','D',' ','#'},
	{'#',' ',' ','#',' ','#','#','#'},
	{'#','#',' ','#',' ',' ',' ','#'},
	{'#','D',' ','#','#',' ','#','#'},
	{'#',' ',' ',' ',' ',' ',' ','#'},
	{'#','S','#','#','#','#','#','#'},
};

//Global variables

// Inital Player Position
// x is between 0-7 going from left to right
int playerX = 1;
// y is between 0-7 going from top to bottom
int playerY = 7;

// bool for keeping loop active.
bool playing = true;

// bool for goal or death end.
bool sucess = false;

// current options as list of char
list<char> options;

void display() {
	cout << "===Current Map===" << endl;
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			//spacing
			cout << ' ';
			if (playerX == j && playerY == i) {// check for player position
				cout << 'X';
			}
			else {
				cout << map[i][j];
			}
		}
		cout << endl;
	}
	cout << "=================" << endl;
	//Key
	cout << " # is wall\n D is death\n S is start\n G is gold\n X is player" << endl;
	cout << "=================" << endl;
}

char input() {
	bool badInput = true;
	char input;
	while (badInput) {
		cout << "Exit program is Q" << endl;
		cout << "You can move ";
		for (char option : options) {
			cout << option << ' ';
		}
		cout << ":> ";
		cin >> input;
		//check all options against input
		for (char option : options) {
			if (input == option) {
				badInput = false;//ends loop when false
			}
		}
		//check input for Q for quit
		if (input == 'Q') {
			badInput = false;
		}
		//if bad input, state it
		if (badInput) {
			cout << "Bad Input. Try Again:" << endl;
		}
	}
	return input;
}

void update(char option) {
	
}

int main() {
	//inital values
	options.push_back('N');
	options.push_back('E');
	options.push_back('S');
	options.push_back('W');

	while (playing) {
		display();
		char option = input();
		update(option);
		playing = false;//exit loop on first for debug
	}



	return 0;
}