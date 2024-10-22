#pragma once

#include "Location.h"
#include "json.hpp"
#include "Player.h"
#include "CommandManager.h"

using json = nlohmann::json;

class Adventure
{
public:
	Adventure(const char* fileName);
	string current;
	player::Player player;
	CommandManager cmdManager;
	bool running = true;
	map<string,location::Location> graph;
	void start(json data);
	void gameInput();
};