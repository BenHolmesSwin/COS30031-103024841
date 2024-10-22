
#include "json.hpp"
#include "Location.h"

using namespace std;
using json = nlohmann::json;

namespace location {
	void from_json(const json& j,Location& l){
		j.at("id").get_to(l.id);
		j.at("name").get_to(l.name);
		j.at("desc").get_to(l.description);
		j.at("connections").get_to(l.connections);
		for (const auto& ent : j["contents"]) {
			string id = ent["id"];
			entity::Entity entityClass = ent.template get<entity::Entity>();
			l.contents.insert(pair<string, entity::Entity>(id, entityClass));
		}
	}
}