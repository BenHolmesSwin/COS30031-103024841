#include <iostream>

#include "Command.h"
#include "Adventure.h"

using namespace std;

//execute commands will return to badInput at the adventure.gameInput() level, meaning to keep in the loop, the badInput result will be true

pair<bool, string> GoCommand::execute( vector<string> args,Adventure& adventure) {
	string resultString = "No matching connection, use LOOK to see possible paths";
	bool badInput = true;
	for (string posibleOption : adventure.graph[adventure.current].connections) {
		if (args.size() == 2) {
			if (posibleOption == args[1]) {
				adventure.current = posibleOption;
				resultString = "GO done";
				badInput = false;
			}
		}
	}
	return pair<bool, string>(badInput, resultString);
}

string GoCommand::syntax() {
	return "GO_[id] || sets current position to location with id [id]";
}

//HELP command
pair<bool, string> HelpCommand::execute(vector<string> args, Adventure& adventure) {
	cout << "========HELP==========" << endl;
	cout << "_ means a space" << endl;
	for (const auto& cmd : adventure.cmdManager.commands) {
		cout << cmd.first << " : " << cmd.second->syntax() << endl;
	}
	cout << "======================" << endl;
	return pair<bool, string>(false, "HELP Done");
}

string HelpCommand::syntax() {
	return "HELP || displays syntax of all current commands";
}

//INVENTORY command
pair<bool, string> InventoryCommand::execute(vector<string> args, Adventure& adventure) {
	return pair<bool, string>(true, "Inventory not implemented yet");
}

string InventoryCommand::syntax() {
	return "INVENTORY || displays players current inventory";
}

//LOOK command
pair<bool, string> LookCommand::execute(vector<string> args, Adventure& adventure) {
	return pair<bool, string>(true, "Look not implemented yet");
}

string LookCommand::syntax() {
	return  "LOOK || displays current locations paths and entities || LOOK_AT_[id] || displays entity with [id] description";
}

//ALIAS command
pair<bool, string> AliasCommand::execute(vector<string> args, Adventure& adventure) {
	return pair<bool, string>(true, "Alias not implemented yet");
}

string AliasCommand::syntax() {
	return "ALIAS_[cmd1]_TO_[cmd2] || Sets commandName (e.g GO) of [cmd1] to [cmd2]";
}

//DEBUG command
pair<bool, string> DebugCommand::execute(vector<string> args, Adventure& adventure) {
	return pair<bool, string>(true, "Debug not implemented yet");
}

string DebugCommand::syntax() {
	return "DEBUG || shows all locations and all of their info";
}

//QUIT command
pair<bool, string> QuitCommand::execute(vector<string> args, Adventure& adventure) {
	adventure.running = false;
	return pair<bool, string>(false, "QUIT done");
}

string QuitCommand::syntax() {
	return "QUIT || Exits program";
}

