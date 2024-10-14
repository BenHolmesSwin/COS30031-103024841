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

char display() {
	
	return ' ';
}

void input(char option) {

}

void update() {

}

int main() {

	while (playing) {
		char option = display();
		input(option);
		update();
	}



	return 0;
}