#pragma once

#include "Location.h"
#include "json.hpp"
#include "Player.h"
#include "CommandManager.h"
#include "ComponentManager.h"
#include "MessageBoard.h"

using json = nlohmann::json;

class Adventure
{
public:
	Adventure(const char* fileName);
	string current;
	player::Player player;
	CommandManager cmdManager;
	ComponentManager compManager;
	MessageBoard msgBoard;
	bool running = true;
	map<string,location::Location> graph;
	void gameInput();
private:
	void start(json data);
};