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
// REMINDER FOR BEN: first is y, second is x
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

// bool for quit
bool quit = false;

// current options as list of char
list<char> options;


void display() {
	cout << "===Current Map===" << endl;
	//looping y axis
	for (int i = 0; i <= 7; i++) {
		//looping x axis
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
	char option;
	while (badInput) {
		cout << "Exit program is Q" << endl;
		cout << "You can move ";
		for (char option : options) {
			cout << option << ' ';
		}
		cout << ":> ";
		cin >> option;
		//check all options against input
		for (char posibleOption : options) {
			if (posibleOption == option) {
				badInput = false;//ends loop when false
			}
		}
		//check input for Q for quit
		if (option == 'Q') {
			badInput = false;
		}
		//if bad input, state it
		if (badInput) {
			cout << "Bad Input. Try Again:" << endl;
		}
	}
	return option;
}

void update(char option) {
	//switch for input option
	//doesnt have check for invalid changes as input validation comparing to options is enough
	switch (option)
	{
		case 'N':
			playerY -= 1;
			break;
		case 'E':
			playerX += 1;
			break;
		case 'S':
			playerY += 1;
			break;
		case 'W':
			playerX -= 1;
			break;
		case 'Q':
			playing = false;
			quit = true; //changing quit to true for end check
			break;
		default://for inital creation so options can be created without input
			break;
	}

	//check for end
	if (map[playerY][playerX] == 'D' || map[playerY][playerX] == 'G') {
		playing = false;
		if (map[playerY][playerX] == 'G') {
			sucess = true;
		}
	}
	else {
		//making new options
		options.clear();
		
		if (playerY > 0) {
			if (map[playerY - 1][playerX] != '#') {
				options.push_back('N');
			}
		}
		if (playerX < 7) {
			if (map[playerY][playerX + 1] != '#') {
				options.push_back('E');
			}
		}
		if (playerY < 7) {
			if (map[playerY + 1][playerX] != '#') {
				options.push_back('S');
			}
		}
		if (playerX > 0) {
			if (map[playerY][playerX - 1] != '#') {
				options.push_back('W');
			}
		}
	}
}

int main() {
	//inital values
	update(' ');//inital options creation

	while (playing) {
		display();
		char option = input();
		update(option);
	}
	if (quit) {// check for quit
		cout << "You have exited the game. Thanks for playing!" << endl;
	}
	else if (sucess) {// check for gold reached
		cout << "Wow - you’ve discovered a large chest filled with GOLD coins!" << endl;
		cout << "YOU WIN!" << endl;
		cout << "Thanks for playing. There probably won’t be a next time." << endl;
	}
	else {
		cout << "Arrrrgh... you have fallen down a pit and landed on spikes." << endl;
		cout << "YOU HAVE DIED!" << endl;
		cout << "Thanks for playing. There probably won’t be a next time." << endl;
	}
	return 0;
}