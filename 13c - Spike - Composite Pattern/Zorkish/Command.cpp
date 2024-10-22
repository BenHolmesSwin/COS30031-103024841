#include <iostream>

#include "Command.h"
#include "Adventure.h"

using namespace std;

//seperating out the check so it doesnt need to be repeated
bool entityContentsCheck(const entity::Entity& ent) {
	if (ent.name == "Bag" || ent.name == "Pouch" || ent.name == "Barrel" || ent.name == "Chest") {
		return true;
	}
	return false;
}

//execute commands will return to badInput at the adventure.gameInput() level, meaning to keep in the input loop, the badInput result will be true

pair<bool, string> GoCommand::execute( vector<string> args,Adventure& adventure) {
	string resultString = "No matching connection, use LOOK to see possible paths";
	bool badInput = true;
	for (string posibleOption : adventure.graph[adventure.current].connections) {
		if (args.size() == 2) {//checks size is 2 as there should be 2 for GO id
			if (posibleOption == args[1]) {
				adventure.current = posibleOption;//set current to new
				resultString = "GO done";
				badInput = false;
			}
		}
	}
	return pair<bool, string>(badInput, resultString);
}

string GoCommand::syntax(string cmdName) {
	return cmdName + "_[id] || sets current position to location with id [id]";
}

//HELP command
pair<bool, string> HelpCommand::execute(vector<string> args, Adventure& adventure) {
	cout << "========HELP==========" << endl;
	cout << "_ means a space || After using ALIAS remember to use the new command name as replacement, new are noted but not all syntax fully updated" << endl;
	for (const auto& cmd : adventure.cmdManager.commands) {
		cout << cmd.first << " : " << cmd.second->syntax(cmd.first) << endl;
	}
	cout << "======================" << endl;
	return pair<bool, string>(false, "HELP Done");
}

string HelpCommand::syntax(string cmdName) {
	return cmdName + " || displays syntax of all current commands";
}

//INVENTORY command
pair<bool, string> InventoryCommand::execute(vector<string> args, Adventure& adventure) {
	cout << "Inventory:" << endl;
	for (const auto& ent : adventure.player.inventory) {
		cout << "   " << ent.first << endl;
	}
	cout << "=====" << endl;
	return pair<bool, string>(false, "INVENTORY done");
}

string InventoryCommand::syntax(string cmdName) {
	return cmdName + " || displays players current inventory as ids";
}

//LOOK command
string lookIn(const entity::Entity& ent) {
	string resultString = "This item has no possible contents";
	if (entityContentsCheck(ent)) {
		cout << "Looking in: " << ent.name << endl;
		if (ent.contents.size() > 0)
		{
			cout << "Contains: ";
			for (const auto& con : ent.contents) {
				cout << con.first << " | ";
			}
			cout << endl;
		}
		else {
			cout << "Nothing in this " + ent.name << endl;
		}
		resultString = "LOOK IN done";
	}
	else
	{
		resultString = "Nothing to LOOK IN";
	}
	return  resultString;
}

pair<bool, string> LookCommand::execute(vector<string> args, Adventure& adventure) {
	string resultString = "No matching item, use LOOK to see possible paths";
	bool badInput = true;
	if (args.size() > 1) {//check size is
		if (args[1] == "AT") {
			if (adventure.graph[adventure.current].contents.count(args[2])) {//if graph contents contains entity with key ars[2]
				const auto& ent = adventure.graph[adventure.current].contents[args[2]];
				cout << "Looking at: " << ent.name << " | " << ent.description << endl;
				badInput = false;
				resultString = "LOOK AT done";
			}
			else if (adventure.player.inventory.count(args[2])) {
				const auto& ent = adventure.player.inventory[args[2]];
				cout << "Looking at: " << ent.name << " | " << ent.description << endl;
				badInput = false;
				resultString = "LOOK AT done";
			}
		}else if (args[1] == "IN") {
			if (adventure.graph[adventure.current].contents.count(args[2])) {//if graph contents contains entity with key ars[2]
				const auto& ent = adventure.graph[adventure.current].contents[args[2]];
				resultString = lookIn(ent);
				badInput = false;
			}
			else if (adventure.player.inventory.count(args[2])) {
				const auto& ent = adventure.player.inventory[args[2]];
				resultString = lookIn(ent);
				badInput = false;
			}
		}
	}
	else {
		cout << "Access from here: ";
		for (string path : adventure.graph[adventure.current].connections) {
			cout << path << " | ";
		}
		cout << endl;
		cout << adventure.graph[adventure.current].name << " contains:" << endl;
		for (const auto& ent : adventure.graph[adventure.current].contents) {
			cout << "   " << ent.first << endl;
		}
		badInput = false;
		resultString = "LOOK done";
	}
	return pair<bool, string>(badInput, resultString);
}

string LookCommand::syntax(string cmdName) {
	return  cmdName + " || displays current locations paths and entities || "+ cmdName + "_AT_[id] || displays entity with [id] description";
}




//ALIAS command
pair<bool, string> AliasCommand::execute(vector<string> args, Adventure& adventure) {
	string resultString = "Incorrect syntax for ALIAS, use HELP";
	bool badInput = true;
	if (args.size() == 4) {
		if (args[2] == "TO" && adventure.cmdManager.commands.count(args[1])) {//if cmd manager commands contain command with key args[1]
			Command* temp = adventure.cmdManager.commands[args[1]];
			adventure.cmdManager.commands.erase(args[1]);
			adventure.cmdManager.commands[args[3]] = temp;
			badInput = false;
			resultString = "ALIAS done: " + args[1] + " changed to " + args[3];
		}
	}
	
	return pair<bool, string>(badInput, resultString);
}

string AliasCommand::syntax(string cmdName) {
	return cmdName + "_[cmd1]_TO_[cmd2] || Sets commandName (e.g GO) of [cmd1] to [cmd2]";
}

//DEBUG command
pair<bool, string> DebugCommand::execute(vector<string> args, Adventure& adventure) {
	cout << "========DEBUG==========" << endl;
	for (const auto& loc : adventure.graph) {
		cout << "Id: " << loc.first << ":" << endl;
		cout << loc.second.name << " : " << loc.second.description << endl;
		cout << "    Access from here: ";
		for (string path : loc.second.connections) {
			cout << path << " | ";
		}
		cout << endl;
		cout << "\tContains:" << endl;
		for (const auto& ent : loc.second.contents) {
			cout << "\t" << ent.first << " : " << ent.second.description << endl;
		}
		cout << endl;
	}
	cout << "======================" << endl;
	return pair<bool, string>(false, "DEBUG Done");
}

string DebugCommand::syntax(string cmdName) {
	return cmdName + " || shows all locations and all of their info";
}

//QUIT command
pair<bool, string> QuitCommand::execute(vector<string> args, Adventure& adventure) {
	adventure.running = false;
	return pair<bool, string>(false, "QUIT done");
}

string QuitCommand::syntax(string cmdName) {
	return cmdName + " || Exits program";
}

