
#include "Path.h"

namespace path {
	string Path::findLoc(string loc) {
		if (loc == locactionId1) {
			return locactionId2;
		}
		else {
			return locactionId1;
		}
	}

	void from_json(const json& j, Path& p) {
		j.at("loc1").get_to(p.locactionId1);
		j.at("loc2").get_to(p.locactionId2);
	}
}