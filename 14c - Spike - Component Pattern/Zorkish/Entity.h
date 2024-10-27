#pragma once

#include <string>
#include <vector>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Component;
struct Message;
class MessageBoard;

namespace entity {
	struct Entity
	{
		string id;
		string name;
		string description;
		bool carry = true;
		bool open = true;
		bool locked = false;
		int health = 0;
		vector<string> componentsList;
		map<string, Entity> inventory;
		map<string, Component*> components;
		void componentAdd(string id, Component* component);
		void recieveMessage(Message message, MessageBoard& msgBoard);
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