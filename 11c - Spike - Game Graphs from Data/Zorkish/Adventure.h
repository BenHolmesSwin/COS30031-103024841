#pragma once

#include "Location.h"
#include "Path.h"
#include "json.hpp"

using json = nlohmann::json;

class Adventure
{
public:
	Adventure(const char* fileName);
	string current;
	void Start(json data);
	map<string,location::Location> graph;
	map<string, path::Path> paths;
	void update(string s);
	void gameRender();
	string gameInput();
	bool gameUpdate(string input);
};