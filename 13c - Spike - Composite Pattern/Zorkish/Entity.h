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
		bool carry;
		bool locked = false;
		map<string, Entity> contents;
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