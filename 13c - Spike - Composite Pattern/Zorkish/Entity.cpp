
#include "json.hpp"
#include "Entity.h"

using namespace std;
using json = nlohmann::json;

namespace entity {
	void from_json(const json& j, Entity& l) {
		j.at("id").get_to(l.id);
		j.at("name").get_to(l.name);
		j.at("desc").get_to(l.description);
	}
}