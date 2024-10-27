#pragma once

#include "Entity.h"

class MessageBoard;

namespace player {
	class Player {
	public:
		map<string, entity::Entity> inventory;
		int health;
		void addItem(string id, entity::Entity item);
		void removeItem(string id);
	};

	void from_json(const json& j, Player& l);
}