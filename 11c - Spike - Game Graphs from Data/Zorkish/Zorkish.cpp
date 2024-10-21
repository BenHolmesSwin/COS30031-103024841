// Zorkish.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Adventure.h"

using namespace std;

bool running = true;

vector<string> split(string& s, const string& delimiter) {// split tokens
	vector<string> tokens;
	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != string::npos) {
		token = s.substr(0, pos);
		tokens.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	tokens.push_back(s);

	return tokens;
}

void render(Adventure& adventure) {
    cout << "You are currently at: " << adventure.current.name << endl;
    cout << adventure.current.description << endl;
    
}

string input(Adventure& adventure) {
	bool badInput = true;
	string input;
	string result;
	while (badInput) {
		cout << "You may GO to: ";
		for (string s : adventure.current.connections) {
			cout << s << " | ";
		}
		cout << endl;
		cout << ":> ";
		getline(cin,input);
		string delimiter = " ";
		auto tokens = split(input, delimiter);
		if (tokens.size() == 2) {
			if (tokens[0] == "GO") {
				//check all options against input
				for (string posibleOption : adventure.current.connections) {
					if (posibleOption == tokens[1]) {
						result = posibleOption;
						badInput = false;
					}
				}

			}
		}//check input for Q for quit
		else if (tokens[0] == "QUIT") {
			result = "QUIT";
			badInput = false;
		}
		else {
			cout << "Bad Input. Try Again:" << endl;
		}
	}
	return result;
}

bool update(Adventure& adventure, string input) {
	if (input == "QUIT") {
		return false;
	}
	for (location::Location l : adventure.graph) {
		if (l.id == input) {
			adventure.current = l;
			return true;
		}
	}
	return true;
}

int main()
{
    Adventure adventure("Adventure.json");
    cout << "Welcome to Zorkish: Adventure" << endl;
    while (running) {
        render(adventure);
        string option = input(adventure);
		running = update(adventure, option);
    }
	cout << "Thanks for playing!" << endl;
}

