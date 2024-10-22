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
		if (ent.open) {
			if (ent.inventory.size() > 0)
			{
				cout << "Contains: ";
				for (const auto& con : ent.inventory) {
					cout << con.first << " | ";
				}
				cout << endl;
			}
			else {
				cout << "Nothing in this " + ent.name << endl;
			}
		}
		else {
			cout << "This " + ent.name + " is closed!" << endl;
		}
		resultString = "LOOK IN done";
	}
	else
	{
		cout << ent.name <<  " has nothing to LOOK IN" << endl;
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
			if (adventure.graph[adventure.current].contents.count(args[2])) {//if graph contents contains entity with key args[2]
				resultString = lookIn(adventure.graph[adventure.current].contents[args[2]]);
				badInput = false;
			}
			else if (adventure.player.inventory.count(args[2])) {//if player invetory contains entity with key args[2]
				resultString = lookIn(adventure.player.inventory[args[2]]);
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

//TAKE command
string takeFrom(vector<string> args, entity::Entity& ent, Adventure& adventure) {
	string result;
	if (ent.inventory.count(args[1])) {//if entity id1 is in id2's inventory
		auto item = ent.inventory[args[1]];
		if (ent.open) {
			if (item.carry) {
				adventure.player.addItem(item.id, item);
				ent.inventory.erase(args[1]);
				cout << item.name << " has been added to player inventory from " << ent.name << endl;
				result = "TAKE from ent to inv";
			}
			else {
				cout << "This item is too big to carry" << endl;
				result = "TAKE from ent to inv Fail big";
			}
		}
		else {
			cout << "This " + ent.name + " is closed!" << endl;
			result = "TAKE from ent to inv Fail close";
		}
	}
	else {
		cout << "This item is not in " + ent.name + "'s inventory" << endl;
		result = "TAKE loc to inv";
	}
	return result;
}

pair<bool, string> TakeCommand::execute(vector<string> args, Adventure& adventure) {
	string resultString = "TAKE failed, check input items have no typos";
	bool badInput = true;
	if (args.size() == 2 && adventure.graph[adventure.current].contents.count(args[1])) {// if command is TAKE_id and current location cotains id1 (args[1])
		auto ent = adventure.graph[adventure.current].contents[args[1]];
		if (ent.carry) {
			adventure.player.addItem(ent.id, ent);
			adventure.graph[adventure.current].contents.erase(args[1]);
			cout << ent.name << " has been added to player inventory"<< endl;
			resultString = "TAKE loc to inv";
			badInput = false;
		}
		else {
			cout << "This item is too big to carry" << endl;
			resultString = "TAKE from loc to inv";
			badInput = false;
		}
	}
	else if (args.size() == 4 && args[2] == "FROM" ) {// if command is TAKE_id_FROM_id and current location cotains id2 (args[3])
		if (adventure.graph[adventure.current].contents.count(args[3])) {//check if id2 is in current
			resultString = takeFrom(args,adventure.graph[adventure.current].contents[args[3]],adventure);
			badInput = false;
		}
		else if (adventure.player.inventory.count(args[3])) {//check if item 2 is in player (for bags that can be carried
			resultString = takeFrom(args, adventure.player.inventory[args[3]], adventure);
			badInput = false;
		}
		else {
			cout << "There is no item " << args[3] << " in current location or player inventory" << endl;
			resultString = "TAKE no id 2";
			badInput = false;
		}
	}
	return pair<bool, string>(badInput, resultString);
}

string TakeCommand::syntax(string cmdName) {
	return cmdName + "_[id1]_[From_Id2] || Takes entity id1 into the players inventory (from entity 2 if used)";
}

//PUT command
string putIn(vector<string> args, entity::Entity& ent, Adventure& adventure) {
	string result;
	auto item = adventure.player.inventory[args[1]];
	if (ent.open) {
		ent.inventory[item.id] = item;
		adventure.player.inventory.erase(args[1]);
		cout << item.name << " has been put in " << ent.name << " from player inventory" << endl;
		result = "TAKE from ent to inv";
	}
	else {
		cout << "This " + ent.name + " is closed!" << endl;
		result = "TAKE from ent to inv Fail close";
	}
	return result;
}

pair<bool, string> PutCommand::execute(vector<string> args, Adventure& adventure) {
	string resultString = "PUT failed, this item is not in your inventory";
	bool badInput = true;
	if (adventure.player.inventory.count(args[1])) {
		if (args.size() == 2) {
			auto ent = adventure.player.inventory[args[1]];
			adventure.graph[adventure.current].contents[ent.id] = ent;
			adventure.player.inventory.erase(args[1]);
			cout << ent.name << " has been added to current location" << endl;
			resultString = "PUT inv to loc";
			badInput = false;
		}
		else if (args.size() == 4 && args[2] == "IN") {// if command is PUT_id_IN_id
			if (adventure.graph[adventure.current].contents.count(args[3])) {//check if id2 is in current
				resultString = putIn(args, adventure.graph[adventure.current].contents[args[3]], adventure);
				badInput = false;
			}
			else if (adventure.player.inventory.count(args[3])) {//check if item 2 is in player (for bags that can be carried)
				resultString = putIn(args, adventure.player.inventory[args[3]], adventure);
				badInput = false;
			}
			else {
				cout << "There is no item " << args[3] << " in current location or player inventory" << endl;
				resultString = "PUT no id 2";
				badInput = false;
			}
		}
	}
	return pair<bool, string>(badInput, resultString);
}

string PutCommand::syntax(string cmdName) {
	return cmdName + "[id1]_IN_[id2] || Puts entity id1 in entity id2 inventory (cannot put item in player use TAKE FROM)";
}

//OPEN command
string openEntity(vector<string> args,entity::Entity& ent, Adventure& adventure) {
	string result;
	if (ent.open) {
		cout << ent.name << " is already open" << endl;
		result = "OPEN already open";
	}
	else if (ent.locked) {
		if (args.size() == 4) {
			if (adventure.player.inventory.count(args[3]) && args[3] == "key") {//needs two sperate ifs cause of potential out of index errors
				ent.open = true;
				ent.locked = false;
				cout << ent.name << " opened with key!" << endl;
				result = "OPEN opened with key";
			}
			else {
				cout << ent.name << " is locked, you need to use a key to Open it (needs to be in your inventory and use FROM)" << endl;
				result = "OPEN locked no key";
			}
		}
		else {
			cout << ent.name << " is locked, you need to use a key to Open it (needs to be in your inventory and use FROM)" << endl;
			result = "OPEN locked no key";
		}
	}
	else {
		ent.open = true;
		cout << ent.name << " opened!" << endl;
		result = "OPEN opened";
	}
	return result;
}

pair<bool, string> OpenCommand::execute(vector<string> args, Adventure& adventure) {
	string resultString = "This entity does not exist in this location or your inventory, use look to find out whats around you";
	bool badInput = true;
	if (args.size() > 1) {//check to prevent out of index errors
		if (adventure.graph[adventure.current].contents.count(args[1]) || adventure.player.inventory.count(args[1])) {
			if (adventure.graph[adventure.current].contents.count(args[1])) {
				resultString = openEntity(args, adventure.graph[adventure.current].contents[args[1]], adventure);
			}
			else {
				resultString = openEntity(args, adventure.player.inventory[args[1]], adventure);
			}
			badInput = false;
		}
	}
	return pair<bool, string>(badInput, resultString);
}

string OpenCommand::syntax(string cmdName) {
	return cmdName + "_[id1]_[WITH_id2] || Opens entity id1 if close (use WITH id2 if locked, entity id2 needs to be a key)";
}

