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
	for (const auto& l : data["locations"]) {
		string id = l["id"];
		location::Location location = l.template get<location::Location>();
		graph.insert(pair<string,location::Location>(id, location));
	}
	for (const auto& l : data["paths"]) {
		string name = l["name"];
		path::Path path = l.template get<path::Path>();
		paths.insert(pair<string, path::Path>(name, path));
	}
	update("castle");
}

void Adventure::update(string s) {
	current = s;
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

//renders current location
void Adventure::gameRender() {
	cout << "You are currently at: " << graph[current].name << endl;
	cout << graph[current].description << endl;

}

string Adventure::gameInput() {
	bool badInput = true;
	string input;
	string result;
	while (badInput) {
		cout << "You may GO to: ";
		for (string s : graph[current].connections) {
			cout << s << " | ";
		}
		cout << endl;
		cout << ":> ";
		getline(cin, input);
		string delimiter = " ";
		auto tokens = split(input, delimiter);
		if (tokens.size() == 2) {
			if (tokens[0] == "GO") {
				for (string posibleOption : graph[current].connections) {//for each string in connections in current
					if (posibleOption == tokens[1]) {//check if the connection is equal to the input
						result = paths[posibleOption].findLoc(current);//set result to loc in path that is not current
						badInput = false;
					}
				}

			}
		}//check input for QUIT
		else if (tokens[0] == "QUIT") {
			result = "QUIT";
			badInput = false;
		}
		if(badInput){
			cout << "Bad Input. Try Again:" << endl;
		}
	}
	return result;
}

bool Adventure::gameUpdate(string input) {
	if (input == "QUIT") {
		return false;
	}
	update(input);
	return true;
}


