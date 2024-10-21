#include <fstream>
#include <iostream>

#include "json.hpp"
#include "Location.h"
#include "Adventure.h"

using namespace std;
using json = nlohmann::json;

Adventure::Adventure(const char* fileName)
{
	json jsonData;
	string s = fileName;
	ifstream file(s);
	if (!file.is_open()) {
		cout << "Error opening file: " << fileName << endl;
		return;
	}

	try {
		file >> jsonData;
	}
	catch (const json::parse_error& e) {
		cout << "Parse error at byte " << e.byte << ": " << e.what() << endl;
	}
	file.close();
	Start(jsonData);
}

void Adventure::Start(json data){

	data.at("locations").get_to(graph);
	update("castle");
}

void Adventure::update(string s) {
	for (location::Location l : graph) {
		if (l.id == s) {
			current = l;
		}
	}
}

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

//For better zorkish, move game renderer
//renders current location
void Adventure::gameRender() {
	cout << "You are currently at: " << current.name << endl;
	cout << current.description << endl;

}

string Adventure::gameInput() {
	bool badInput = true;
	string input;
	string result;
	while (badInput) {
		cout << "You may GO to: ";
		for (string s : current.connections) {
			cout << s << " | ";
		}
		cout << endl;
		cout << ":> ";
		getline(cin, input);
		string delimiter = " ";
		auto tokens = split(input, delimiter);
		if (tokens.size() == 2) {
			if (tokens[0] == "GO") {
				//check all options against input
				for (string posibleOption : current.connections) {
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

bool Adventure::gameUpdate(string input) {
	if (input == "QUIT") {
		return false;
	}
	for (location::Location l : graph) {
		if (l.id == input) {
			current = l;
			return true;
		}
	}
	return true;
}


