
#include "json.hpp"
#include "Location.h"

using namespace std;
using json = nlohmann::json;

namespace location {
	void from_json(const json& j,Location l){
		j.at("id").get_to(l.id);
		j.at("name").get_to(l.name);
		j.at("desc").get_to(l.description);
		auto connections = j.at("connections");
		for (json connection : connections) {
			l.connections.push_back(connection);
		}
	}
}