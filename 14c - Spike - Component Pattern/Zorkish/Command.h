#pragma once

#include <vector>
#include <string>

using namespace std;
class Adventure;

class Command {
public:
	virtual ~Command(){}
	virtual pair<bool, string> execute(vector<string> args, Adventure& adventure) = 0;
	virtual string syntax(string cmdName) = 0;
};

class GoCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class HelpCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class InventoryCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class LookCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class AliasCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class DebugCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class QuitCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class TakeCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class PutCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class OpenCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class UseCommand : public Command {
	string syntax(string cmdName) override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};