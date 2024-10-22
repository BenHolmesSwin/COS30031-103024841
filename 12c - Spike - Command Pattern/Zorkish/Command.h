#pragma once

#include <vector>
#include <string>

using namespace std;
class Adventure;

class Command {
public:
	virtual ~Command(){}
	virtual pair<bool, string> execute(vector<string> args, Adventure& adventure) = 0;
	virtual string syntax() = 0;
};

class GoCommand : public Command {
	string syntax() override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class HelpCommand : public Command {
	string syntax() override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class InventoryCommand : public Command {
	string syntax() override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class LookCommand : public Command {
	string syntax() override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class AliasCommand : public Command {
	string syntax() override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class DebugCommand : public Command {
	string syntax() override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};

class QuitCommand : public Command {
	string syntax() override;
	pair<bool, string> execute(vector<string> args, Adventure& adventure) override;
};