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

pair<bool, string> HelpCommand::execute(vector<string> args, Adventure& adventure) {
	return pair<bool, string>(true, "Help not implemented yet");
}

pair<bool, string> InventoryCommand::execute(vector<string> args, Adventure& adventure) {
	return pair<bool, string>(true, "Inventory not implemented yet");
}

pair<bool, string> LookCommand::execute(vector<string> args, Adventure& adventure) {
	return pair<bool, string>(true, "Look not implemented yet");
}

pair<bool, string> AliasCommand::execute(vector<string> args, Adventure& adventure) {
	return pair<bool, string>(true, "Alias not implemented yet");
}

pair<bool, string> DebugCommand::execute(vector<string> args, Adventure& adventure) {
	return pair<bool, string>(true, "Debug not implemented yet");
}

pair<bool, string> QuitCommand::execute(vector<string> args, Adventure& adventure) {
	adventure.running = false;
	return pair<bool, string>(false, "QUIT done");
}

