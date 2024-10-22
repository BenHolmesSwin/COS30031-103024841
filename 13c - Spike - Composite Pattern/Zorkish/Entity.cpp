
#include "json.hpp"
#include "Entity.h"

using namespace std;
using json = nlohmann::json;

namespace entity {
	void from_json(const json& j, Entity& l) {
		j.at("id").get_to(l.id);
		j.at("name").get_to(l.name);
		j.at("desc").get_to(l.description);
		j.at("carry").get_to(l.carry);
	}

}

//if i wanted to make bag and such recursive (contains other bags on start) i would just replace whats in the for loop with .inventory = entity::createinventory(ent);
namespace bag {
	void from_json(const json& j, Bag& b) {
		j.at("id").get_to(b.id);
		j.at("name").get_to(b.name);
		j.at("desc").get_to(b.description);
		for (const auto& ent : j["inventory"]) {
			b.inventory[ent["id"]] = ent.template get<entity::Entity>();
		}
	}
}
namespace pouch {
	void from_json(const json& j, Pouch& p) {
		j.at("id").get_to(p.id);
		j.at("name").get_to(p.name);
		j.at("desc").get_to(p.description);
		j.at("locked").get_to(p.locked);
		j.at("open").get_to(p.open);
		for (const auto& ent : j["inventory"]) {
			p.inventory[ent["id"]] = ent.template get<entity::Entity>();
		}
	}
}
namespace barrel {
	void from_json(const json& j, Barrel& b) {
		j.at("id").get_to(b.id);
		j.at("name").get_to(b.name);
		j.at("desc").get_to(b.description);
		j.at("open").get_to(b.open);
		for (const auto& ent : j["inventory"]) {
			b.inventory[ent["id"]] = ent.template get<entity::Entity>();
		}
	}
}
namespace chest {
	void from_json(const json& j, Chest& c) {
		j.at("id").get_to(c.id);
		j.at("name").get_to(c.name);
		j.at("desc").get_to(c.description);
		j.at("locked").get_to(c.locked);
		j.at("open").get_to(c.open);
		for (const auto& ent : j["inventory"]) {
			c.inventory[ent["id"]] = ent.template get<entity::Entity>();
		}
	}
}

map<string, entity::Entity> createContents(const json& j) {
	map<string, entity::Entity> result;
	for (const auto& ent : j["inventory"]) {
		if (ent["name"] == "Bag") {
			result[ent["id"]] = ent.template get<bag::Bag>();
		}
		else if (ent["name"] == "Pouch") {
			result[ent["id"]] = ent.template get<pouch::Pouch>();
		}
		else if (ent["name"] == "Barrel") {
			result[ent["id"]] = ent.template get<barrel::Barrel>();
		}
		else if (ent["name"] == "Chest") {
			result[ent["id"]] = ent.template get<chest::Chest>();
		}
		else {
			result[ent["id"]] = ent.template get<entity::Entity>();
		}
	}
	return result;
}