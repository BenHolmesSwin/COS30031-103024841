
#include "Player.h"

using namespace std;
using json = nlohmann::json;

namespace player {
	void Player::addItem(string id, entity::Entity item) {
		inventory[id] = item;
	}

	void Player::removeItem(string id) {
		inventory.erase(id);
	}

	void from_json(const json& j, Player& p) {
		j.at("health").get_to(p.health);
		for (const auto& ent : j["inventory"]) {
			string id = ent["id"];
			entity::Entity entityClass = ent.template get<entity::Entity>();
			p.addItem(id, entityClass);
		}
	}
	
}