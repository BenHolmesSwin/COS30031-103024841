#pragma once

#include <string>
#include <vector>

#include "json.hpp"
#include "Entity.h"

using namespace std;
using json = nlohmann::json;

namespace location {
	struct Location
	{
		string id;
		string name;
		string description;
		vector<string> connections;
		map<string, entity::Entity> contents;
	};

	void from_json(const json& j, Location& l);
}