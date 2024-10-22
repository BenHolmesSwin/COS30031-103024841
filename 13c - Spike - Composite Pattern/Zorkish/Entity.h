#pragma once

#include <string>
#include <vector>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

namespace entity {
	struct Entity
	{
		string id;
		string name;
		string description;
	};

	void from_json(const json& j, Entity& l);
}