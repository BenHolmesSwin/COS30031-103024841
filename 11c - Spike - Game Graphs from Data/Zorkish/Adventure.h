#pragma once

#include "Location.h"
#include "json.hpp"

using json = nlohmann::json;

class Adventure
{
public:

	Adventure(const char* fileName);
	location::Location current;
	void Start(json data);
	vector<location::Location> graph;
	void update(string s);
	void gameRender();
	string gameInput();
	bool gameUpdate(string input);
};