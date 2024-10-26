#pragma once

#include <string>
#include <vector>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Component;

namespace entity {
	struct Entity
	{
		string id;
		string name;
		string description;
		bool carry = true;
		bool open = true;
		bool locked = false;
		vector<string> componentsList;
		map<string, Entity> inventory;
		map<string, Component*> components;
	};
}
namespace bag {
	struct Bag : entity::Entity
	{
	};
}
namespace pouch {
	struct Pouch : entity::Entity
	{
	};
}
namespace barrel {
	struct Barrel : entity::Entity
	{
		bool carry = false;
	};
}
namespace chest {
	struct Chest : entity::Entity
	{
		bool carry = false;
	};
}

map<string, entity::Entity> createContents(const json& j);