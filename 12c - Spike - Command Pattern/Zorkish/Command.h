#pragma once

#include <vector>
#include <string>

using namespace std;
class Adventure;

class Command {
public:
	string sytnax;
	virtual ~Command(){}
	virtual pair<bool, string> execute(vector<string> args, Adventure& adventure) = 0;
};

class GoCommand : public Command {
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class HelpCommand : public Command {
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class InventoryCommand : public Command {
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class LookCommand : public Command {
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class AliasCommand : public Command {
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class DebugCommand : public Command {
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class QuitCommand : public Command {
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};