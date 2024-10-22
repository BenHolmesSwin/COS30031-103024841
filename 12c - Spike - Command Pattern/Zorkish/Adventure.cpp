#include <fstream>
#include <iostream>

#include "json.hpp"
#include "Location.h"
#include "Adventure.h"
#include "Command.h"

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
	start(jsonData);
}

void Adventure::start(json data){
	data.at("player").get_to(player);
	for (const auto& l : data["locations"]) {
		string id = l["id"];
		location::Location location = l.template get<location::Location>();
		graph[id] = location;
	}
	current = "castle";
	cmdManager.commands["GO"] = new GoCommand();
	cmdManager.commands["HELP"] = new HelpCommand();
	cmdManager.commands["INVENTORY"] = new InventoryCommand();
	cmdManager.commands["LOOK"] = new LookCommand();
	cmdManager.commands["ALIAS"] = new AliasCommand();
	cmdManager.commands["DEBUG"] = new DebugCommand();
	cmdManager.commands["QUIT"] = new QuitCommand();
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

void Adventure::gameInput() {

	cout << "You are currently at: " << graph[current].name << endl;

	pair<bool,string> badInput = pair<bool,string>(true,"inital");
	string input;
	while (badInput.first) {
		cout << ":> ";
		getline(cin, input);
		string delimiter = " ";
		auto tokens = split(input, delimiter);
		badInput = cmdManager.executeCommand(tokens[0],tokens,*this);
		if (badInput.first) {
			cout << badInput.second << endl;
		}
	}
}


