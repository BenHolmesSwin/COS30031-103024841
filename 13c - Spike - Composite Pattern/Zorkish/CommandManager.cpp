

#include <string>

#include "CommandManager.h"
#include "Command.h"
#include "Adventure.h"

using namespace std;

pair<bool, string> CommandManager::executeCommand(const string& commandName, vector<string> args, Adventure & adventure) {
	if (commands.count(commandName)) {
		pair<bool, string> result = commands[commandName]->execute(args, adventure);
		return result;
	}
	return pair<bool, string>(true, "Command not in command list. Try HELP if dont know any commands");
}