#pragma once

#include "Location.h"
#include "json.hpp"
#include "Player.h"
#include "CommandManager.h"
#include "ComponentManager.h"

using json = nlohmann::json;

class Adventure
{
public:
	Adventure(const char* fileName);
	string current;
	player::Player player;
	CommandManager cmdManager;
	ComponentManager compManager;
	bool running = true;
	map<string,location::Location> graph;
	void gameInput();
private:
	void start(json data);
};