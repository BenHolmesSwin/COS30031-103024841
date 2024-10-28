#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

//forward delcaration
class Command;
class Adventure;

class CommandManager {
public:
	map<string, Command*> commands;
	pair<bool,string> executeCommand(const string& commandName, vector<string> args, Adventure& adventure);
};